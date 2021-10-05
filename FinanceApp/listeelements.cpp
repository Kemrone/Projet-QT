#include "listeelements.h"
#include "ui_listeelements.h"
#include "connexion.h"
#include "printview.h"
#include <QPointer>
#include <QDebug>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

ListeElements::ListeElements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListeElements)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    /*On custom la page d'accueil :
     * .On ne veut pas que l'user voit les tables
     * programmes/transactions si il ne clique pas sur un élément lié
     * .On fait en sorte de sélectionner toute la ligne et non qu'un seul élément
     * .On commence par ressortir la liste des chapitre (racine de l'arborescence)
        */
    ui->articleList->verticalHeader()->setVisible(false);
    ui->progList->verticalHeader()->setVisible(false);
    ui->TransactionList->verticalHeader()->setVisible(false);
    ui->articleList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->progList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TransactionList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TransactionList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->progList->setVisible(false);
    ui->TransactionList->setVisible(false);
    ui->printButton->setVisible(false);
    ui->ChapComboBox->addItem("Chapitre");
    ui->SousChapComboBox->addItem("Sous-Chapitre");

    Connexion con;
    con.Connecter();

    QSqlQuery query ;
    QString res;
    query.prepare("SELECT idChapitre,nom FROM chapitre");
    query.exec();
        while(query.next()){

             res = query.value(0).toString() + " | " + query.value(1).toString()  ;
             ui->ChapComboBox->addItem(res);
        }
}


ListeElements::~ListeElements()
{
    delete ui;
}




void ListeElements::on_ChapComboBox_currentTextChanged(const QString &arg1)
{
    /*On découvre les sous chapitres liés aux chapitres sélectionné
    *On reset les autres éléments en cour sur la page, pour rester cohérent avec le nouveau
    chapitre*/

    if(arg1 == "Chapitre"){
         ui->articleList->reset();
         ui->progList->reset();
         ui->progList->setVisible(false);
         ui->TransactionList->setVisible(false);
         ui->SousChapComboBox->clear();
         ui->SousChapComboBox->addItem("Sous-Chapitre");
         ui->deleteProgButton->setVisible(false);
          ui->printButton->setVisible(false);
    }
    else{
          ui->printButton->setVisible(false);
          ui->progList->setVisible(false);
          ui->TransactionList->setVisible(false);
          ui->SousChapComboBox->clear();
          ui->progList->reset();
          ui->deleteProgButton->setVisible(false);
          ui->printButton->setVisible(false);


           QSqlQuery query;
           QString res;
          QString  id =   ui->ChapComboBox->currentText();
           QStringList idSplited = id.split('|');




           query.prepare("SELECT idSousChap,nom FROM sous_chapitre WHERE idChapitre = " +idSplited.at(0));
            query.exec();
           while(query.next()){
               res = query.value(0).toString() + " | " + query.value(1).toString();
               ui->SousChapComboBox->addItem(res);
        }
    }
}





void ListeElements::on_SousChapComboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Sous-Chapitre"){
        ui->deleteProgButton->setVisible(false);
         ui->printButton->setVisible(false);
        ui->progList->setVisible(false);
        ui->TransactionList->setVisible(false);
        ui->progList->reset();
        ui->articleList->reset();
    }
    else{
        ui->deleteProgButton->setVisible(false);
         ui->printButton->setVisible(false);
        ui->progList->setVisible(false);
        ui->TransactionList->setVisible(false);
        ui->progList->reset();
        ui->articleList->reset();

        QSqlQueryModel * model = new QSqlQueryModel();
        QSqlQuery query;
        QString  id =   ui->SousChapComboBox->currentText();
        QStringList idSplited = id.split('|');



    query.prepare("SELECT idArticle,nom,solde,derniereMaj FROM article WHERE idSousChapitre = " + idSplited.at(0));
    query.exec();
    model->setQuery(query);
    ui->articleList->setModel(model);
    }

}


void ListeElements::on_articleList_clicked(const QModelIndex &index)
{
    ui->printButton->setVisible(true);
    ui->progList->setVisible(true);
    ui->deleteProgButton->setVisible(true);
    QSqlQuery query;
     QItemSelectionModel *select = ui->articleList->selectionModel();
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQueryModel * model2 = new QSqlQueryModel();
    QString SelectedRow = select ->selectedRows(0).value(0).data().toString();
            //index.data(0).toString();
    qDebug()<<SelectedRow;
    query.prepare("SELECT idProgramme,nom,solde,derniereMaj FROM programme WHERE idArticle = " + SelectedRow);
    query.exec();
    model->setQuery(query);
    ui->progList->setModel(model);

    query.prepare("SELECT idTransaction,nom,montant,CASE WHEN idType = 1 THEN 'dotation' WHEN idType = 2 THEN 'depense' END AS type,description FROM transactions WHERE idArticle = "+SelectedRow);
    query.exec();
    model2->setQuery(query);
    ui->TransactionList->setModel(model2);
    ui->TransactionList->setVisible(true);

}

void ListeElements::on_progList_clicked(const QModelIndex &index)
{

    ui->deleteProgButton->setVisible(true);
    ui->printButton->setVisible(true);
    ui->progList->setVisible(true);

    QSqlQuery query;
    QSqlQueryModel * model = new QSqlQueryModel();
     QItemSelectionModel *select = ui->progList->selectionModel();
    QString SelectedRow = select ->selectedRows(0).value(0).data().toString();//index.data(0).toString();


    query.prepare("SELECT idTransaction,nom,montant,CASE WHEN idType = 1 THEN 'dotation' WHEN idType = 2 THEN 'depense' END AS type,description FROM transactions WHERE idProgramme = "+select->selectedRows(0).value(0).data().toString());
    query.exec();
    model->setQuery(query);
    ui->TransactionList->setModel(model);
}





void ListeElements::on_printButton_clicked()
{
    QPointer<PrintView> recap = new PrintView;
    QItemSelectionModel *select = ui->TransactionList->selectionModel();
    QSqlQuery query;
    QString prjt;
    query.prepare("SELECT article.nom FROM article INNER JOIN transactions ON article.idArticle = transactions.idArticle WHERE transactions.idTransaction  = "+ select->selectedRows(0).value(0).data().toString());
    query.exec();
    while(query.next()){
     prjt = query.value(0).toString();
    }

    if(prjt == ""){
        query.prepare("SELECT programme.nom FROM programme INNER JOIN transactions ON programme.idProgramme = transactions.idProgramme WHERE transactions.idTransaction  = "+ select->selectedRows(0).value(0).data().toString());
        query.exec();
        while(query.next()){
        prjt = query.value(0).toString();
        }
    }


     QString espace = "                        ";
     QString msg = "Nom transaction :" +espace +  select->selectedRows(1).value(0).data().toString() +"\n"
                  +"Montant :" + espace +select->selectedRows(2).value(0).data().toString()+"\n"
                  +"Projet Associé :" + espace + prjt+"\n"
                  +"Description :" + espace + select->selectedRows(4).value(0).data().toString();


    recap->receiveTitle(select->selectedRows(3).value(0).data().toString());
    recap->receiveMessage(msg);


    recap->show();


}

void ListeElements::on_deleteChapButton_clicked()
{
    QString  id =   ui->ChapComboBox->currentText();
    QStringList idSplited = id.split('|');


    QSqlQuery query;
    query.prepare("DELETE FROM programme "
                  "WHERE idProgramme = "
                  "(SELECT programme.idProgramme "
                  "FROM programme INNER JOIN article ON programme.idArticle = article.idArticle "
                                 "INNER JOIN sous_chapitre ON article.idSousChapitre = sous_chapitre.idSousChap "
                                 "INNER JOIN chapitre ON chapitre.idChapitre = sous_chapitre.idChapitre "
                  "WHERE chapitre.idChapitre = " + idSplited.at(0) + ")");
    query.exec();

    query.prepare("DELETE FROM Article "
                  "WHERE idArticle = "
                  "(SELECT article.idArticle "
                  "FROM article INNER JOIN sous_chapitre ON article.idSousChapitre = sous_chapitre.idSousChap "
                                "INNER JOIN chapitre ON chapitre.idChapitre = sous_chapitre.idChapitre "
                  "WHERE chapitre.idChapitre = "+idSplited.at(0) + ")");
    query.exec();

    query.prepare("DELETE FROM sous_chapitre "
                  "WHERE idChapitre = "  +idSplited.at(0));


    query.exec();

    query.prepare("DELETE FROM chapitre "
                  "WHERE idChapitre = " +idSplited.at(0));

    query.exec();

    ui->ChapComboBox->removeItem(ui->ChapComboBox->currentIndex());
    ui->SousChapComboBox->clear();
    ui->SousChapComboBox->addItem("Sous-Chapitre");
    ui->progList->reset();
    ui->articleList->reset();
}

void ListeElements::on_deleteSousChapButton_clicked()
{
    QString  id =   ui->SousChapComboBox->currentText();
    QStringList idSplited = id.split('|');

    QSqlQuery query;

    query.prepare("DELETE FROM programme "
                  "WHERE idProgramme = "
                  "(SELECT programme.idProgramme "
                  "FROM programme INNER JOIN article ON programme.idArticle = article.idArticle "
                                 "INNER JOIN sous_chapitre ON article.idSousChapitre = sous_chapitre.idSousChap"
                  "WHERE sous_chapitre.idSousChap = " + idSplited.at(0) + ")");



    query.exec();

    query.prepare("DELETE FROM Article "
                  "WHERE idSousChapitre = "+idSplited.at(0));
    query.exec();

    query.prepare("DELETE FROM sous_chapitre "
                  "WHERE idSousChap = "  +idSplited.at(0));

    query.exec();
    ui->SousChapComboBox->removeItem(ui->SousChapComboBox->currentIndex());
    ui->progList->reset();
    ui->articleList->reset();


}

void ListeElements::on_deleteArticleButton_clicked()
{
    QItemSelectionModel *select = ui->articleList->selectionModel();

     QSqlQuery query;

     query.prepare("DELETE FROM Programme "
                   "WHERE idArticle = "+ select->selectedRows(0).value(0).data().toString());
     query.exec();



     query.prepare("DELETE FROM Article "
                   "WHERE idArticle = "+ select->selectedRows(0).value(0).data().toString());

     query.exec();

}

void ListeElements::on_deleteProgButton_clicked()
{
    QItemSelectionModel *select = ui->progList->selectionModel();

     QSqlQuery query;

     query.prepare("DELETE FROM Programme "
                   "WHERE idProgramme = "+ select->selectedRows(0).value(0).data().toString());
     query.exec();
}

void ListeElements::on_PreviousButton_clicked()
{
    hide();
    parentWidget()->show();
}



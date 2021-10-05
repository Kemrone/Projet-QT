#include "dota.h"
#include "ui_dota.h"
#include "article.h"
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "QDebug"

#include "connexion.h"

Dota::Dota(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dota)
{
    ui->setupUi(this);

 Connexion con;
 con.Connecter();

    QSqlQuery * query = new QSqlQuery();
    QString res;
    query->prepare("SELECT idArticle,nom,solde,budgetInitial FROM article");
    query->exec();
        while(query->next()){
             res = query->value(0).toString() + " - " + query->value(1).toString() + " - solde = '"+ query->value(2).toString() + "' - budgetDépart : "+query->value(3).toString() ;
             ui->comboBox_article->addItem(res);
        }


        QString  solde =   ui->comboBox_article->currentText();
        QStringList soldeSplited = solde.split('-');

        query ->prepare("SELECT solde FROM article WHERE idArticle = "+soldeSplited.at(0) +" AND nom = '" + soldeSplited.at(1)+"'");


       query->exec();
        solde = query->value(0).toString();
        ui->Montant_label->setText( solde);


}




Dota::~Dota()
{
    delete ui;
}

void Dota::on_OK_Button_clicked()
{
    QString nom = ui->txt_nom_dotation->toPlainText();
    QString description = ui->txt_description->toPlainText();
    double montant = ui->txt_montant->toPlainText().toDouble();
    QString  boxContent =   ui->comboBox_article->currentText();
    QStringList soldeSplited = boxContent.split("'");
    QStringList stkSplited = boxContent.split('-');
    double solde = soldeSplited.at(1).toFloat();

    QString resultat = QString::number(solde+montant);




    QSqlQuery * query = new QSqlQuery();
    query ->prepare("UPDATE article SET solde =" + resultat + "WHERE idArticle = "+ stkSplited.at(0));
    query->exec();



    query ->prepare("INSERT INTO effectuer SET (idArticle,idTransaction)""VALUES(?,?)" );
    query->addBindValue(stkSplited.at(0));
    query->exec();




    query ->prepare("INSERT INTO transactions (nom,montant,description,idType,idArticle)"
                    "VALUES (?,?,?,?,?)");
          query->addBindValue(nom);
          query->addBindValue(montant);
          query->addBindValue(description);
          query->addBindValue(1);
          query->addBindValue(stkSplited.at(0));
     query->exec();




}

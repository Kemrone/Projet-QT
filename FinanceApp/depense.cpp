#include "depense.h"
#include "ui_depense.h"
#include "connexion.h"
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QPointer>
#include <iostream>
#include <operations.h>
#include <printview.h>

Depense::Depense(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Depense)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);


    Connexion con;
    con.Connecter();

    QSqlQuery query ;
    QString res;
    query.prepare("SELECT idArticle,nom,solde,budgetInitial FROM article");
    query.exec();
        while(query.next()){
             res = query.value(0).toString() + " | " + query.value(1).toString() + " | solde = '"+ query.value(2).toString() + "' | budgetDépart : "+query.value(3).toString() ;
             ui->comboBox_article->addItem(res);
                 }


}

Depense::~Depense()
{
    delete ui;
}




void Depense::on_OK_Button_clicked()
{

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%Y",timeinfo);
    std::string date(buffer);

    Article art;
    Budget init;
    Budget actuel;
    Frais dep;
    dep.setNom(ui->txt_nom_dotation->toPlainText().toLocal8Bit().constData());
    dep.setDescription(ui->txt_description->toPlainText().toLocal8Bit().constData());

    // QString nom = ui->txt_nom_dotation->toPlainText();
    // QString description = ui->txt_description->toPlainText();
    // double montant = ui->txt_montant->toPlainText().toDouble();
     QString  boxContent =   ui->comboBox_article->currentText();
     QStringList soldeSplited = boxContent.split("'");
     QStringList stkSplited = boxContent.split('|');
   //  double solde = soldeSplited.at(1).toFloat();
   //  QString resultat = QString::number(solde+montant);

    //QString resultat = QString::number(solde-montant);


    Connexion con;
    con.Connecter();
    QSqlQuery  query ;

    QMessageBox::StandardButton message;
    message = QMessageBox::question(this, "MessageBox Classique", "Etes vous sur de vouloir exeucter cette transaction?", QMessageBox::Yes|QMessageBox::No);
     if(message == QMessageBox::No ){

     }
     else if(message == QMessageBox::Yes){

      if(ui->article_radio->isChecked()){
         query.prepare("SELECT * FROM article WHERE idArticle = " + stkSplited.at(0));
         query.exec();
         while(query.next()){

             art.setNom(query.value(1).toString().toLocal8Bit().constData());
             actuel.putMontant(query.value(2).toDouble());
             init.putMontant(query.value(3).toDouble());
             art.setUpdate(query.value(4).toInt());
            }
         art.putBudgetSup(actuel);
         art.putBudgetInitial(init);
         art.setId(stkSplited.at(0).toInt());
         dep.depenser(art, ui->txt_montant->toPlainText().toDouble());
         art.setUpdate(std::stoi(date));


         query.prepare("UPDATE article SET solde = " + QString::fromStdString(std::to_string((art.getBudgetSup().getMontant()))) +" , budgetInitial = " +QString::fromStdString(std::to_string((art.getBudgetInitial().getMontant()))) + " , derniereMaj = " + QString::number(art.getUpdate()) + " WHERE idArticle = " + QString::number(art.getId()));
         query.exec();

         query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                         "VALUES (?,?,?,?,?,?)");
               query.addBindValue(ui->txt_nom_dotation->toPlainText());
               query.addBindValue(ui->txt_montant->toPlainText().toDouble());
               query.addBindValue(ui->txt_description->toPlainText());
               query.addBindValue(QString::fromStdString(date));
               query.addBindValue(1);
               query.addBindValue(QString::number(art.getId()));
          query.exec();
         }


      else if(ui->programme_radio->isChecked()){
          query.prepare("SELECT * FROM programme WHERE idProgramme = " + stkSplited.at(0));
          query.exec();
          while(query.next()){
              art.setNom(query.value(1).toString().toLocal8Bit().constData());
              actuel.putMontant(query.value(2).toDouble());
              init.putMontant(query.value(3).toDouble());
              art.setUpdate(query.value(4).toInt());
             }
          art.putBudgetSup(actuel);
          art.putBudgetInitial(init);
          art.setId(stkSplited.at(0).toInt());
          dep.depenser(art, ui->txt_montant->toPlainText().toDouble());
          art.setUpdate(std::stoi(date));

          query.prepare("UPDATE programme SET solde = " + QString::fromStdString(std::to_string((art.getBudgetSup().getMontant()))) +" , budgetInitial = " +QString::fromStdString(std::to_string((art.getBudgetInitial().getMontant()))) + " , derniereMaj = " + QString::number(art.getUpdate()) + " WHERE idProgramme = " + QString::number(art.getId()));
          query.exec();

          query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idProgramme)"
                          "VALUES (?,?,?,?,?,?)");
                query.addBindValue(ui->txt_nom_dotation->toPlainText());
                query.addBindValue(ui->txt_description->toPlainText());
                query.addBindValue(ui->txt_montant->toPlainText().toDouble());
                query.addBindValue(QString::fromStdString(date));
                query.addBindValue(2);
                query.addBindValue(QString::number(art.getId()));
           query.exec();
          }


      }


 /*

    if(ui->article_radio->isChecked()){

        query.prepare("SELECT budgetInitial FROM article WHERE idArticle = "+ stkSplited.at(0));
        query.exec();
            if(query.next()){
                 budgetInit = query.value(0).toDouble();
            }

            if(budgetInit ==0 ){
                budgetInit = resultat.toDouble();
            }

    query.prepare("UPDATE article SET solde = " + resultat +", budgetInitial = " + QString::number(budgetInit) +  " WHERE idArticle = "+ stkSplited.at(0));
    query.exec();

    query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                    "VALUES (?,?,?,?,?,?)");
          query.addBindValue(nom);
          query.addBindValue(montant);
          query.addBindValue(description);
           query.addBindValue(QString::fromStdString(date));
          query.addBindValue(1);
          query.addBindValue(stkSplited.at(0));
     query.exec();
 }



    else if(ui->programme_radio->isChecked()){

        query.prepare("SELECT budgetInitial FROM programme WHERE idProgramme = "+ stkSplited.at(0));
        query.exec();
            while(query.next()){
                 budgetInit = query.value(0).toDouble();
        }

            if(budgetInit ==0 ){
                budgetInit = resultat.toDouble();
            }


        query.prepare("UPDATE programme SET solde = " + resultat + ", budgetInitial =" +budgetInit+ " WHERE idProgramme = "+ stkSplited.at(0));
        query.exec();

        query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                        "VALUES (?,?,?,?,?,?)");
              query.addBindValue(nom);
              query.addBindValue(montant);
              query.addBindValue(description);
               query.addBindValue(QString::fromStdString(date));
              query.addBindValue(1);
              query.addBindValue(stkSplited.at(0));
         query.exec();

          }
 */
     QMessageBox::information(this,"Done","Transaction Effectuée");
     QMessageBox::StandardButton message2;
    message2 = QMessageBox::question(this, "MessageBox Important", "Voulez vous imprimer un recapitulatif ?", QMessageBox::Yes|QMessageBox::No);


      if(message2 == QMessageBox::No){
          art.~Article();
          dep.~Frais();
          init.~Budget();
          actuel.~Budget();
          hide();
      }


      else if(message2 == QMessageBox::Yes){


         QPointer<PrintView> recap = new PrintView;

          QString espace = "                        ";
          QString msg = "Nom transaction :" +espace +  QString::fromStdString(dep.getNom())+"\n"
                       +"Montant :" + espace + QString(ui->txt_montant->toPlainText())+"\n"
                       +"Projet Associé :" + espace + QString::fromStdString(art.getNom())+"\n"
                       +"Description :" + espace + QString::fromStdString(dep.getDescription());



         recap->receiveTitle("Depense");
         recap->receiveMessage(msg);

         recap->show();











          art.~Article();
          dep.~Frais();
          init.~Budget();
          actuel.~Budget();
          hide();

          }
     }





void Depense::on_article_radio_clicked()
{
    ui->comboBox_article->clear();

    Connexion con;
    con.Connecter();
    QSqlQuery query ;
    QString res;
    query.prepare("SELECT idArticle,nom,solde,budgetInitial FROM article");
    query.exec();
        while(query.next()){
             res = query.value(0).toString() + " | " + query.value(1).toString() + " | solde = '"+ query.value(2).toString() + "' | budgetDépart : "+query.value(3).toString() ;
             ui->comboBox_article->addItem(res);
        }
}





void Depense::on_programme_radio_clicked()
{
    ui->comboBox_article->clear();

    Connexion con;
    con.Connecter();
    QSqlQuery query ;
    QString res;
    query.prepare("SELECT idProgramme,nom,solde,budgetInitial FROM programme");
    query.exec();
        while(query.next()){
             res = query.value(0).toString() + " | " + query.value(1).toString() + " | solde = '"+ query.value(2).toString() + "' | budgetDépart : "+query.value(3).toString() ;
             ui->comboBox_article->addItem(res);
        }
}



void Depense::on_comboBox_article_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
    ui->Montant_label->setText("null");
    }
    else{
        QString  solde =   ui->comboBox_article->currentText();
        QStringList soldeSplited = solde.split('|');
        solde = soldeSplited.at(2);
        ui->Montant_label->setText(solde);


    }
}

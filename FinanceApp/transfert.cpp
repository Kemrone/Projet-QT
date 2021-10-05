#include "transfert.h"
#include "ui_transfert.h"
#include "connexion.h"
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QPointer>
#include <QSqlQuery>
#include <operations.h>

Transfert::Transfert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transfert)
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
             ui->comboBox_article_2->addItem(res);


        }


}

Transfert::~Transfert()
{
    delete ui;
}

void Transfert::on_comboBox_article_currentTextChanged(const QString &arg1)
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
void Transfert::on_comboBox_article_2_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){
    ui->Montant_label_2->setText("null");
    }
    else{
        QString  solde =   ui->comboBox_article_2->currentText();
        QStringList soldeSplited = solde.split('|');
        solde = soldeSplited.at(2);
        ui->Montant_label_2->setText(solde);
    }
}


void Transfert::on_article_radio_1_clicked()
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

void Transfert::on_article_radio_2_clicked()
{
    ui->comboBox_article_2->clear();

    Connexion con;
    con.Connecter();
    QSqlQuery query ;
    QString res;
    query.prepare("SELECT idArticle,nom,solde,budgetInitial FROM article");
    query.exec();
        while(query.next()){
             res = query.value(0).toString() + " | " + query.value(1).toString() + " | solde = '"+ query.value(2).toString() + "' | budgetDépart : "+query.value(3).toString() ;
             ui->comboBox_article_2->addItem(res);
        }
}



void Transfert::on_programme_radio_1_clicked()
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

void Transfert::on_programme_radio_2_clicked()
{
    ui->comboBox_article_2->clear();

    Connexion con;
    con.Connecter();
    QSqlQuery query ;
    QString res;
    query.prepare("SELECT idProgramme,nom,solde,budgetInitial FROM programme");
    query.exec();
        while(query.next()){
             res = query.value(0).toString() + " | " + query.value(1).toString() + " | solde = '"+ query.value(2).toString() + "' | budgetDépart : "+query.value(3).toString() ;
             ui->comboBox_article_2->addItem(res);
        }
}


void Transfert::on_OK_Button_clicked()
{

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%Y",timeinfo);
    std::string date(buffer);
    QString stk;

   Article art;
   Budget init;
   Budget actuel;
   Frais dep;
   Credit cred;
   cred.setNom(ui->txt_nom_dotation->toPlainText().toLocal8Bit().constData());
   cred.setDescription(ui->txt_description->toPlainText().toLocal8Bit().constData());

    //QString nom = ui->txt_nom_dotation->toPlainText();
   // QString description = ui->txt_description->toPlainText();
   // double montant = ui->txt_montant->toPlainText().toDouble();
    QString  boxContent =   ui->comboBox_article->currentText();
    QString boxContent2 = ui->comboBox_article_2->currentText();
    QStringList soldeSplited = boxContent.split("'");
    QStringList stkSplited = boxContent.split('|');
    QStringList soldeSplited2 = boxContent2.split("'");
    QStringList stkSplited2 = boxContent2.split('|');
   // double solde = soldeSplited.at(1).toFloat();
  //  double solde2 = soldeSplited2.at(1).toFloat();
   // QString resultat;


    Connexion con;
    con.Connecter();
    QSqlQuery query;


    QMessageBox::StandardButton message;
    message = QMessageBox::question(this, "MessageBox Classique", "Etes vous sur de vouloir exeucter cette transaction?", QMessageBox::Yes|QMessageBox::No);
     if(message == QMessageBox::No ){

     }
     else if(message == QMessageBox::Yes){

    if(ui->article_radio_1->isChecked() && ui->article_radio_2->isChecked()){

        query.prepare("SELECT * FROM article WHERE idArticle = " + stkSplited.at(0));
        query.exec();
        while(query.next()){
            art.setNom(query.value(1).toString().toLocal8Bit().constData());
            actuel.putMontant(query.value(2).toDouble());
            init.putMontant(query.value(3).toDouble());
            art.setUpdate(query.value(4).toInt());
            stk = query.value(1).toString();
           }
        art.putBudgetSup(actuel);
        art.putBudgetInitial(init);
        art.setId(stkSplited.at(0).toInt());
        cred.crediter(art, ui->txt_montant->toPlainText().toDouble(), 0);
        art.setUpdate(std::stoi(date));

        query.prepare("UPDATE article SET solde = " + QString::fromStdString(std::to_string((art.getBudgetSup().getMontant()))) +" , budgetInitial = " +QString::fromStdString(std::to_string((art.getBudgetInitial().getMontant()))) + " , derniereMaj = " + QString::number(art.getUpdate()) +  " WHERE idArticle = " + QString::number(art.getId()));
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

         /*-----------------------------------------------------*/

         query.prepare("SELECT * FROM article WHERE idArticle = " + stkSplited2.at(0));
         query.exec();
         while(query.next()){

             art.setNom(query.value(1).toString().toLocal8Bit().constData());
             actuel.putMontant(query.value(2).toDouble());
             init.putMontant(query.value(3).toDouble());
              art.setUpdate(query.value(4).toInt());

            }
         art.putBudgetSup(actuel);
         art.putBudgetInitial(init);
         art.setId(stkSplited2.at(0).toInt());
         dep.depenser(art, ui->txt_montant->toPlainText().toDouble());
         art.setUpdate(std::stoi(date));

         query.prepare("UPDATE article SET solde = " + QString::fromStdString(std::to_string((art.getBudgetSup().getMontant()))) +" , budgetInitial = " +QString::fromStdString(std::to_string((art.getBudgetInitial().getMontant()))) + " , derniereMaj = " + QString::number(art.getUpdate()) +  " WHERE idArticle = " + QString::number(art.getId()));
         query.exec();

         query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                         "VALUES (?,?,?,?,?,?)");
               query.addBindValue(ui->txt_nom_dotation->toPlainText());
               query.addBindValue(ui->txt_montant->toPlainText().toDouble());
               query.addBindValue(ui->txt_description->toPlainText());
               query.addBindValue(QString::fromStdString(date));
               query.addBindValue(2);
               query.addBindValue(QString::number(art.getId()));
          query.exec();

        }



    else if (ui->article_radio_1->isChecked() && ui->programme_radio_2->isChecked()){

        query.prepare("SELECT * FROM article WHERE idArticle = " + stkSplited.at(0));
        query.exec();
        while(query.next()){
            art.setNom(query.value(1).toString().toLocal8Bit().constData());
            actuel.putMontant(query.value(2).toDouble());
            init.putMontant(query.value(3).toDouble());
            art.setUpdate(query.value(4).toInt());
            stk = query.value(1).toString();
           }
        art.putBudgetSup(actuel);
        art.putBudgetInitial(init);
        art.setId(stkSplited.at(0).toInt());
        cred.crediter(art, ui->txt_montant->toPlainText().toDouble(), 0);
        art.setUpdate(std::stoi(date));

        query.prepare("UPDATE article SET solde = " + QString::fromStdString(std::to_string((art.getBudgetSup().getMontant()))) +" , budgetInitial = " +QString::fromStdString(std::to_string((art.getBudgetInitial().getMontant()))) + " , derniereMaj = " + QString::number(art.getUpdate()) +  " WHERE idArticle = " + QString::number(art.getId()));
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

         /*-----------------------------------------------------*/

         query.prepare("SELECT * FROM programme WHERE idProgramme = " + stkSplited2.at(0));
         query.exec();
         while(query.next()){

             art.setNom(query.value(1).toString().toLocal8Bit().constData());
             actuel.putMontant(query.value(2).toDouble());
             init.putMontant(query.value(3).toDouble());
              art.setUpdate(query.value(4).toInt());
            }
         art.putBudgetSup(actuel);
         art.putBudgetInitial(init);
         art.setId(stkSplited2.at(0).toInt());
         dep.depenser(art, ui->txt_montant->toPlainText().toDouble());
         art.setUpdate(std::stoi(date));

         query.prepare("UPDATE programme SET solde = " + QString::fromStdString(std::to_string((art.getBudgetSup().getMontant()))) +" , budgetInitial = " +QString::fromStdString(std::to_string((art.getBudgetInitial().getMontant()))) + " , derniereMaj = " + QString::number(art.getUpdate()) +  " WHERE idProgramme = " + QString::number(art.getId()));
         query.exec();

         query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                         "VALUES (?,?,?,?,?,?)");
               query.addBindValue(ui->txt_nom_dotation->toPlainText());
               query.addBindValue(ui->txt_montant->toPlainText().toDouble());
               query.addBindValue(ui->txt_description->toPlainText());
               query.addBindValue(QString::fromStdString(date));
               query.addBindValue(2);
               query.addBindValue(QString::number(art.getId()));
          query.exec();

    }



     else if (ui->programme_radio_1->isChecked() && ui->article_radio_2->isChecked()){

        query.prepare("SELECT * FROM programme WHERE idProgramme = " + stkSplited.at(0));
        query.exec();
        while(query.next()){
            art.setNom(query.value(1).toString().toLocal8Bit().constData());
            actuel.putMontant(query.value(2).toDouble());
            init.putMontant(query.value(3).toDouble());
            art.setUpdate(query.value(4).toInt());
            stk = query.value(1).toString();
           }
        art.putBudgetSup(actuel);
        art.putBudgetInitial(init);
        art.setId(stkSplited.at(0).toInt());
        cred.crediter(art, ui->txt_montant->toPlainText().toDouble(), 0);
        art.setUpdate(std::stoi(date));

        query.prepare("UPDATE programme SET solde = " + QString::fromStdString(std::to_string((art.getBudgetSup().getMontant()))) +" , budgetInitial = " +QString::fromStdString(std::to_string((art.getBudgetInitial().getMontant()))) + " , derniereMaj = " + QString::number(art.getUpdate()) +  " WHERE idProgramme = " + QString::number(art.getId()));
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

         /*-----------------------------------------------------*/

         query.prepare("SELECT * FROM article WHERE idArticle = " + stkSplited2.at(0));
         query.exec();
         while(query.next()){

             art.setNom(query.value(1).toString().toLocal8Bit().constData());
             actuel.putMontant(query.value(2).toDouble());
             init.putMontant(query.value(3).toDouble());
              art.setUpdate(query.value(4).toInt());
            }
         art.putBudgetSup(actuel);
         art.putBudgetInitial(init);
         art.setId(stkSplited2.at(0).toInt());
         dep.depenser(art, ui->txt_montant->toPlainText().toDouble());
         art.setUpdate(std::stoi(date));

         query.prepare("UPDATE article SET solde = " + QString::fromStdString(std::to_string((art.getBudgetSup().getMontant()))) +" , budgetInitial = " +QString::fromStdString(std::to_string((art.getBudgetInitial().getMontant()))) + " , derniereMaj = " + QString::number(art.getUpdate()) +  " WHERE idArticle = " + QString::number(art.getId()));
         query.exec();

         query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                         "VALUES (?,?,?,?,?,?)");
               query.addBindValue(ui->txt_nom_dotation->toPlainText());
               query.addBindValue(ui->txt_montant->toPlainText().toDouble());
               query.addBindValue(ui->txt_description->toPlainText());
               query.addBindValue(QString::fromStdString(date));
               query.addBindValue(2);
               query.addBindValue(QString::number(art.getId()));
          query.exec();

        }

    else if (ui->programme_radio_1->isChecked() && ui->programme_radio_2->isChecked()){

        query.prepare("SELECT * FROM programme WHERE idProgramme = " + stkSplited.at(0));
        query.exec();
        while(query.next()){
            art.setNom(query.value(1).toString().toLocal8Bit().constData());
            actuel.putMontant(query.value(2).toDouble());
            init.putMontant(query.value(3).toDouble());
            art.setUpdate(query.value(4).toInt());
            stk = query.value(1).toString();
           }
        art.putBudgetSup(actuel);
        art.putBudgetInitial(init);
        art.setId(stkSplited.at(0).toInt());
        cred.crediter(art, ui->txt_montant->toPlainText().toDouble(), 0);
        art.setUpdate(std::stoi(date));

        query.prepare("UPDATE programme SET solde = " + QString::fromStdString(std::to_string((art.getBudgetSup().getMontant()))) +" , budgetInitial = " +QString::fromStdString(std::to_string((art.getBudgetInitial().getMontant()))) + " , derniereMaj = " + QString::number(art.getUpdate()) +  " WHERE idProgramme = " + QString::number(art.getId()));
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

         /*-----------------------------------------------------*/

         query.prepare("SELECT * FROM programme WHERE idProgramme = " + stkSplited2.at(0));
         query.exec();
         while(query.next()){

             art.setNom(query.value(1).toString().toLocal8Bit().constData());
             actuel.putMontant(query.value(2).toDouble());
             init.putMontant(query.value(3).toDouble());
              art.setUpdate(query.value(4).toInt());
            }
         art.putBudgetSup(actuel);
         art.putBudgetInitial(init);
         art.setId(stkSplited2.at(0).toInt());
         dep.depenser(art, ui->txt_montant->toPlainText().toDouble());
         art.setUpdate(std::stoi(date));

         query.prepare("UPDATE article SET solde = " + QString::fromStdString(std::to_string((art.getBudgetSup().getMontant()))) +" , budgetInitial = " +QString::fromStdString(std::to_string((art.getBudgetInitial().getMontant()))) + " , derniereMaj = " + QString::number(art.getUpdate()) +  " WHERE idProgramme = " + QString::number(art.getId()));
         query.exec();

         query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                         "VALUES (?,?,?,?,?,?)");
               query.addBindValue(ui->txt_nom_dotation->toPlainText());
               query.addBindValue(ui->txt_montant->toPlainText().toDouble());
               query.addBindValue(ui->txt_description->toPlainText());
               query.addBindValue(QString::fromStdString(date));
               query.addBindValue(2);
               query.addBindValue(QString::number(art.getId()));
          query.exec();

    }


    QMessageBox::information(this,"Done","Transaction Effectuée");
    QMessageBox::StandardButton message2;
   message2 = QMessageBox::question(this, "MessageBox Important", "Voulez vous imprimer un recapitulatif ?", QMessageBox::Yes|QMessageBox::No);


     if(message2 == QMessageBox::No){
         art.~Article();
         cred.~Credit();
         init.~Budget();
         actuel.~Budget();
         hide();
     }


     else if(message2 == QMessageBox::Yes){


        QPointer<PrintView> recap = new PrintView;

         QString espace = "                        ";
         QString msg = "Nom transaction :" +espace +  QString::fromStdString(cred.getNom())+"\n"
                      +"Montant :" + espace + QString(ui->txt_montant->toPlainText())+"\n"
                      +"Projet Associé :" + espace + QString::fromStdString(art.getNom())+ " et "+ stk +"\n"
                      +"Description :" + espace + QString::fromStdString(cred.getDescription());



        recap->receiveTitle("Transfert");
        recap->receiveMessage(msg);

        recap->show();

    }

     art.~Article();
     cred.~Credit();
     init.~Budget();
     actuel.~Budget();
     hide();


}













/*
    if(ui->article_radio_1->isChecked() && ui->article_radio_2->isChecked()){

    resultat = QString::number(solde+montant);

        query.prepare("UPDATE article SET solde = " + resultat + " WHERE idArticle = "+ stkSplited.at(0));
        query.exec();

        query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                        "VALUES (?,?,?,?,?,?)");
          //    query.addBindValue(nom);
             // query.addBindValue(montant);
            //  query.addBindValue(description);
               query.addBindValue(QString::fromStdString(date));
              query.addBindValue(1);
              query.addBindValue(stkSplited.at(0));
         query.exec();




         ------------------------------------------------------------------------------------------


     resultat = QString::number(solde2-montant);

        query.prepare("UPDATE article SET solde = " + resultat + " WHERE idArticle = "+ stkSplited2.at(0));
         query.exec();

         query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                         "VALUES (?,?,?,?,?,?)");
               query.addBindValue(nom);
               query.addBindValue(montant);
               query.addBindValue(description);
                query.addBindValue(QString::fromStdString(date));
               query.addBindValue(2);
               query.addBindValue(stkSplited2.at(0));
          query.exec();


    }

    else if (ui->article_radio_1->isChecked() && ui->programme_radio_2->isChecked()){

       // resultat = QString::number(solde+montant);

        //    query.prepare("UPDATE article SET solde = " + resultat + " WHERE idArticle = "+ stkSplited.at(0));
         //   query.exec();

            query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                            "VALUES (?,?,?,?,?,?)");
                  query.addBindValue(nom);
                  query.addBindValue(montant);
                  query.addBindValue(description);
                   query.addBindValue(QString::fromStdString(date));
                  query.addBindValue(1);
                  query.addBindValue(stkSplited.at(0));
             query.exec();




             ------------------------------------------------------------------------------------------


        // resultat = QString::number(solde2-montant);

           //  query.prepare("UPDATE programme SET solde = " + resultat + " WHERE idProgramme = "+ stkSplited2.at(0));
          //   query.exec();

             query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idProgramme)"
                             "VALUES (?,?,?,?,?,?)");
                   query.addBindValue(nom);
                   query.addBindValue(montant);
                   query.addBindValue(description);
                    query.addBindValue(QString::fromStdString(date));
                   query.addBindValue(2);
                   query.addBindValue(stkSplited2.at(0));
              query.exec();


    }

    else if (ui->programme_radio_1->isChecked() && ui->article_radio_2->isChecked()){

      //  resultat = QString::number(solde+montant);

       //     query.prepare("UPDATE programme SET solde = " + resultat + " WHERE idProgramme = "+ stkSplited.at(0));
         //   query.exec();

            query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idProgramme)"
                            "VALUES (?,?,?,?,?,?)");
                  query.addBindValue(nom);
                  query.addBindValue(montant);
                  query.addBindValue(description);
                   query.addBindValue(QString::fromStdString(date));
                  query.addBindValue(1);
                  query.addBindValue(stkSplited.at(0));
             query.exec();




             ------------------------------------------------------------------------------------------


        // resultat = QString::number(solde2-montant);

          //   query.prepare("UPDATE programme SET solde = " + resultat + " WHERE idArticle = "+ stkSplited2.at(0));
          //   query.exec();

             query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idArticle)"
                             "VALUES (?,?,?,?,?,?)");
                   query.addBindValue(nom);
                   query.addBindValue(montant);
                   query.addBindValue(description);
                    query.addBindValue(QString::fromStdString(date));
                   query.addBindValue(2);
                   query.addBindValue(stkSplited2.at(0));
              query.exec();

    }

    else if (ui->programme_radio_1->isChecked() && ui->programme_radio_2->isChecked()){

       // resultat = QString::number(solde+montant);

        //    query.prepare("UPDATE programme SET solde = " + resultat + " WHERE idProgramme = "+ stkSplited.at(0));
         //   query.exec();

            query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idProgramme)"
                            "VALUES (?,?,?,?,?,?)");
                  query.addBindValue(nom);
                  query.addBindValue(montant);
                  query.addBindValue(description);
                   query.addBindValue(QString::fromStdString(date));
                  query.addBindValue(1);
                  query.addBindValue(stkSplited.at(0));
             query.exec();




            ------------------------------------------------------------------------------------------


         //resultat = QString::number(solde2-montant);

           //  query.prepare("UPDATE programme SET solde = " + resultat + " WHERE idProgramme = "+ stkSplited2.at(0));
          //   query.exec();

             query.prepare("INSERT INTO transactions (nom,montant,description,annee,idType,idProgramme)"
                             "VALUES (?,?,?,?,?,?)");
                   query.addBindValue(nom);
                   query.addBindValue(montant);
                   query.addBindValue(description);
                    query.addBindValue(QString::fromStdString(date));
                   query.addBindValue(2);
                   query.addBindValue(stkSplited2.at(0));
              query.exec();

    }
*/



    art.~Article();
    cred.~Credit();
    dep.~Frais();
    init.~Budget();
    actuel.~Budget();
     close();

}

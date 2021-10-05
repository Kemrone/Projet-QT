#include "avis.h"
#include "ui_avis.h"
#include "mainwindow.h"
#include "connexion.h"
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

Avis::Avis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Avis)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    Connexion con;
    con.Connecter();
    QString res;

    QSqlQuery query;

    query.prepare("SELECT idFournisseur,nom FROM fournisseur");
    query.exec();
    while(query.next()){
        res = query.value(0).toString() + " | " + query.value(1).toString() ;
        ui->comboBoxFournisesur->addItem(res);
    }


    ui->radioButton_1->setAutoExclusive(false);
    ui->radioButton_2->setAutoExclusive(false);
    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_4->setAutoExclusive(false);
    ui->radioButton_5->setAutoExclusive(false);
}

Avis::~Avis()
{
    delete ui;
}



void Avis::on_menu_clicked()
{
    hide();
parentWidget()->show();
}

void Avis::on_radioButton_1_clicked()
{
    ui->radioButton_1->setChecked(true);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(false);
    ui->radioButton_5->setChecked(false);
}

void Avis::on_radioButton_2_clicked()
{
    ui->radioButton_1->setChecked(true);
    ui->radioButton_2->setChecked(true);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(false);
    ui->radioButton_5->setChecked(false);
}

void Avis::on_radioButton_3_clicked()
{
    ui->radioButton_1->setChecked(true);
    ui->radioButton_2->setChecked(true);
    ui->radioButton_3->setChecked(true);
    ui->radioButton_4->setChecked(false);
    ui->radioButton_5->setChecked(false);
}

void Avis::on_radioButton_4_clicked()
{
    ui->radioButton_1->setChecked(true);
    ui->radioButton_2->setChecked(true);
    ui->radioButton_3->setChecked(true);
    ui->radioButton_4->setChecked(true);
    ui->radioButton_5->setChecked(false);
}

void Avis::on_radioButton_5_clicked()
{
    ui->radioButton_1->setChecked(true);
    ui->radioButton_2->setChecked(true);
    ui->radioButton_3->setChecked(true);
    ui->radioButton_4->setChecked(true);
    ui->radioButton_5->setChecked(true);
}

void Avis::on_comboBoxFournisesur_currentTextChanged(const QString &arg1)
{
    if(arg1 == ""){

    }
    else{
         QString  id =   ui->comboBoxFournisesur->currentText();
        QStringList idSplited = id.split('|');
        id = idSplited.at(0);
        QSqlQuery query;
        double res =0;
        int count =0;
        query.prepare("SELECT note FROM avis WHERE idFournisseur = " + id);
        query.exec();
        while(query.next()){
            count++;
            res = res + query.value(0).toDouble();
        }
        res = res/count;
        ui->labelNote->setText("Avg : " + QString::number(res));
    }
}

void Avis::on_okButton_clicked()
{
    QString  id =   ui->comboBoxFournisesur->currentText();
     QSqlQuery query;
   QStringList idSplited = id.split('|');
   id = idSplited.at(0);


    if(ui->radioButton_1->isChecked() && ui->radioButton_2->isChecked()==false){
       query.prepare("INSERT INTO avis (description,note,idFournisseur)"
                                 "VALUES (?,?,?)");
       query.addBindValue(ui->txt_com->toPlainText());
       query.addBindValue(1);
       query.addBindValue(idSplited.at(0));
       query.exec();
    }

    if(ui->radioButton_2->isChecked() && ui->radioButton_3->isChecked()==false){
        query.prepare("INSERT INTO avis (description,note,idFournisseur)"
                                 "VALUES (?,?,?)");
        query.addBindValue(ui->txt_com->toPlainText());
        query.addBindValue(2);
        query.addBindValue(idSplited.at(0));
        query.exec();
    }

    if(ui->radioButton_3->isChecked() && ui->radioButton_4->isChecked()==false){
       query.prepare("INSERT INTO avis (description,note,idFournisseur)"
                                 "VALUES (?,?,?)");
       query.addBindValue(ui->txt_com->toPlainText());
       query.addBindValue(3);
       query.addBindValue(idSplited.at(0));
       query.exec();
    }

    if(ui->radioButton_4->isChecked() && ui->radioButton_5->isChecked()==false){
       query.prepare("INSERT INTO avis (description,nte,idFournisseur)"
                                 "VALUES (?,?,?)");
       query.addBindValue(ui->txt_com->toPlainText());
       query.addBindValue(4);
       query.addBindValue(idSplited.at(0));
       query.exec();
    }

    if(ui->radioButton_5->isChecked()){
      query.prepare("INSERT INTO avis (description,note,idFournisseur)"
                                 "VALUES (?,?,?)");
      query.addBindValue(ui->txt_com->toPlainText());
      query.addBindValue(5);
      query.addBindValue(idSplited.at(0));
      query.exec();
    }

    QMessageBox::information(this,"Done","Avis enregistré");
    hide();
    parentWidget()->show();
}

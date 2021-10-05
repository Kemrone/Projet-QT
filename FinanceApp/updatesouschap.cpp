#include "updatesouschap.h"
#include "ui_updatesouschap.h"
#include "connexion.h"
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

UpdateSousChap::UpdateSousChap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateSousChap)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    Connexion con;
    con.Connecter();

    QSqlQuery query;
    QString res;
    query.prepare("SELECT idChapitre,nom FROM chapitre");
    query.exec();
    while(query.next()){
        res = query.value(0).toString() + " | " + query.value(1).toString();
        ui->comboBoxChap->addItem(res);
    }

    query.prepare("SELECT idSousChap,nom from sous_chapitre");
    query.exec();
    while(query.next()){
        res = query.value(0).toString() + " | " + query.value(1).toString();
        ui->comboBoxSousChap->addItem(res);
    }
}

UpdateSousChap::~UpdateSousChap()
{
    delete ui;
}

void UpdateSousChap::on_okButton_clicked()
{
    QSqlQuery query;
    QString idChap = ui->comboBoxChap->currentText();
     QStringList idChapSplited = idChap.split('|');
    QString  id =   ui->comboBoxSousChap->currentText();
    QStringList idSplited = id.split('|');


    query.prepare("UPDATE sous_chapitre SET nom = '" + ui->txt_nom->toPlainText() + "' WHERE idSousChap = " + idSplited.at(0));
    query.exec();


    query.prepare("UPDATE sous_chapitre  SET description = '" + ui->txt_description->toPlainText() + "' WHERE idSousChap = " + idSplited.at(0));
    query.exec();


    query.prepare("UPDATE sous_chapitre  SET idChapitre = '" + idChapSplited.at(0) + "' WHERE idSousChap = " + idSplited.at(0));
    query.exec();

    QMessageBox::information(this,"Done","Modifications effectuées");

    hide();

}

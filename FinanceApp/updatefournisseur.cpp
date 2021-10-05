#include "updatefournisseur.h"
#include "ui_updatefournisseur.h"
#include "connexion.h"
#include <QPointer>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

UpdateFournisseur::UpdateFournisseur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateFournisseur)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);


    Connexion con;
    con.Connecter();

    QSqlQuery query;
    QString res;
    query.prepare("SELECT idFournisseur,nom FROM fournisseur");
    query.exec();
    while(query.next()){
        res = query.value(0).toString() + " | " + query.value(1).toString();
        ui->comboBoxFournisseur->addItem(res);
    }


}

UpdateFournisseur::~UpdateFournisseur()
{
    delete ui;
}

void UpdateFournisseur::on_okButton_clicked()
{
    QSqlQuery query;
    QString  id =   ui->comboBoxFournisseur->currentText();
    QStringList idSplited = id.split('|');


    query.prepare("UPDATE fournisseur SET nom = '" + ui->txt_nom->toPlainText() + "' WHERE idFournisseur = " + idSplited.at(0));
    query.exec();


    query.prepare("UPDATE fournisseur SET raisonSociale = '" + ui->txt_RS->toPlainText() + "' WHERE idFournisseur = " + idSplited.at(0));
    query.exec();


    query.prepare("UPDATE fournisseur SET domaine = '" +ui->txt_domaine->toPlainText() + "' WHERE idFournisseur = " + idSplited.at(0));
    query.exec();

    QMessageBox::information(this,"Done","Modifications effectuées");

    hide();
}

#include "updatechapitre.h"
#include "ui_updatechapitre.h"
#include "connexion.h"
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

UpdateChapitre::UpdateChapitre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateChapitre)
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
}

UpdateChapitre::~UpdateChapitre()
{
    delete ui;
}

void UpdateChapitre::on_okButton_clicked()
{
    QSqlQuery query;
    QString  id =   ui->comboBoxChap->currentText();
    QStringList idSplited = id.split('|');


    query.prepare("UPDATE chapitre SET nom = '" + ui->txt_nom->toPlainText() + "' WHERE idchapitre = " + idSplited.at(0));
    query.exec();


    query.prepare("UPDATE chapitre SET description = '" + ui->txt_description->toPlainText() + "' WHERE idChapitre = " + idSplited.at(0));
    query.exec();

    QMessageBox::information(this,"Done","Modifications effectuées");

    hide();

}

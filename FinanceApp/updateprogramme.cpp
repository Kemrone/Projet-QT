#include "updateprogramme.h"
#include "ui_updateprogramme.h"
#include "connexion.h"
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>


UpdateProgramme::UpdateProgramme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateProgramme)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    Connexion con;
    con.Connecter();

    QSqlQuery query;
    QString res;
    query.prepare("SELECT idArticle,nom FROM article");
    query.exec();
    while(query.next()){
        res = query.value(0).toString() + " | " + query.value(1).toString();
        ui->comboBoxArticle->addItem(res);
    }
    query.prepare("SELECT idProgramme,nom FROM programme");
    query.exec();
    while(query.next()){
        res = query.value(0).toString() + " | " + query.value(1).toString();
        ui->comboBoxProgramme->addItem(res);

    }
}

UpdateProgramme::~UpdateProgramme()
{
    delete ui;


}

void UpdateProgramme::on_okButton_clicked()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%Y",timeinfo);
    std::string date(buffer);


    QSqlQuery query;
    QString  idProg =   ui->comboBoxProgramme->currentText();
    QStringList idProgSplited = idProg.split('|');
    QString  id =   ui->comboBoxArticle->currentText();
    QStringList idSplited = id.split('|');





        query.prepare("UPDATE programme SET nom = '" + ui->txt_nom->toPlainText() + "' WHERE idProgramme = " + idProgSplited.at(0));
        query.exec();


        query.prepare("UPDATE programme SET idArticle = '" + idSplited.at(0) + "' WHERE idProgramme = " + idProgSplited.at(0));
        query.exec();


        query.prepare("UPDATE programme SET solde = " +ui->txt_solde->toPlainText() + " WHERE idProgramme = " + idProgSplited.at(0));
        query.exec();


        query.prepare("UPDATE programme SET budgetInitial = " +ui->txt_solde_init->toPlainText() + " WHERE idProgramme = " + idProgSplited.at(0));
        query.exec();


        query.prepare("UPDATE programme SET derniereMaj = " + QString::fromStdString(date) + " WHERE idProgramme = " + idProgSplited.at(0));
        query.exec();


    QMessageBox::information(this,"Done","Modifications effectuées");

    hide();


}

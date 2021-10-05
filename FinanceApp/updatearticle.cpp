#include "updatearticle.h"
#include "ui_updatearticle.h"
#include "connexion.h"
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

UpdateArticle::UpdateArticle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateArticle)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    Connexion con;
    con.Connecter();

    QSqlQuery query;
    QString res;
    query.prepare("SELECT idSousChap,nom FROM sous_chapitre");
    query.exec();
    while(query.next()){
        res = query.value(0).toString() + " | " + query.value(1).toString();
        ui->comboBoxSousChap->addItem(res);
    }
    query.prepare("SELECT idArticle,nom FROM article");
    query.exec();
    while(query.next()){
        res = query.value(0).toString() + " | " + query.value(1).toString();
        ui->comboBoxArticle->addItem(res);

    }
}

UpdateArticle::~UpdateArticle()
{
    delete ui;
}

void UpdateArticle::on_okButton_clicked()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%Y",timeinfo);
    std::string date(buffer);


    QSqlQuery query;
    QString  idArt =   ui->comboBoxArticle->currentText();
    QStringList idArtSplited = idArt.split('|');
    QString  id =   ui->comboBoxSousChap->currentText();
    QStringList idSplited = id.split('|');





        query.prepare("UPDATE article SET nom = " + ui->txt_nom->toPlainText() + " WHERE idArticle = " + idArtSplited.at(0));
        query.exec();


        query.prepare("UPDATE article SET idSousChapitre = " + idSplited.at(0) + " WHERE idArticle = " + idArtSplited.at(0));
        query.exec();


        query.prepare("UPDATE article SET solde = " +ui->txt_solde->toPlainText() + " WHERE idArticle = " + idArtSplited.at(0));
        query.exec();


        query.prepare("UPDATE article SET budgetInitial = " +ui->txt_solde_init->toPlainText() + " WHERE idArticle = " + idArtSplited.at(0));
        query.exec();


        query.prepare("UPDATE article SET derniereMaj = " + QString::fromStdString(date) + " WHERE idArticle = " + idArtSplited.at(0));
        query.exec();


    QMessageBox::information(this,"Done","Modifications effectuées");

    hide();


}

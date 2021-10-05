#include "ajoutarticle.h"
#include "ui_ajoutarticle.h"
#include "connexion.h"
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

AjoutArticle::AjoutArticle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutArticle)
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




    ui->txt_solde->setText("0");
}

AjoutArticle::~AjoutArticle()
{
    delete ui;
}

void AjoutArticle::on_okButton_clicked()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%Y",timeinfo);
    std::string date(buffer);


    QSqlQuery query;
    QString  id =   ui->comboBoxSousChap->currentText();
    QStringList idSplited = id.split('|');


    query.prepare("INSERT INTO article (nom,solde,budgetInitial,derniereMaj,idSousChapitre)"
                    "VALUES (?,?,?,?,?)");
          query.addBindValue(ui->txt_nom->toPlainText());
          query.addBindValue(ui->txt_solde->toPlainText().toDouble());
          query.addBindValue(ui->txt_solde->toPlainText());
          query.addBindValue(QString::fromStdString(date));
          query.addBindValue(idSplited.at(0));
    query.exec();

    QMessageBox::information(this,"Done","Ajout effectué");

    hide();


}



void AjoutArticle::on_txt_solde_textChanged()
{
    if(ui->txt_solde->toPlainText() == ""){
        ui->txt_solde->setText("0");
    }
}

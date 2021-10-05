#include "ajoutprogramme.h"
#include "ui_ajoutprogramme.h"
#include "connexion.h"
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

AjoutProgramme::AjoutProgramme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutProgramme)
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

     ui->txt_solde->setText("0");

}

AjoutProgramme::~AjoutProgramme()
{
    delete ui;
}

void AjoutProgramme::on_okButton_clicked()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%Y",timeinfo);
    std::string date(buffer);


    QSqlQuery query;
    QString  id =   ui->comboBoxArticle->currentText();
    QStringList idSplited = id.split('|');


    query.prepare("INSERT INTO programme (nom,solde,budgetInitial,derniereMaj,idArticle)"
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

void AjoutProgramme::on_txt_solde_textChanged()
{
    if(ui->txt_solde->toPlainText() == ""){
        ui->txt_solde->setText("0");
    }
}

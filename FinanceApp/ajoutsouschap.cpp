#include "ajoutsouschap.h"
#include "ui_ajoutsouschap.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "connexion.h"

AjoutSousChap::AjoutSousChap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutSousChap)
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

AjoutSousChap::~AjoutSousChap()
{
    delete ui;
}

void AjoutSousChap::on_okButton_clicked()
{
    QSqlQuery query;
    QString  id =   ui->comboBoxChap->currentText();
    QStringList idSplited = id.split('|');


    query.prepare("INSERT INTO sous_chapitre (nom,description,idChapitre)"
                    "VALUES (?,?,?)");
          query.addBindValue(ui->txt_nom->toPlainText());
          query.addBindValue(ui->txt_description->toPlainText());
          query.addBindValue(idSplited.at(0));
    query.exec();

    QMessageBox::information(this,"Done","Ajout effectué");

    hide();
}

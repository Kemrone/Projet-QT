#include "ajoutfournisseur.h"
#include "ui_ajoutfournisseur.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "connexion.h"

AjoutFournisseur::AjoutFournisseur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutFournisseur)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

AjoutFournisseur::~AjoutFournisseur()
{
    delete ui;
}

void AjoutFournisseur::on_okButton_clicked()
{
    Connexion con;
    con.Connecter();

    QSqlQuery query;



    query.prepare("INSERT INTO fournisseur (nom,raisonSociale,domaine)"
                    "VALUES (?,?,?)");
          query.addBindValue(ui->txt_nom->toPlainText());
          query.addBindValue(ui->txt_RS->toPlainText());
          query.addBindValue(ui->txt_domaine->toPlainText());
    query.exec();

    QMessageBox::information(this,"Done","Ajout effectué");

    hide();

}

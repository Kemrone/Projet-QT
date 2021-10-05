#include "ajoutchapitre.h"
#include "ui_ajoutchapitre.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "connexion.h"

AjoutChapitre::AjoutChapitre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutChapitre)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

AjoutChapitre::~AjoutChapitre()
{
    delete ui;
}

void AjoutChapitre::on_okButton_clicked()
{
    Connexion con;
    con.Connecter();

    QSqlQuery query;



    query.prepare("INSERT INTO chapitre (nom,description)"
                    "VALUES (?,?)");
          query.addBindValue(ui->txt_nom->toPlainText());
          query.addBindValue(ui->txt_description->toPlainText());
    query.exec();

    QMessageBox::information(this,"Done","Ajout effectué");

    hide();
}

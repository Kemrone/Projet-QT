#include "ajouterchapitre.h"
#include "ui_ajouterchapitre.h"

AJouterChapitre::AJouterChapitre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AJouterChapitre)
{
    ui->setupUi(this);
}

AJouterChapitre::~AJouterChapitre()
{
    delete ui;
}

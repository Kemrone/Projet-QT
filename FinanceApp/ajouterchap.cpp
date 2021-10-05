#include "ajouterchap.h"
#include "ui_ajouterchap.h"

AjouterChap::AjouterChap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterChap)
{
    ui->setupUi(this);
}

AjouterChap::~AjouterChap()
{
    delete ui;
}

#include "choixnomenc.h"
#include "ui_choixnomenc.h"

ChoixNomenc::ChoixNomenc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoixNomenc)
{
    ui->setupUi(this);
}

ChoixNomenc::~ChoixNomenc()
{
    delete ui;
}

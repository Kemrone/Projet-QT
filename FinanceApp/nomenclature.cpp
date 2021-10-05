#include "nomenclature.h"
#include "ui_nomenclature.h"

Nomenclature::Nomenclature(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nomenclature)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

Nomenclature::~Nomenclature()
{
    delete ui;
}

void Nomenclature::on_listButton_clicked()
{
    hide();
    liste = new ListeElements(this);
    liste->show();
}

void Nomenclature::on_elemButton_clicked()
{

    hide();
    ajout = new AjoutElements(this);
    ajout->show();
}

void Nomenclature::on_menuButton_clicked()
{
    hide();
    parentWidget()->show();
}

#include "transaction.h"
#include "ui_transaction.h"
#include "dotation.h"
#include "depense.h"
#include "transfert.h"

Transaction::Transaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transaction)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

Transaction::~Transaction()
{
    delete ui;
}

void Transaction::on_menu_clicked()
{
    hide();
parentWidget()->show();
}


void Transaction::on_dotation_clicked()
{

    dot = new dotation(this);
    dot -> show();

}


void Transaction::on_depense_clicked()
{
    dep = new Depense(this);
    dep -> show();

}

void Transaction::on_transfert_clicked()
{

    transf = new Transfert(this);
    transf -> show();
}

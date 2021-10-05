#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transaction.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Page d'Accueil");



}

MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_avis_menu_clicked()
{
    hide();
    avis = new Avis(this);
    avis->show();
}

void MainWindow::on_quitter_menu_clicked()
{
    close();

}

void MainWindow::on_transaction_menu__clicked()
{
    hide();
    trans = new Transaction(this);
    trans ->show();
}

void MainWindow::on_nomenclature_menu_clicked()
{
    hide();
    nomenclature = new Nomenclature(this);
    nomenclature->show();
}

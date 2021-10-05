#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "transaction.h"
#include "avis.h"
#include "nomenclature.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_avis_menu_clicked();

    void on_quitter_menu_clicked();

    void on_transaction_menu__clicked();

    void on_nomenclature_menu_clicked();

private:
    Ui::MainWindow *ui;
    Transaction *trans;
    Avis *avis;
    Nomenclature *nomenclature;
};
#endif // MAINWINDOW_H

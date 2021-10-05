#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <QDialog>
#include "dotation.h"
#include "depense.h"
#include "transfert.h"
namespace Ui {
class Transaction;
}

class Transaction : public QDialog
{
    Q_OBJECT

public:
    explicit Transaction(QWidget *parent = nullptr);
    ~Transaction();

private slots:
    void on_menu_clicked();
    void on_dotation_clicked();
    void on_transfert_clicked();
    void on_depense_clicked();

private:
    Ui::Transaction *ui;
    dotation *dot;
    Depense *dep;
    Transfert *transf;

};

#endif // TRANSACTION_H

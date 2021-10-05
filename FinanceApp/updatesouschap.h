#ifndef UPDATESOUSCHAP_H
#define UPDATESOUSCHAP_H

#include <QDialog>

namespace Ui {
class UpdateSousChap;
}

class UpdateSousChap : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateSousChap(QWidget *parent = nullptr);
    ~UpdateSousChap();

private slots:
    void on_okButton_clicked();

private:
    Ui::UpdateSousChap *ui;
};

#endif // UPDATESOUSCHAP_H

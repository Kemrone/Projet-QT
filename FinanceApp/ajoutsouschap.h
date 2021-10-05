#ifndef AJOUTSOUSCHAP_H
#define AJOUTSOUSCHAP_H

#include <QDialog>

namespace Ui {
class AjoutSousChap;
}

class AjoutSousChap : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutSousChap(QWidget *parent = nullptr);
    ~AjoutSousChap();

private slots:
    void on_okButton_clicked();

private:
    Ui::AjoutSousChap *ui;
};

#endif // AJOUTSOUSCHAP_H

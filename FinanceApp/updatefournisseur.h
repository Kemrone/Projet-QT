#ifndef UPDATEFOURNISSEUR_H
#define UPDATEFOURNISSEUR_H

#include <QDialog>

namespace Ui {
class UpdateFournisseur;
}

class UpdateFournisseur : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateFournisseur(QWidget *parent = nullptr);
    ~UpdateFournisseur();

private slots:
    void on_okButton_clicked();

private:
    Ui::UpdateFournisseur *ui;
};

#endif // UPDATEFOURNISSEUR_H

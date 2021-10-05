#ifndef AJOUTFOURNISSEUR_H
#define AJOUTFOURNISSEUR_H

#include <QDialog>

namespace Ui {
class AjoutFournisseur;
}

class AjoutFournisseur : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutFournisseur(QWidget *parent = nullptr);
    ~AjoutFournisseur();

private slots:
    void on_okButton_clicked();

private:
    Ui::AjoutFournisseur *ui;
};

#endif // AJOUTFOURNISSEUR_H

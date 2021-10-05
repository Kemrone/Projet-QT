#ifndef NOMENCLATURE_H
#define NOMENCLATURE_H

#include "listeelements.h"
#include "ajoutelements.h"
#include <QDialog>

namespace Ui {
class Nomenclature;
}

class Nomenclature : public QDialog
{
    Q_OBJECT

public:
    explicit Nomenclature(QWidget *parent = nullptr);
    ~Nomenclature();

private slots:
    void on_listButton_clicked();

    void on_elemButton_clicked();

    void on_menuButton_clicked();

private:
    Ui::Nomenclature *ui;
    ListeElements *liste;
    AjoutElements *ajout;
};

#endif // NOMENCLATURE_H

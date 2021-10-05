#ifndef AJOUTERCHAP_H
#define AJOUTERCHAP_H

#include <QDialog>

namespace Ui {
class AjouterChap;
}

class AjouterChap : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterChap(QWidget *parent = nullptr);
    ~AjouterChap();

private:
    Ui::AjouterChap *ui;
};

#endif // AJOUTERCHAP_H

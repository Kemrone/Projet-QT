#ifndef AJOUTPROGRAMME_H
#define AJOUTPROGRAMME_H

#include <QDialog>

namespace Ui {
class AjoutProgramme;
}

class AjoutProgramme : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutProgramme(QWidget *parent = nullptr);
    ~AjoutProgramme();

private slots:
    void on_okButton_clicked();

    void on_txt_solde_textChanged();

private:
    Ui::AjoutProgramme *ui;
};

#endif // AJOUTPROGRAMME_H

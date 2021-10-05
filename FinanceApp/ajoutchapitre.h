#ifndef AJOUTCHAPITRE_H
#define AJOUTCHAPITRE_H

#include <QDialog>

namespace Ui {
class AjoutChapitre;
}

class AjoutChapitre : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutChapitre(QWidget *parent = nullptr);
    ~AjoutChapitre();

private slots:
    void on_okButton_clicked();

private:
    Ui::AjoutChapitre *ui;
};

#endif // AJOUTCHAPITRE_H

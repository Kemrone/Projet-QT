#ifndef UPDATECHAPITRE_H
#define UPDATECHAPITRE_H

#include <QDialog>

namespace Ui {
class UpdateChapitre;
}

class UpdateChapitre : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateChapitre(QWidget *parent = nullptr);
    ~UpdateChapitre();

private slots:
    void on_okButton_clicked();

private:
    Ui::UpdateChapitre *ui;
};

#endif // UPDATECHAPITRE_H

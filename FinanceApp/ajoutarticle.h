#ifndef AJOUTARTICLE_H
#define AJOUTARTICLE_H

#include <QDialog>

namespace Ui {
class AjoutArticle;
}

class AjoutArticle : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutArticle(QWidget *parent = nullptr);
    ~AjoutArticle();

private slots:
    void on_okButton_clicked();


    void on_txt_solde_textChanged();

private:
    Ui::AjoutArticle *ui;
};

#endif // AJOUTARTICLE_H

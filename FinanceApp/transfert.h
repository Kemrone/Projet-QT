#ifndef TRANSFERT_H
#define TRANSFERT_H

#include <QDialog>
#include "printview.h"

namespace Ui {
class Transfert;
}

class Transfert : public QDialog
{
    Q_OBJECT

public:
    explicit Transfert(QWidget *parent = nullptr);
    ~Transfert();

private slots:
    void on_article_radio_1_clicked();

    void on_article_radio_2_clicked();

    void on_programme_radio_1_clicked();

    void on_programme_radio_2_clicked();

    void on_comboBox_article_currentTextChanged(const QString &arg1);

    void on_comboBox_article_2_currentTextChanged(const QString &arg1);

    void on_OK_Button_clicked();

private:
    Ui::Transfert *ui;
};

#endif // TRANSFERT_H

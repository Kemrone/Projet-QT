#ifndef DOTATION_H
#define DOTATION_H

#include <QDialog>
#include "connexion.h"
#include "printview.h"

namespace Ui {
class dotation;
}

class dotation : public QDialog
{
    Q_OBJECT
    //QSharedPointer <PrintView> recap;

public:
    explicit dotation(QWidget *parent = nullptr);
    ~dotation();

private slots:

    void on_OK_Button_clicked();

    void on_comboBox_article_currentTextChanged(const QString &arg1);

    void on_programme_radio_clicked();

    void on_article_radio_clicked();

signals:
    void sendMessage(const QString &msg);

private:
    Ui::dotation *ui;




};

#endif // DOTATION_H

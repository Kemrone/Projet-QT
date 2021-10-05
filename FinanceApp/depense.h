#ifndef DEPENSE_H
#define DEPENSE_H

#include <QDialog>

namespace Ui {
class Depense;
}

class Depense : public QDialog
{
    Q_OBJECT

public:
    explicit Depense(QWidget *parent = nullptr);
    ~Depense();

private slots:
    void on_OK_Button_clicked();

    void on_article_radio_clicked();

    void on_programme_radio_clicked();

    void on_comboBox_article_currentTextChanged(const QString &arg1);

private:
    Ui::Depense *ui;
};

#endif // DEPENSE_H

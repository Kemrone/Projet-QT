#ifndef AVIS_H
#define AVIS_H
#include <QDialog>
#include <QRadioButton>

namespace Ui {
class Avis;
}

class Avis : public QDialog
{
    Q_OBJECT

public:
    explicit Avis(QWidget *parent = nullptr);
    ~Avis();

private slots:
    void on_menu_clicked();




    void on_radioButton_1_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_comboBoxFournisesur_currentTextChanged(const QString &arg1);

    void on_okButton_clicked();

private:
    Ui::Avis *ui;

};

#endif // AVIS_H

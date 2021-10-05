#ifndef DOTA_H
#define DOTA_H

#include <QDialog>

namespace Ui {
class Dota;
}

class Dota : public QDialog
{
    Q_OBJECT

public:
    explicit Dota(QWidget *parent = nullptr);
    ~Dota();

private slots:
    void on_OK_Button_clicked();

private:
    Ui::Dota *ui;
};

#endif // DOTA_H

#ifndef UPDATEPROGRAMME_H
#define UPDATEPROGRAMME_H

#include <QDialog>

namespace Ui {
class UpdateProgramme;
}

class UpdateProgramme : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateProgramme(QWidget *parent = nullptr);
    ~UpdateProgramme();

private slots:
    void on_okButton_clicked();

private:
    Ui::UpdateProgramme *ui;
};

#endif // UPDATEPROGRAMME_H

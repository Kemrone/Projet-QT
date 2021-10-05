#ifndef PRINTVIEW_H
#define PRINTVIEW_H

#include <QDialog>
#include "article.h"
#include "operations.h"

namespace Ui {
class PrintView;
}

class PrintView : public QDialog
{
    Q_OBJECT

public:
   Article getArt();
   void setArt(Article art);
   Operations getOpe();
   void setOpe(Operations ope);


    void receiveTitle(const QString &title);
    void receiveMessage(const QString &msg);
    explicit PrintView(QWidget *parent = nullptr);
    ~PrintView();

private slots:


    void on_QuitterButton_clicked();

    void on_ImprimerButton_clicked();

private:
    Ui::PrintView *ui;
    Article art;
    Operations ope;


};

#endif // PRINTVIEW_H

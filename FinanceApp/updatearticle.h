#ifndef UPDATEARTICLE_H
#define UPDATEARTICLE_H

#include <QDialog>

namespace Ui {
class UpdateArticle;
}

class UpdateArticle : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateArticle(QWidget *parent = nullptr);
    ~UpdateArticle();

private slots:
    void on_okButton_clicked();

private:
    Ui::UpdateArticle *ui;
};

#endif // UPDATEARTICLE_H

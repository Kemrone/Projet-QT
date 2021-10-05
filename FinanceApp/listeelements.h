#ifndef LISTEELEMENTS_H
#define LISTEELEMENTS_H

#include <QDialog>

namespace Ui {
class ListeElements;
}

class ListeElements : public QDialog
{
    Q_OBJECT

public:
    explicit ListeElements(QWidget *parent = nullptr);
    ~ListeElements();

private slots:
    void on_ChapComboBox_currentIndexChanged(const QString &arg1);

    void on_ChapComboBox_currentTextChanged(const QString &arg1);

    void on_PreviousButton_clicked();

    void on_SousChapComboBox_currentTextChanged(const QString &arg1);

    void on_articleList_clicked(const QModelIndex &index);



    void on_printButton_clicked();

    void on_deleteChapButton_clicked();

    void on_deleteSousChapButton_clicked();

    void on_deleteArticleButton_clicked();

    void on_deleteProgButton_clicked();

    void on_progList_clicked(const QModelIndex &index);

private:
    Ui::ListeElements *ui;
};

#endif // LISTEELEMENTS_H

#ifndef AJOUTELEMENTS_H
#define AJOUTELEMENTS_H

#include <QDialog>
#include "ajoutarticle.h"
#include "ajoutchapitre.h"
#include "ajoutfournisseur.h"
#include "ajoutprogramme.h"
#include "ajoutsouschap.h"
#include "updatearticle.h"
#include "updatechapitre.h"
#include "updatefournisseur.h"
#include "updateprogramme.h"
#include "updatesouschap.h"

namespace Ui {
class AjoutElements;
}

class AjoutElements : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutElements(QWidget *parent = nullptr);
    ~AjoutElements();

private slots:

    void on_previousButton_clicked();

    void on_addChapButton_clicked();

    void on_updateArticleButton_clicked();

    void on_addArticleButton_clicked();

    void on_addFournisseur_clicked();

    void on_updateFournisseur_clicked();

    void on_addSousChapButton_clicked();

    void on_addProgrammeButton_clicked();

    void on_updateProgrammeButton_clicked();

    void on_updateSousChapButton_clicked();

    void on_updateChapButton_clicked();

private:
    Ui::AjoutElements *ui;
    AjoutChapitre * chap;
    UpdateChapitre * upChap;
    AjoutArticle * art;
    UpdateArticle * upArt;
    AjoutFournisseur * fourn;
    UpdateFournisseur * upFourn;
    AjoutSousChap * sousChap;
    UpdateSousChap * upSousChap;
    AjoutProgramme * prog;
    UpdateProgramme * upProg;
};

#endif // AJOUTELEMENTS_H

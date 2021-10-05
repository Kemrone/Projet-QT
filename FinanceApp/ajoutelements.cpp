#include "ajoutelements.h"
#include "ui_ajoutelements.h"

AjoutElements::AjoutElements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutElements)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

AjoutElements::~AjoutElements()
{
    delete ui;
}

void AjoutElements::on_previousButton_clicked()
{
    hide();
    parentWidget()->show();
}



void AjoutElements::on_addChapButton_clicked()
{
    chap = new AjoutChapitre(this);
    chap->show();

}

void AjoutElements::on_updateArticleButton_clicked()
{
    upArt = new UpdateArticle(this);
    upArt->show();
}

void AjoutElements::on_addArticleButton_clicked()
{
    art = new AjoutArticle(this);
    art->show();
}

void AjoutElements::on_addFournisseur_clicked()
{
    fourn = new AjoutFournisseur(this);
    fourn->show();
}

void AjoutElements::on_updateFournisseur_clicked()
{
    upFourn = new UpdateFournisseur(this);
    upFourn->show();
}

void AjoutElements::on_addSousChapButton_clicked()
{
    sousChap = new AjoutSousChap(this);
    sousChap->show();
}

void AjoutElements::on_addProgrammeButton_clicked()
{
    prog = new AjoutProgramme(this);
    prog->show();
}

void AjoutElements::on_updateProgrammeButton_clicked()
{
    upProg = new UpdateProgramme(this);
    upProg->show();
}

void AjoutElements::on_updateSousChapButton_clicked()
{
    upSousChap = new UpdateSousChap(this);
    upSousChap->show();
}

void AjoutElements::on_updateChapButton_clicked()
{
    upChap = new UpdateChapitre(this);
    upChap->show();
}

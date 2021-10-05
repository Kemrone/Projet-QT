#include "article.h"
#include <string>
#include "budget.h"


Article::Article(){

}


Article::Article(std::string nom) : nom(nom)
{

     budgetInitial.putDescription("Budget Initial");
     budgetInitial.putMontant(0);
     budgetSup.putDescription("Budget Actuel");
     budgetSup.putMontant(0);
}

Article::~Article()
{
    //dtor
}

Budget Article::getBudgetInitial(){
    return this ->budgetInitial;
}

void Article::putBudgetInitial(Budget b){
    budgetInitial = b;
}

Budget Article::getBudgetSup(){
    return this ->budgetSup;
}

void Article::putBudgetSup(Budget b){
    budgetSup = b;
}

std::string Article::getNom(){
    return this -> nom;
}

void Article::setNom(std::string n){
    nom =n;
}

int Article::getId(){
    return this ->id;
}

void Article::setId(int id){
    this->id = id;
}

int Article::getFk(){
    return this ->fk;
}

void Article::setFk(int fk){
    this->fk = fk;
}


int Article::getUpdate(){
    return this ->update;
}

void Article::setUpdate(int update){
    this->update = update;
}

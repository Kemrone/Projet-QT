#include "operations.h"
#include <budget.h>
#include <article.h>
#include <iostream>
#include <ctime>




Operations::Operations(int id, std::string nom){
    this->id = id;
    this->nom = nom;
}

Operations::Operations(){

}


Operations::~Operations()
{
    //dtor
}


int Operations::getId(){
    return this->id;
}

void Operations::setId(int id){
   this-> id = id;
}

void Operations::setNom(std::string nom){
   this-> nom = nom;
}

std::string Operations::getNom(){
    return this->nom;
}

void Operations::setDescription(std::string description){
   this-> description = description;
}

std::string Operations::getDescription(){
    return this->description;
}


Credit :: Credit() {

}

Credit::~Credit(){

}

Frais::Frais()
{

}

Frais::~Frais(){

}

Transfert_Fond::Transfert_Fond(){

}

Transfert_Fond::~Transfert_Fond(){

}



void Credit::crediter(Article& a, double credit,int typeOpe){

time_t rawtime;
struct tm * timeinfo;
char buffer[80];

time (&rawtime);
timeinfo = localtime(&rawtime);

strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
std::string date(buffer);


    Budget x;
    x = a.getBudgetInitial();
    x.putMontant(credit);

    if( a.getBudgetInitial().getMontant() == 0 && typeOpe==1  ){
        x.putDate( date);
        a .putBudgetInitial(x);
        a .putBudgetSup(x);
    }
    else if (a.getBudgetInitial().getMontant() !=0)
{
    x= a.getBudgetSup();
    x.putDate("Derniere maj : " + date);
    x.putDescription("");
    x.putMontant(a.getBudgetSup().getMontant()+credit);
    a.putBudgetSup(x);
}

x.~Budget();

}


void Frais::depenser(Article& a, double debit){

time_t rawtime;
struct tm * timeinfo;
char buffer[80];

time (&rawtime);
timeinfo = localtime(&rawtime);

strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
std::string date(buffer);



    Budget x;
    x = a.getBudgetSup();
    x.putDescription("");
    cout<<"Budget de " << a.getNom() << ": "<<a.getBudgetSup().getMontant()<<endl;
    x.putMontant(a.getBudgetSup().getMontant() -debit);
    x.putDate(date);
    a.putBudgetSup(x);
    cout<<"Nouveau budget : "<<a.getBudgetSup().getMontant()<<endl;
}





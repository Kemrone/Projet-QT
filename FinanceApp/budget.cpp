#include "budget.h"
#include <string>
#include <iostream>

Budget :: Budget() : id(idSuivant++ ) {

}


int Budget::idSuivant = 0;

Budget::~Budget()
{
    //dtor
}



int Budget::getId(){
    return this -> id;
}



int Budget::getAnnee(){
    return this ->annee;
}

void Budget::putAnnee(int a){
    annee = a;
}

std::string Budget::getDate(){
    return date;
}

void Budget::putDate(std::string d){
    date = d;
}


std::string Budget::getDescription(){
    return description;
}

void Budget::putDescription(std::string d){
    description = d;
}

int Budget::getMontant(){
    return this -> montant;
}

void Budget::putMontant(int m){
    montant =m;
}

void Budget::afficherBudget(){
    std::cout<< "id : "  << getId()<< std::endl;
    std::cout<< "annee : "  << getAnnee() << std::endl;
    std::cout<< "date : "<< getDate() <<std::endl;
    std::cout<< "description :"<< getDescription() <<std::endl;
    std::cout<< "Montant : "<< getMontant() <<std::endl;

}

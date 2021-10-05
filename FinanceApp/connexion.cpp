#include "connexion.h"
#include <QtSql/QtSql>
#include <QSqlDatabase>



Connexion::Connexion()
{

}

Connexion::~Connexion(){

}


void Connexion::Connecter()
{

   db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("C:/Users/marc-eli/Desktop/prjt/ProjetL2/ProjetHemza/projetOk/BDD/projetFinance.sqlite");

    if(!db.open()){

    }




}




#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>

class Connexion
{
public:

    Connexion();
    void Connecter();
    void Deconnecter();
    ~Connexion();

private:

    QSqlDatabase db;



};

#endif // CONNEXION_H

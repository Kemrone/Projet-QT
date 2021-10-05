#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <iostream>
#include <article.h>


class Operations
{
public:
    Operations();
    Operations(int id, std::string nom);
    virtual ~Operations();
    void setId(int id);
    int getId();
    void setDescription(std::string nom);
    std::string getDescription();
    void setNom(std::string nom);
    std::string getNom();
    void setAnnee(int annee);
    int getAnnee();


protected:

private: int id;
         int annee;
         std::string description;
         std::string nom;
};

class Credit : public Operations{

  public:
        Credit();
        virtual ~Credit();
        void crediter(Article& a, double credit, int typeOpe);


    protected:

    private:

};


class Frais : public Operations{

  public:
      Frais();
      virtual ~Frais();
      void depenser(Article& a, double debit);

   protected:

   private:

};

class Transfert_Fond : public Operations{

    public:
        Transfert_Fond();
        virtual ~Transfert_Fond();
        void transfert(Article& a, Article& b, int montant);

};


#endif // OPERATIONS_H

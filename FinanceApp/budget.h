#ifndef BUDGET_H
#define BUDGET_H
#include <string>

class Budget
{
    public:
        Budget();
        Budget(int annee, std::string date);
        virtual ~Budget();
        int getId();
        int getAnnee();
        void putAnnee(int a);
        std::string getDate();
        void putDate(std::string d);
        std::string getDescription();
        void putDescription(std::string d);
        int getMontant();
        void putMontant(int m);
        void afficherBudget();


    protected:

    private:   int  id=0;
             static int idSuivant;
             int annee;
             std::string date;
             std::string description;
             int montant;
};





#endif // BUDGET_H

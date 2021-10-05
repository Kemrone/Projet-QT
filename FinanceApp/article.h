#ifndef ARTICLE_H
#define ARTICLE_H
#include <string>
#include <budget.h>
using namespace std;
class Article
{
    public:
        Article();
        Article(std::string nom);
        virtual ~Article();
        Budget getBudgetInitial();
        void putBudgetInitial(Budget b);
        Budget getBudgetSup();
        void putBudgetSup(Budget b);
        std::string getNom();
        void setNom(std::string n);
        int getId();
        void setId(int id);
        int getUpdate();
        void setUpdate(int update);
        int getFk();
        void setFk(int fk);


    protected:

    private: int id;
             int fk;
             int update;
             std::string nom;
             Budget budgetInitial;
             Budget budgetSup;
};

#endif // ARTICLE_H


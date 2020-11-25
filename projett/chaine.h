#ifndef CHAINE_H
#define CHAINE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class chaine
{

    QString type_produit;
    int reference,nb_machine;

public:
    chaine();
    chaine(QString,int,int);
    void setnb_machine(int nb)
    {
       nb_machine=nb;
    }
    int getnb_machine()
    {
        return nb_machine;
    }
    void setType_produit(QString t)
    {
        type_produit=t;
    }
    QString getType_produit()
    {
        return type_produit;
    }
    void setRef(int r)
    {
        reference=r;
    }
    int getRef()
    {
        return reference;
    }
    bool ajouter();
    QSqlQueryModel * afficher();
    //bool supprimer(int);
    bool imprimer();

};

#endif // CHAINE_H


#include "A10Etat.h"

using namespace std;

Etat::Etat(){
    nom = -1;
    rang = 0;
    datePlusTot = 0;
    datePlusTard = 0;
    marge = 0;
}
Etat::Etat(unsigned int nom) {
    this->nom = nom;
    this->rang = 0;
    this->datePlusTot = 0;
    this->datePlusTard = 0;
    this->marge = 0;
}

Etat::Etat(Etat& a){
    this->nom = a.nom;
    this->rang = a.rang;
    this->datePlusTot = a.datePlusTot;
    this->datePlusTard = a.datePlusTard;
    this->marge = a.marge;
}


void Etat::ajoutSuccesseur(Etat* etat, int poids)
{
    this->successeurs.push_back(etat);
    this->poidsSuccesseur.push_back(poids);
}

void Etat::ajoutPredecesseur(Etat* etat, int poids)
{
    this->predecesseurs.push_back(etat);
    this->poidsPredecesseur.push_back(poids);
}


// fonction testée au niveau de l'etat, mais pas au niveau du poids
void Etat::supprSuccesseur(unsigned int nom){

    int posSuccesseur = chercherPosSuccesseur(nom);

    if(posSuccesseur != -1){
        this->successeurs.erase(successeurs.begin() + posSuccesseur);
        this->poidsSuccesseur.erase(poidsSuccesseur.begin() + posSuccesseur);
    }
}

int Etat::chercherPosSuccesseur(int nom){
    for(unsigned int pos = 0; pos<successeurs.size(); pos++){
        if(successeurs[pos]->getNom() == nom){
            return pos;
        }
    }
    cerr<< "ERREUR DANS chercherPosSuccesseur, le successeur n'a pas été trouvé" <<endl;
    return -1;
}


// fonction testée au niveau de l'etat, mais pas au niveau du poids
void Etat::supprPredecesseur(unsigned int nom){

    int posPredecesseur = chercherPosPredecesseur(nom);

    if(posPredecesseur != -1){
        this->predecesseurs.erase(predecesseurs.begin() + posPredecesseur);
        this->poidsPredecesseur.erase(poidsPredecesseur.begin() + posPredecesseur);
    }
}

int Etat::chercherPosPredecesseur(int nom){
    for(unsigned int pos = 0; pos<predecesseurs.size(); pos++){
        if(predecesseurs[pos]->getNom() == nom){
            return pos;
        }
    }
    cerr<< "ERREUR DANS chercherPosPredecesseur, le predecesseur n'a pas été trouvé" <<endl;
    return -1;
}


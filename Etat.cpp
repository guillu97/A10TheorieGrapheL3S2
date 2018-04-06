
#include "Etat.h"

using namespace std;

Etat::Etat(){
    nom = -1;
}
Etat::Etat(unsigned int nom) {
    this->nom = nom;
}

Etat::Etat(Etat& a){
    this->nom = a.nom;
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

int Etat::chercherPosSuccesseur(unsigned int nom){
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

int Etat::chercherPosPredecesseur(unsigned int nom){
    for(unsigned int pos = 0; pos<predecesseurs.size(); pos++){
        if(predecesseurs[pos]->getNom() == nom){
            return pos;
        }
    }
    cerr<< "ERREUR DANS chercherPosPredecesseur, le predecesseur n'a pas été trouvé" <<endl;
    return -1;
}



#include "Etat.h"

using namespace std;

Etat::Etat(){
    nom = -1;
}
Etat::Etat(int nom) {
    this->nom = nom;
}

Etat::Etat(Etat& a){
    this->nom = a.nom;
}


void Etat::ajoutSuccesseur(int nom, int poids)
{
    this->successeurs.push_back(new Etat(nom));
    this->poidsSuccesseur.push_back(poids);
}

void Etat::ajoutPredecesseur(int nom, int poids)
{
    this->predecesseurs.push_back(new Etat(nom));
    this->poidsPredecesseur.push_back(poids);
}





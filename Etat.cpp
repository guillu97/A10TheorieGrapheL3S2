
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


void Etat::ajoutSuccesseur(int nom)
{
    this->successeurs.push_back(new Etat(nom));
}

void Etat::ajoutArcEntrants(Arc* arc){
    this->tabArcsEntrants.push_back(arc);
}
void Etat::ajoutArcSortants(Arc* arc){
    this->tabArcsSortants.push_back(arc);
}




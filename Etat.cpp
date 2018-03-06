
#include "Etat.h"

using namespace std;

Etat::Etat(int nom) {
    this->nom = nom;
}


void Etat::ajoutSuccesseur(int nom)
{
    this->successeurs.push_back(new Etat(nom));
}



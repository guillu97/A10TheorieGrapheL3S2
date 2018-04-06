
//
// Created by SPORE on 06/03/2018.
//

#ifndef A10THEORIEGRAPHEL3S2_ETAT_H
#define A10THEORIEGRAPHEL3S2_ETAT_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>


class Etat {

private:
    int nom;
    int rang = 0;







public:
    std::vector <Etat*> successeurs;
    std::vector <Etat*> predecesseurs;
    std::vector<int> poidsSuccesseur;
    std::vector<int> poidsPredecesseur;

    Etat(unsigned int nom);
    Etat(Etat& a);
    Etat();
    void ajoutSuccesseur(Etat* etat, int poids);
    void ajoutPredecesseur(Etat* etat, int poids);

    // fonction testée au niveau de l'etat, mais pas au niveau du poids
    void supprSuccesseur(unsigned int nom);
    int chercherPosSuccesseur(unsigned int nom);

    // fonction testée au niveau de l'etat, mais pas au niveau du poids
    void supprPredecesseur(unsigned int nom);
    int chercherPosPredecesseur(unsigned int nom);

    unsigned int getNom(){
        return this->nom;
    }

    /*
    std::vector <Etat*>* getSuccesseurs(){
        return &successeurs;
    }

    std::vector <Etat*>* getPredecesseurs(){
        return &predecesseurs;
    }
    */


};


#endif //A10THEORIEGRAPHEL3S2_ETAT_H

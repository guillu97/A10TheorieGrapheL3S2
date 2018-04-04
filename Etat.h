
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
    std::vector <Etat*> successeurs;
    std::vector <Etat*> predecesseurs;


    std::vector<int> poidsSuccesseur;
    std::vector<int> poidsPredecesseur;



public:
    Etat(int nom);
    Etat(Etat& a);
    Etat();
    void ajoutSuccesseur(int nom, int poids);
    void ajoutPredecesseur(int nom, int poids);


    int getNom(){
        return this->nom;
    }

    std::vector <Etat*> getSuccesseurs(){
        return successeurs;
    }

    std::vector <Etat*> getPredecesseurs(){
        return predecesseurs;
    }


};


#endif //A10THEORIEGRAPHEL3S2_ETAT_H

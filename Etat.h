
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





public:
    Etat(int nom);
    Etat(Etat& a);
    Etat();
    void ajoutSuccesseur(int nom);


    int getNom(){
        return this->nom;
    }

    std::vector <Etat*> getSuccesseurs(){
        return successeurs;
    }

};


#endif //A10THEORIEGRAPHEL3S2_ETAT_H

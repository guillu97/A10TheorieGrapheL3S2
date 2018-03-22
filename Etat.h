
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

// it is needed to avoid include loop
class Arc;

class Etat {

private:
    int nom;
    std::vector <Etat*> successeurs;
    std::vector <Arc*> tabArcsEntrants;
    std::vector <Arc*> tabArcsSortants;




public:
    Etat(int nom);
    Etat(Etat& a);
    Etat();
    void ajoutSuccesseur(int nom);
    void ajoutArcEntrants(Arc*);
    void ajoutArcSortants(Arc*);


    int getNom(){
        return this->nom;
    }

    std::vector <Etat*> getSuccesseurs(){
        return successeurs;
    }

    std::vector <Arc*> getTabArcsEntrants(){
        return tabArcsEntrants;
    }
    std::vector <Arc*> getTabArcsSortants(){
        return tabArcsSortants;
    }


};


#endif //A10THEORIEGRAPHEL3S2_ETAT_H

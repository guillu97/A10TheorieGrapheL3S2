//
// Created by SPORE on 06/03/2018.
//

#ifndef A10THEORIEGRAPHEL3S2_GRAPHE_H
#define A10THEORIEGRAPHEL3S2_GRAPHE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <vector>


#include "Etat.h"
#include "Arc.h"

#define DEBUG 1

class Graphe {

private:


    std::string fileName;
    int nbSommet;
    int nbArc;
    bool** matAdj = NULL;
    double** matInc = NULL;

    std::vector <Arc*> tabArcs;
    std::vector <int> tabPointEntrees;

    Etat* tabEtats[];



    //Arete* matAdj;


public:
    Graphe(std::string fileName);
    Graphe(Graphe* test);

    void importGraphe(std::string fileName);
    void displayGraphe();
    void recherchePointsEntrees();
    void displayPointEntrees();


};


#endif //A10THEORIEGRAPHEL3S2_GRAPHE_H

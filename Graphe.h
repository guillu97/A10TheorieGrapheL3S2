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

#define DEBUG 1

class Graphe {

private:


    std::string fileName;
    int nbSommet;
    int nbArc;

    bool** matAdj = NULL;
    double** matInc = NULL;


    // En UTILISANT matAdj
    //std::vector <int> tabPointEntrees;
    std::vector <Etat*> tabPointEntrees;

    std::vector<Etat*> tabEtats;



    //Arete* matAdj;


public:

    Graphe(std::string fileName);
    Graphe(Graphe const& autreGraphe);

    void importGraphe(std::string fileName);
    void remplirGraphe();
    void displayGraphe();
    void recherchePointsEntrees();
    void displayPointEntrees();

    void niveau1();

};


#endif //A10THEORIEGRAPHEL3S2_GRAPHE_H

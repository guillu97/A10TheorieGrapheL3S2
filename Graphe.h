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



#define DEBUG 1

class Graphe {

private:


    std::string fileName;
    int nbSommet;
    int nbArc;
    std::vector < std::vector <bool> > matAdj;
    std::vector < std::vector <int> > matInc;


    // En utilisant matAdj
    std::vector <int> tabPointEntree;





public:
    Graphe(std::string fileName);
    Graphe(Graphe& g);

    void importGraphe(std::string fileName);
    void displayGraphe();
    void recherchePointsEntree();
    void displayPointEntree();
    bool detectionCircuit();
    bool verifMatAdjVide();
    void niveau1();

};


#endif //A10THEORIEGRAPHEL3S2_GRAPHE_H

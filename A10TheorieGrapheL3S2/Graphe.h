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

<<<<<<< HEAD
=======


>>>>>>> 5cdf1cf06e800bed9a53b772a742223e53e3b5e9

class Graphe {

private:
    std::string fileName;
    int nbSommet;
    int nbArc;
    bool** matAdj = NULL;
    double** matInc = NULL;


    bool hasBeenImported;
    void importGraphe(std::string fileName);

    //Arete* matAdj;


public:
    Graphe(std::string fileName);

    void displayGraphe();

};

typedef struct sommetListePredecesseurs { /*liste des prédecesseurs associés à un sommet*/
 int sommet ;
 sommetListePredecesseurs * predecesseurSuivant } sommetListePredecesseurs ;

 typedef struct listeSommets { /*liste des listes de prédecesseurs = liste de sommets*/
 int sommet ;
 sommetListePredecesseurs * predecesseurs ;
 listeSommets * sommetSuivant } listeSommets ;


#endif //A10THEORIEGRAPHEL3S2_GRAPHE_H

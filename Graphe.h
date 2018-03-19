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


class Graphe {

private:
    std::string fileName;
    int nbSommet;
    int nbArc;
    bool** matAdj;
    double** matInc;

    //Arete* matAdj;


public:
    Graphe();
    void importGraphe(std::string fileName);
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

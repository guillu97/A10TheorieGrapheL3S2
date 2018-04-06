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





    //Arete* matAdj;


public:

std::vector<Etat*> tabEtats;

    Graphe(std::string fileName);
    Graphe(Graphe const& autreGraphe);

    void importGraphe(std::string fileName);
    void remplirGraphe();
    void displayGraphe();
    void affichageGraphe();
    void displayEtatToMatriceAdjIncid();
    void recherchePointsEntrees();
    void displayPointEntrees();

    void supprEtat(Etat* etat);
    int chercherPosEtatDansTab(Etat* etatSearch, std::vector<Etat*> tabDeRecherche);
    void detectionCircuit();

    void niveau1();

};


#endif //A10THEORIEGRAPHEL3S2_GRAPHE_H

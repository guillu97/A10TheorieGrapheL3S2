//
// Created by SPORE on 06/03/2018.
//

#ifndef A10THEORIEGRAPHEL3S2_GRAPHE_H
#define A10THEORIEGRAPHEL3S2_GRAPHE_H

#include <string>
#include <iostream>
#include <iomanip>
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
    int** matInc = NULL;


    // En UTILISANT matAdj
    //std::vector <int> tabPointEntrees;
    std::vector <Etat*> tabPointEntrees;

    bool importe;




    //Arete* matAdj;


public:

    std::vector<Etat*> tabEtats;

    Graphe(std::string fileName);
    Graphe(Graphe const& autreGraphe);

    bool importGraphe(std::string fileName);
    void remplirGraphe();
    void displayGraphe();
    void affichageGraphe();
    void displayEtatToMatriceAdjIncid();
    void recherchePointsEntrees();
    void displayPointEntrees();

    void supprEtat(Etat* etat);
    int chercherPosEtatDansTab(Etat* etatSearch, std::vector<Etat*> tabDeRecherche);


    //return true s'il y a un circuit
    //return false s'il n'y a pas de circuit
    bool detectionCircuit();
    void calcRang();

    void affichageRang();

    bool verificationPointEntree();

    void niveau1();
    void niveau2();

};


#endif //A10THEORIEGRAPHEL3S2_GRAPHE_H

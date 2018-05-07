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

#define DEBUG 0

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
    std::vector<Etat*>  tabPointSorties;

    bool importe;




    //Arete* matAdj;


public:

    std::vector<Etat*> tabEtats;

    Graphe(std::string fileName, int level);
    Graphe(Graphe const& autreGraphe);

    bool importGraphe(std::string fileName);
    bool importContrainte(std::string fileName);
    void remplirGraphe();
    void displayGraphe();
    void affichageGraphe();
    void displayEtatToMatriceAdjIncid();

    void recherchePointsEntrees();
    void displayPointEntrees();

    void recherchePointsSorties();
    void displayPointSorties();

    void supprEtat(Etat* etat);
    int chercherPosEtatDansTab(Etat* etatSearch, std::vector<Etat*> tabDeRecherche);


    //return true s'il y a un circuit
    //return false s'il n'y a pas de circuit
    bool detectionCircuit();
    void calcRang();

    void affichageRang();
    // affichage des rangs sous forme d'un tableau (pour la lisibilité)
    void affichageRangTab();

    bool verificationPointEntree();
    bool verificationPointSortie();

    bool verificationValeurArc();
    bool verificationValeurArcNonNulle();

    void calcDatePlusTot();

    void displayDatePlusTot();

    void niveau1();
    void niveau2();

};


#endif //A10THEORIEGRAPHEL3S2_GRAPHE_H

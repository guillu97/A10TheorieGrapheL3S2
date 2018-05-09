//
// Created by SPORE on 06/03/2018.
//

#ifndef A10THEORIEGRAPHEL3S2_A10GRAPHE_H
#define A10THEORIEGRAPHEL3S2_A10GRAPHE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <vector>
#include <istream>


#include "A10Etat.h"
#include "A10log.h"

#define DEBUG 1
#define LOG 1

class Graphe {

private:
    std::string fileName;
    int nbSommet;
    int nbArc;

    bool** matAdj = NULL;
    int** matInc = NULL;

    // utilisé pour les contraintes
    int* tabPoidsEtat = NULL;


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


    bool** grapheToMatAdj();

    int** grapheToMatInc();


    void recherchePointsEntrees();
    void displayPointEntrees();

    void recherchePointsSorties();
    void displayPointSorties();


    std::vector<Etat*> suppr(std::vector<Etat*> tab, Etat* etat);
    std::vector<int> suppr(std::vector<int> tab, int poids);

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
    bool verificationValeurArcInteract();

    bool verificationValeurArcNonNeg();
    bool verificationValeurArcNonNegInteract();


    bool remplirGrapheInteract();

    std::vector<Etat*> detectionCircuitInteract();

    void copieGrapheInteract(Graphe* autreGraphe);
    Graphe(Graphe* autreGraphe);

    bool** grapheToMatAdjContraintes();

    int** grapheToMatIncContraintes();


    void calcDatePlusTot();
    void displayDatePlusTot();

    /**
    * @param pourcentageDatePlusTard le pourcentage pour la date au plus tard de fin de projet égal
    * à certain poucentage de sa date au plus tôt
    * (ici le pourcentage est juste un rapport, généralement on appelera cette fonction avec un nombre entre 1 et 2,
    * ce qui équivaut à 100 à 200 pourcents
    * (si pourcentagDatePlusTard = 1, date au plus tard du projet est égale à sa date au plus tot)
    */
    void calcDatePlusTard(float pourcentageDatePlusTard);
    void displayDatePlusTard();

    void calcMarges();
    void affichageMarge();

    void creerPointEntree();
    void creerPointSortie();

    void niveau1();
    void niveau2();
    void niveau3();
    void niveau4();

};


#endif //A10THEORIEGRAPHEL3S2_A10GRAPHE_H

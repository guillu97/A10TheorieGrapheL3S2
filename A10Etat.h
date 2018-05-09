
//
// Created by SPORE on 06/03/2018.
//

#ifndef A10THEORIEGRAPHEL3S2_A10ETAT_H
#define A10THEORIEGRAPHEL3S2_A10ETAT_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>


class Etat {

private:
    int nom;
    int rang;
    int datePlusTot;
    int datePlusTard;
    int marge;



    //TODO: On devrait mettre un poid pour le niveau 3 !!!!!! Les deux tableaux suivants serait inutiles




public:
    std::vector <Etat*> successeurs;
    std::vector <Etat*> predecesseurs;
    std::vector<int> poidsSuccesseur;
    std::vector<int> poidsPredecesseur;

    Etat(unsigned int nom);
    Etat(Etat& a);
    Etat();
    void ajoutSuccesseur(Etat* etat, int poids);
    void ajoutPredecesseur(Etat* etat, int poids);

    // fonction testée au niveau de l'etat, mais pas au niveau du poids
    void supprSuccesseur(unsigned int nom);
    int chercherPosSuccesseur(int nom);

    // fonction testée au niveau de l'etat, mais pas au niveau du poids
    void supprPredecesseur(unsigned int nom);
    int chercherPosPredecesseur(int nom);

    int getNom(){
        return this->nom;
    }

    void setNom(int newNom){
        this->nom = newNom;
    }

    void setRang(int newRang){
        this->rang = newRang;
    }
    int getRang(){
        return this->rang;
    }

    void setDatePlusTot(int newDatePlusTot){
        this->datePlusTot = newDatePlusTot;
    }

    int getDatePlusTot(){
        return datePlusTot;
    }

    void setDatePlusTard(int newDatePlusTard){
        this->datePlusTard = newDatePlusTard;
    }

    int getDatePlusTard(){
        return datePlusTard;
    }

    void setMarge(int newMarge){
        this->marge = newMarge;
    }

    int getMarge(){
        return marge;
    }

    /*
    std::vector <Etat*>* getSuccesseurs(){
        return &successeurs;
    }

    std::vector <Etat*>* getPredecesseurs(){
        return &predecesseurs;
    }
    */


};


#endif //A10THEORIEGRAPHEL3S2_A10ETAT_H

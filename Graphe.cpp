//
// Created by SPORE on 06/03/2018.
//


#include "Graphe.h"
#include <fstream>





using namespace std;

Graphe::Graphe(string fileName) {
    this->fileName = fileName;
    this->hasBeenImported = false;
    importGraphe(fileName);

}



void Graphe::importGraphe(string fileName) {

    ifstream file(fileName.c_str(), ios::in);  // on ouvre le fichier en lecture, le fichier est dans le même dossier que l'executable


    if(file)  // si l'ouverture a réussi
    {

        // instructions

        file >> this->nbSommet;
        file >> this->nbArc;


        // créer tableau de booléen 2d   (matrice carrée de hauteur nb sommet)  toutes les cases sont initialisées à false
        matAdj = new bool*[this->nbSommet];
        for(int i = 0; i < this->nbSommet; i++)
        {
            matAdj[i] = new bool[this->nbSommet];
            for(int j = 0; j <this->nbSommet; j++){
                matAdj[i][j] = false;
            }
        }

        // créer tableau de int 2d  (matrice carrée de hauteur nb sommet) toutes les cases sont initialisées à 0
        matInc = new double*[this->nbSommet];
        for(int i = 0; i < this->nbSommet; i++)
        {
            matInc[i] = new double[this->nbSommet];
            for(int j = 0; j <this->nbSommet; j++){
                matInc[i][j] = NAN;

            }
        }



        // remplir matAdj et matInc
        int etatDebut, etatFin, poids;
        for(int i = 0; i < this->nbArc; i++){

            file >> etatDebut;
            cout << "etatDebut: " << etatDebut << " ";
            file >> etatFin;
            cout << "etatFin: " << etatFin<< " ";
            file >> poids;
            cout<< "poids: " << poids << endl;

            // remplir une case matAdj avec true
            matAdj[etatDebut][etatFin] = true;

            //remplir une case matInc avec son poids
            matInc[etatDebut][etatFin] = poids;
        }

        hasBeenImported = true;

        file.close();  // on ferme le fichier

    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;

}

void Graphe::displayGraphe() {
    ofstream fichier("A10FargesNomicisioVo.txt", ios::app);
    // ios::append, pas de suppression du contenu déjà existant, ajout des traces à la suite
    if(hasBeenImported) {
        if(fichier) // si le fichier d'écriture existe
        {

        cout << "nb sommet: ";
        fichier << "nb sommet: ";
        cout << this->nbSommet << endl;
        fichier << this->nbSommet << endl;

        cout << "\n" << "nb arc: ";
        fichier << "\n" << "nb arc: ";
        cout << this->nbArc << endl;
        fichier << this->nbArc << endl;


        cout << "\n" << "MatAdj: " << endl;
        fichier << "\n" << "MatAdj: " << endl;

        // display matAdj

        for (int i = 0; i < this->nbSommet; i++) {
            for (int j = 0; j < this->nbSommet; j++) {
                cout << matAdj[i][j] << " ";
                fichier << matAdj[i][j];
                fichier << " ";
            }
            cout << endl;
            fichier << endl;
        }


        cout << "\n" << "MatInc: " << endl;
        fichier << "\n" << "MatInc: " << endl;

        // display matInc

        for (int i = 0; i < this->nbSommet; i++) {
            for (int j = 0; j < this->nbSommet; j++) {

                if (isnan(matInc[i][j])) {
                    cout << "/" << " ";
                    fichier << "/" << " ";
                }
                else
                {
                    cout << matInc[i][j] << " ";
                    fichier << matInc[i][j] << " ";
                }

            }
            cout << endl;
            fichier << endl;
        }
        cout << endl;
        fichier << endl;
        }
        else // le fichier d'écriture n'existe pas
        {
            cerr << "FATAL ERROR" << endl;
        }
    }else
        cerr << "the Graphe hasn't been imported" <<endl;

}



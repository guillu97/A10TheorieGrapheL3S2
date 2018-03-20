//
// Created by SPORE on 06/03/2018.
//


#include "Graphe.h"






using namespace std;

Graphe::Graphe(string fileName) {
    this->fileName = fileName;
    importGraphe(fileName);




}


void Graphe::importGraphe(string fileName) {

    ifstream file(fileName.c_str(), ios::in);  // on ouvre le fichier en lecture, le fichier est dans le même dossier que l'executable


    if(file)  // si l'ouverture a réussi
    {


        // instructions

        file >> this->nbSommet;
        file >> this->nbArc;


        // create a tabEtat with all the states, then we will add the successors
        for(int i = 0; i<this->nbSommet; i++){
            this->tabEtats[i] = new Etat(i);
        }

        #if DEBUG == 1
        cout <<endl;
        cout << "Les etats presents: " <<endl;
        for(int i = 0; i<this->nbSommet; i++ ){
            cout << tabEtats[i]->getNom() << " ";
        }
        cout <<endl;
        cout <<endl;
        #endif // DEBUG



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




        // remplir matAdj, matInc, tabEtats et tabArc
        int etatDebut, etatFin, poids;

        for(int i = 0; i < this->nbArc; i++){

            file >> etatDebut;

            file >> etatFin;

            file >> poids;


            #if DEBUG == 1

                cout <<"DEBUG"<<endl;
                cout << "etatDebut: " << etatDebut << " ";

                cout << "etatFin: " << etatFin<< " ";

                cout<< "poids: " << poids << endl;
            #endif // DEBUG

            // remplir une case matAdj avec true
            matAdj[etatDebut][etatFin] = true;

            //remplir une case matInc avec son poids
            matInc[etatDebut][etatFin] = poids;


            //we add the successor to the tabEtats
            tabEtats[etatDebut]->ajoutSuccesseur(etatFin);

            // ajoute les arcs
            tabArcs.push_back(new Arc(tabEtats[etatDebut], tabEtats[etatFin], poids));

        }

        #if DEBUG == 1

            cout << endl;
            cout << endl;
            cout << "DEBUG" <<endl;

            cout << "Tous les etats et leurs successeurs: "<<endl;
            for(int i = 0; i<this->nbSommet; i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                cout << "Etat " << tabEtats[i]->getNom() << " :"<<endl;
                cout<< "successeurs: [ ";
                for(unsigned int j = 0; j<tabEtats[i]->getSuccesseurs().size(); j++){
                    cout << tabEtats[i]->getSuccesseurs()[j]->getNom() << " ";
                }
                cout <<"]"<<endl;
            }

            cout << endl;
            cout << endl;


            cout << endl;
            cout << endl;

            cout << "Tous les arcs: "<<endl;
            for(int i = 0; i< this->nbArc; i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                cout << "Arc : " <<endl;
                cout << "Etat debut " << tabArcs[i]->getExtremiteInitiale()->getNom();
                cout<< " Etat fin " << tabArcs[i]->getExtremiteTerminale()->getNom();
                cout<< " Poids " << tabArcs[i]->getPoids();
                cout <<endl;
            }

            cout << endl;
            cout << endl;

        #endif // DEBUG





        file.close();  // on ferme le fichier

    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;

}

void Graphe::displayGraphe() {
    cout << endl;
    cout << "nb sommet: ";
    cout << this->nbSommet << endl;
    cout << endl;
    cout << "nb arc: ";
    cout << this->nbArc << endl;

    cout << endl;

    cout << "MatAdj: " << endl;

    if(matAdj != NULL){
        // display matAdj
        for(int i = 0; i<this->nbSommet; i++){
            for(int j = 0; j<this->nbSommet; j++){
                cout << matAdj[i][j] << " ";
            }
            cout << endl;
        }
    }else
        cout << "matAdj est vide" <<endl;

    cout << endl;

    cout << "MatInc: " << endl;
    if(matInc != NULL){
        // display matInc
        for(int i = 0; i<this->nbSommet; i++){
            for(int j = 0; j<this->nbSommet; j++){
                if(isnan(matInc[i][j])){
                    cout << "/" << " ";
                }else
                    cout << matInc[i][j] << " ";
            }
            cout << endl;
        }
    }else
        cout << "matInc est vide" <<endl;

    cout << endl;



}



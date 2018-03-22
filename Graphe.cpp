//
// Created by SPORE on 06/03/2018.
//


#include "Graphe.h"






using namespace std;

Graphe::Graphe(string fileName) {
    this->fileName = fileName;
    importGraphe(fileName);




}
Graphe::Graphe(Graphe* autreGraphe) {
    this->fileName = autreGraphe->fileName;
    this->importGraphe(fileName);
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
            tabEtats.push_back(new Etat(i));
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

            //ajoute les arcs dans les états
            tabEtats[etatDebut]->ajoutArcSortants(new Arc(tabEtats[etatDebut], tabEtats[etatFin], poids));
            tabEtats[etatFin]->ajoutArcEntrants(new Arc(tabEtats[etatFin], tabEtats[etatDebut], poids));
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

            cout << "Tous les etats et leurs arcs: "<<endl;
            cout << endl;
            for(int i = 0; i<this->nbSommet; i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                cout << "Etat " << tabEtats[i]->getNom() << " :"<<endl;
                cout<< "Arcs sortants ("<< tabEtats[i]->getTabArcsSortants().size()<<") : " <<endl<< "[ "<<endl;
                for(unsigned int j = 0; j<tabEtats[i]->getTabArcsSortants().size(); j++){
                    tabEtats[i]->getTabArcsSortants()[j]->afficherArc();
                }
                cout <<"]"<<endl;
                cout<< "Arcs entrants (" << tabEtats[i]->getTabArcsEntrants().size() <<") : " <<endl<< "[ "<<endl;
                for(unsigned int j = 0; j<tabEtats[i]->getTabArcsEntrants().size(); j++){
                    tabEtats[i]->getTabArcsEntrants()[j]->afficherArc();
                }
                cout <<"]"<<endl;

                cout << endl;
            }

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

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Graphe::recherchePointsEntrees(){

    // cette somme permet de vérifier s'il l'état est présent parmi les successeurs de tous les états
    int sum = 0;
    // on va parcourir tout le tableau des états
    for(unsigned int i = 0; i<this->tabEtats.size(); i++){
            sum = 0;
            for(unsigned int j = 0; j<this->tabEtats.size(); j++){

                // on récupère son tableau de successeurs
                vector<Etat*>tabSuccesseurs = tabEtats[tabEtats[j]->getNom()]->getSuccesseurs();


                // on recherche dans le tableau des successeurs de l'état  (tabEtat[tabEtats[j]->getNom()])
                // pour voir si l'état tabEtats[i]->getNom() est présent ou non.
                // si à la fin du 'for' sum = 0, alors létat n'est pas présent
                 for(unsigned int k = 0; k< tabSuccesseurs.size(); k++){
                    if(tabSuccesseurs[k]->getNom() == tabEtats[i]->getNom())
                        sum++;
                 }
            }
            if(sum == 0){
                tabPointEntrees.push_back(tabEtats[i]);
            }
    }
    #if DEBUG == 1
        displayPointEntrees();


    #endif // DEBUG


    /*
     En UTILISANT la matrice d'adjacence
    int sum = 0;
    for(int j = 0; j<this->nbSommet; j++){
        sum = 0;
        for(int i = 0; i<this->nbSommet; i++){
            cout<< "mat ["<<i<<"]"<<"["<<j<<"] " << matAdj[i][j] <<endl;
            if(matAdj[i][j]){
                    cout<<"test" <<endl;
                sum++;
            }
        }
        cout<<endl;

        if(sum == 0){
            tabPointEntrees.push_back(j);
        }
    }

    #if DEBUG == 1
        displayPointEntrees();


    #endif // DEBUG

    */
}

void Graphe::displayPointEntrees(){
    cout<<endl;
    cout<<endl;

    cout << "Points d'entrees"<<endl;

    if(tabPointEntrees.size() == 0)
        cout<<"Il n y a pas de point d entree"<<endl;
    else{
          for(unsigned int i = 0; i<tabPointEntrees.size(); i++)
            cout<<"Etat "<< tabPointEntrees[i]->getNom() <<endl;
    }

    /*
    En UTILISANT la matrice d'adjacence
    if(tabPointEntrees.size() == 0)
        cout<<"Il n y a pas de point d entree"<<endl;
    else{
        for(unsigned int i = 0; i<tabPointEntrees.size(); i++)
            cout<<"Etat "<< tabPointEntrees[i] <<endl;
    }
    */
    cout<<endl;
    cout<<endl;
}




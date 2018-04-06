//
// Created by SPORE on 06/03/2018.
//


#include "Graphe.h"
#define SPACE 3





using namespace std;

Graphe::Graphe(string fileName) {
    this->fileName = fileName;
    importGraphe(fileName);
}

Graphe::Graphe(Graphe const& autreGraphe) {

    this->fileName = autreGraphe.fileName;

    this->nbSommet = autreGraphe.nbSommet;
    this->nbArc = autreGraphe.nbArc;

    // créer tableau de booléen 2d   (matrice carrée de hauteur nb sommet)  toutes les cases sont copiées
    this->matAdj = new bool*[this->nbSommet];
    for(int i = 0; i < this->nbSommet; i++)
    {
        this->matAdj[i] = new bool[this->nbSommet];
        for(int j = 0; j <this->nbSommet; j++){
            this->matAdj[i][j] = autreGraphe.matAdj[i][j];
        }
    }

    // créer tableau de int 2d  (matrice carrée de hauteur nb sommet) toutes les cases sont copiées
    this->matInc = new double*[this->nbSommet];
    for(int i = 0; i < this->nbSommet; i++)
    {
        this->matInc[i] = new double[this->nbSommet];
        for(int j = 0; j <this->nbSommet; j++){
            matInc[i][j] = autreGraphe.matInc[i][j];

        }
    }


    this->remplirGraphe();
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




        // remplir matAdj, matInc, tabEtats et tabArc
        int etatDebut, etatFin, poids;

        #if DEBUG == 1
                cout <<"DEBUG : lecture du fichier txt "<<endl;
        #endif // DEBUG

        for(int i = 0; i < this->nbArc; i++){

            file >> etatDebut;

            file >> etatFin;

            file >> poids;


            #if DEBUG == 1
                cout << "etatDebut: " << etatDebut << " ";

                cout << "etatFin: " << etatFin<< " ";

                cout<< "poids: " << poids << endl;
            #endif // DEBUG

            // remplir une case matAdj avec true
            matAdj[etatDebut][etatFin] = true;

            //remplir une case matInc avec son poids
            matInc[etatDebut][etatFin] = poids;

        }

        #if DEBUG == 1
                cout <<": DEBUG "<<endl;
        #endif // DEBUG


    // test
        remplirGraphe();

        file.close();  // on ferme le fichier

    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;

}

/**
*   fonction qui remplit le graphe (tabEtat) à partir de la matrice d'adjacence et de la matrice d'incicdence
*/
void Graphe::remplirGraphe(){

    // create a tabEtat with all the states, then we will add the successors
    for(int i = 0; i<this->nbSommet; i++){
        tabEtats.push_back(new Etat(i));
    }

    #if DEBUG == 1
        cout << endl;
        cout<< "DEBUG : " <<endl;
        cout << "Les etats presents: " <<endl;
        for(int i = 0; i<this->nbSommet; i++ ){
            cout << tabEtats[i]->getNom() << " ";
        }
        cout<<endl;
        cout<< ": DEBUG" <<endl;
        cout <<endl;
    #endif // DEBUG


    for(int etatDebut = 0; etatDebut<this->nbSommet; etatDebut++){
        for(int etatFin = 0; etatFin<this->nbSommet; etatFin++){
                        //we add the successor to the tabEtats
            if(matAdj[etatDebut][etatFin]){
                tabEtats[etatDebut]->ajoutSuccesseur(tabEtats[etatFin], matInc[etatFin][etatDebut]);
                tabEtats[etatFin]->ajoutPredecesseur(tabEtats[etatDebut], matInc[etatDebut][etatFin]);
            }
        }
    }


    #if DEBUG == 1

            cout << endl;
            cout << endl;
            cout << "DEBUG : " <<endl;

            cout << "Tous les etats et leurs successeurs : "<<endl;
            for(unsigned int i = 0; i<this->tabEtats.size(); i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                cout << "Etat " << tabEtats[i]->getNom() << " :"<<endl;
                cout<< "successeurs: [ ";
                for(unsigned int j = 0; j<tabEtats[i]->successeurs.size(); j++){
                    cout << tabEtats[i]->successeurs[j]->getNom() << " ";
                }
                cout <<"]"<<endl;
            }

            cout << "Tous les etats et leurs predecesseurs : "<<endl;
            for(unsigned int i = 0; i<this->tabEtats.size(); i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                cout << "Etat " << tabEtats[i]->getNom() << " :"<<endl;
                cout<< "predecesseurs: [ ";
                for(unsigned int j = 0; j<tabEtats[i]->predecesseurs.size(); j++){
                    cout << tabEtats[i]->predecesseurs[j]->getNom() << " ";;
                }
                cout <<"]"<<endl;
            }

            cout<<": DEBUG"<<endl;
            cout << endl;
            cout << endl;

        #endif // DEBUG


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

void Graphe::displayEtatToMatriceAdjIncid(){

    cout << "****MATRICE D'ADJACENCE****" << endl << endl;
    for(unsigned int j = 0; j < tabEtats.size(); j++)
        cout << setw(SPACE) << left << tabEtats[j]->getNom();
    cout << endl;
    for(unsigned int j = 0; j < tabEtats.size(); j++)
        cout << "-------";
    cout << endl;
    for(unsigned int i = 0; i < this->tabEtats.size(); i++){
        std::vector <Etat*> tabSuccesseursSuccesseurs = tabEtats[i]->successeurs;
        unsigned int k = 0;
        for(unsigned int j = 0; j < tabEtats.size(); j++){

            if ( k >= tabSuccesseursSuccesseurs.size())
                cout << setw(SPACE) << left << 0;
            else if(tabSuccesseursSuccesseurs[k]->getNom() == tabEtats[j]->getNom()){
                cout << setw(SPACE) << left << 1;
                k++;
            }
            else
                cout << setw(SPACE) << left << 0;
        }
        cout << endl;
    }

    cout << "****MATRICE D'INCIDENCE****" << endl << endl;
    for(unsigned int j = 0; j < tabEtats.size(); j++)
        cout << setw(SPACE) << left << tabEtats[j]->getNom();
    cout << endl;
    for(unsigned int j = 0; j < tabEtats.size(); j++)
        cout << "-------";
    cout << endl;
    for(unsigned int i = 0; i < this->tabEtats.size(); i++){
        std::vector <Etat*> tabSuccesseursSuccesseurs = tabEtats[i]->successeurs;
        unsigned int k = 0;
        for(unsigned int j = 0; j < tabEtats.size(); j++){

            if ( k >= tabSuccesseursSuccesseurs.size())
                cout << setw(SPACE) << left << "/";
            else if(tabSuccesseursSuccesseurs[k]->getNom() == tabEtats[j]->getNom()){
                cout << setw(SPACE) << left << tabEtats[j]->poidsSuccesseur[k];
                k++;
            }
            else
                cout << setw(SPACE) << left << "/";
        }
        cout << endl;
    }

}



void Graphe::affichageGraphe(){
    cout << "Tous les etats et leurs successeurs : "<<endl;
            for(unsigned int i = 0; i<this->tabEtats.size(); i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                cout << "Etat " << tabEtats[i]->getNom() << " :"<<endl;
                cout<< "successeurs: [ ";
                for(unsigned int j = 0; j<tabEtats[i]->successeurs.size(); j++){
                    cout << tabEtats[i]->successeurs[j]->getNom() << " ";
                }
                cout <<"]"<<endl;

                cout<< "PoidsSuccesseurs: [ ";
                for(unsigned int j = 0; j<tabEtats[i]->successeurs.size(); j++){
                    cout << tabEtats[i]->poidsSuccesseur[j] << " ";
                }
                cout <<"]"<<endl;
            }

            cout << "Tous les etats et leurs predecesseurs : "<<endl;
            for(unsigned int i = 0; i<this->tabEtats.size(); i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                cout << "Etat " << tabEtats[i]->getNom() << " :"<<endl;
                cout<< "predecesseurs: [ ";
                for(unsigned int j = 0; j<tabEtats[i]->predecesseurs.size(); j++){
                    cout << tabEtats[i]->predecesseurs[j]->getNom() << " ";
                }
                cout <<"]"<<endl;
            }
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
                vector<Etat*>tabSuccesseurs = tabEtats[tabEtats[j]->getNom()]->successeurs;


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



void Graphe::supprEtat(Etat* etat){
    int posEtatInTabEtat = chercherPosEtatDansTab(etat, tabEtats);

    // si on trouve l'etat à supprimer
    if(posEtatInTabEtat != -1){

        // /!\ c'est une copie faite pour la recherche de position
        vector<Etat*> successeurs = tabEtats[posEtatInTabEtat]->successeurs;

        for(unsigned int i = 0; i < successeurs.size(); i++){

            // /!\ c'est une copie faite pour la recherche
            vector<Etat*> predecesseurDeEtat = successeurs[i]->predecesseurs;


            int posEtatInTabPredecesseur = chercherPosEtatDansTab(etat, predecesseurDeEtat);

            if(posEtatInTabPredecesseur != -1){
                // ici on passe par le vrai tableau et non par la copie
                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->predecesseurs
                .erase(tabEtats[posEtatInTabEtat]
                    ->successeurs[i]
                    ->predecesseurs.begin()
                       + posEtatInTabPredecesseur);


                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->poidsPredecesseur
                .erase(tabEtats[posEtatInTabEtat]
                    ->successeurs[i]
                    ->poidsPredecesseur.begin()
                       + posEtatInTabPredecesseur);

            }

            // /!\ c'est une copie faite pour la recherche
            vector<Etat*> successeurDeEtat = successeurs[i]->successeurs;
            int posEtatInTabSuccesseur = chercherPosEtatDansTab(etat, successeurDeEtat);

            if(posEtatInTabSuccesseur != -1){
                // ici on passe par le vrai tableau pet non par la copie
                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->successeurs
                .erase(tabEtats[posEtatInTabEtat]
                    ->successeurs[i]
                    ->successeurs.begin()
                       + posEtatInTabSuccesseur);

                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->poidsSuccesseur
                .erase(tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->poidsSuccesseur.begin()
                   + posEtatInTabPredecesseur);
            }
        }

        tabEtats.erase(tabEtats.begin() + posEtatInTabEtat);
    }
}


int Graphe::chercherPosEtatDansTab(Etat* etatSearch, vector<Etat*> tabDeRecherche){
    for(unsigned int pos = 0; pos<tabDeRecherche.size(); pos++){
        if(tabDeRecherche[pos] == etatSearch){
            return pos;
        }
    }
    return -1;
}

/**
* return true s'il y a un circuit
* return false s'il n'y a pas de circuit
*/
bool Graphe::detectionCircuit(){
    Graphe copieGraphe = *this;


    copieGraphe.recherchePointsEntrees();
    while(copieGraphe.tabPointEntrees.size() != 0 && copieGraphe.tabEtats.size() != 0){
        for(unsigned int i = 0; i<copieGraphe.tabPointEntrees.size(); i++){
            // on supprime le point d'entree du graphe copié
            copieGraphe.supprEtat(copieGraphe.tabPointEntrees[i]);

            // on supprime l'etat du tableau des points d'entrees car on vient de le traité
            copieGraphe.tabPointEntrees.erase(copieGraphe.tabPointEntrees.begin() + i);
        }
        copieGraphe.recherchePointsEntrees();
    }
    if(copieGraphe.tabEtats.size() == 0){
            // il n'y a pas de circuit
        return false;
    }else if (copieGraphe.tabPointEntrees.size() == 0){
        // il y a un circuit
        return true;

        //TODO:  display le graphe pour montrer le circuit
        // (pour la trace / debug)
    }


}

void Graphe::calcRang(){
    /*
    Graphe copieGraphe = *this;
    copieGraphe.recherchePointsEntrees();
    int k = 0;
    while(copieGraphe.tabPointEntrees.size() != 0 && copieGraphe.tabEtats.size() != 0){
        for(unsigned int i = 0; i<copieGraphe.tabPointEntrees.size(); i++){
            // on supprime le point d'entree du graphe copié
            copieGraphe.supprEtat(copieGraphe.tabPointEntrees[i]);

            // on supprime l'etat du tableau des points d'entrees car on vient de le traité
            copieGraphe.tabPointEntrees.erase(copieGraphe.tabPointEntrees.begin() + i);
        }
        copieGraphe.recherchePointsEntrees();
    }
    */
}




void Graphe::niveau1(){
    displayGraphe();


    // verification un seul point d'entree
    recherchePointsEntrees();
    if(tabPointEntrees.size() > 1){
        // ne rien faire
    }
    else{
        // faire
    }
}




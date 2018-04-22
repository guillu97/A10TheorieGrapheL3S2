//
// Created by SPORE on 06/03/2018.
//


#include "Graphe.h"
#define SPACE 3





using namespace std;

Graphe::Graphe(string fileName, int level) {
    this->fileName = fileName;

    if (level == 3 || level == 4){
        if(importContrainte(fileName))
            this->importe = true;
        else
            this->importe = false;
    }else{
        if(importGraphe(fileName))
            this->importe = true;
        else
            this->importe = false;
    }

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
    this->matInc = new int*[this->nbSommet];
    for(int i = 0; i < this->nbSommet; i++)
    {
        this->matInc[i] = new int[this->nbSommet];
        for(int j = 0; j <this->nbSommet; j++){
            matInc[i][j] = autreGraphe.matInc[i][j];

        }
    }


    this->remplirGraphe();
}


bool Graphe::importGraphe(string fileName) {

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
        matInc = new int*[this->nbSommet];
        for(int i = 0; i < this->nbSommet; i++)
        {
            matInc[i] = new int[this->nbSommet];
            for(int j = 0; j <this->nbSommet; j++){
                matInc[i][j] = 0;

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
        this->remplirGraphe();

        file.close();  // on ferme le fichier



    }
    else{  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        this->importe = false;
        return false;
    }

    if(this->matAdj && this->matInc){
        this->importe = true;
        return true;
    }
    else{
        this->importe = false;
        return false;
    }

}


bool Graphe::importContrainte(string fileName){
    ifstream file(fileName.c_str(), ios::in);  // on ouvre le fichier en lecture, le fichier est dans le même dossier que l'executable
    file>>this->nbSommet;
    if (!file) return false;
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
    matInc = new int*[this->nbSommet];
    for(int i = 0; i < this->nbSommet; i++)
    {
        matInc[i] = new int[this->nbSommet];
        for(int j = 0; j <this->nbSommet; j++){
            matInc[i][j] = 0;

        }
    }


    //Tableau qui contient les poids de chaque Etat
    int* tableauPoid = new int[this->nbSommet];
    for(int i = 0; i < this->nbSommet; i++){
        int lEtat;
        int lePoid;
        file >> lEtat;
        file >> lePoid;
        tableauPoid[lEtat-1] = lePoid;
    }

    cout << "Contrainte" << endl;
    for(int i = 0; i < this->nbSommet; i++){

            int lEtat;
            file >> lEtat;
            int lePredecesseur;
            file >> lePredecesseur;
            cout << "Sommet " << lEtat << "  ";
            while(lePredecesseur != 0){
                matAdj[lePredecesseur-1][lEtat-1] = true;
                matInc[lePredecesseur-1][lEtat-1] = tableauPoid[lePredecesseur-1];
                cout << lePredecesseur << " ";
                file >> lePredecesseur;

            }
            cout << endl;

    }

    this->remplirGraphe();
    this->displayGraphe();
    this->displayEtatToMatriceAdjIncid();
    return true;
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
                tabEtats[etatDebut]->ajoutSuccesseur(tabEtats[etatFin], this->matInc[etatDebut][etatFin]);
                tabEtats[etatFin]->ajoutPredecesseur(tabEtats[etatDebut], this->matInc[etatDebut][etatFin]);
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
                if(matInc[i][j] == 0){
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
    cout << setw(SPACE) << left<< "//" << "| ";
    for(unsigned int j = 0; j < tabEtats.size(); j++)
        cout << setw(SPACE) << left << tabEtats[j]->getNom();
    cout << endl;
    for(unsigned int j = 0; j < tabEtats.size(); j++)
        cout << "-------";
    cout << endl;
    for(unsigned int i = 0; i < this->tabEtats.size(); i++){
        vector <Etat*> tabSuccesseursSuccesseurs = tabEtats[i]->successeurs;
        unsigned int k = 0;

        cout << setw(SPACE) << left << tabEtats[i]->getNom() << "| ";
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
    cout<<endl;
    cout << "****MATRICE D'INCIDENCE****" << endl << endl;
    cout << setw(SPACE) << left<< "//" << "| ";
    for(unsigned int j = 0; j < tabEtats.size(); j++)
        cout << setw(SPACE) << left << tabEtats[j]->getNom();
    cout << endl;
    for(unsigned int j = 0; j < tabEtats.size(); j++)
        cout << "-------";
    cout << endl;
    for(unsigned int i = 0; i < this->tabEtats.size(); i++){
        vector <Etat*> tabSuccesseursSuccesseurs = tabEtats[i]->successeurs;
        vector<int>tabPoidsSuccesseurs = tabEtats[i]->poidsSuccesseur;
        unsigned int k = 0;

        cout << setw(SPACE) << left << tabEtats[i]->getNom() << "| ";
        for(unsigned int j = 0; j < tabEtats.size(); j++){

            if ( k >= tabSuccesseursSuccesseurs.size())
                cout << setw(SPACE) << left << "/";
            else if(tabSuccesseursSuccesseurs[k]->getNom() == tabEtats[j]->getNom()){
                cout << setw(SPACE) << left << tabPoidsSuccesseurs[k];
                k++;
            }
            else
                cout << setw(SPACE) << left << "/";
        }
        cout << endl;
    }

}



void Graphe::affichageGraphe(){
    cout<<endl;
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
    cout<<endl;
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
    cout<<endl;

}

void Graphe::affichageRang(){
    cout<<"Tous les etats et leurs rangs : " <<endl;
    for(unsigned int i = 0; i<this->tabEtats.size(); i++){
        //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
        cout << "Etat " << tabEtats[i]->getNom() << " :"<<endl;
        cout<< "rang: [";
        cout<<tabEtats[i]->getRang();
        cout <<"]"<<endl;
    }
}



/** @brief (one liner)
  *
  * (documentation goes here)
  */
void Graphe::recherchePointsEntrees(){

    // cette somme permet de vérifier si l'état est présent parmi les successeurs de tous les états
    int sum = 0;
    // on va parcourir tout le tableau des états
    for(unsigned int i = 0; i<this->tabEtats.size(); i++){
            sum = 0;
            for(unsigned int j = 0; j<this->tabEtats.size(); j++){

                // /!\ ici tabSuccesseurs est une copie pour la recherche, il ne faut pas l'utiliser pour modifier des valeurs
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

void Graphe::recherchePointsSorties(){
    // cette somme permet de vérifier si l'état est présent parmi les prédécesseurs de tous les états
    int sum = 0;
    // on va parcourir tout le tableau des états
    for(unsigned int i = 0; i<this->tabEtats.size(); i++){
            sum = 0;
            for(unsigned int j = 0; j<this->tabEtats.size(); j++){

                // /!\ ici tabPredecesseurs est une copie pour la recherche, il ne faut pas l'utiliser pour modifier des valeurs
                // on récupère son tableau de predecesseurs
                vector<Etat*>tabPredecesseurs = tabEtats[tabEtats[j]->getNom()]->predecesseurs;


                // on recherche dans le tableau des predecesseurs de l'état  (tabEtat[tabEtats[j]->getNom()])
                // pour voir si l'état tabEtats[i]->getNom() est présent ou non.
                // si à la fin du 'for' sum = 0, alors létat n'est pas présent
                 for(unsigned int k = 0; k< tabPredecesseurs.size(); k++){
                    if(tabPredecesseurs[k]->getNom() == tabEtats[i]->getNom())
                        sum++;
                 }
            }
            if(sum == 0){
                tabPointSorties.push_back(tabEtats[i]);
            }
    }
}

void Graphe::displayPointSorties(){
    cout<<endl;
    cout<<endl;

    cout << "Points de sorties"<<endl;

    if(tabPointEntrees.size() == 0)
        cout<<"Il n y a pas de point de sortie"<<endl;
    else{
          for(unsigned int i = 0; i<tabPointSorties.size(); i++)
            cout<<"Etat "<< tabPointSorties[i]->getNom() <<endl;
    }
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
    // if copieGraphe.tabEtats.size() == 0 and copieGraphe.tabPointEntrees.size() == 0, il n'y a pas de circuit
    return false;

}

void Graphe::calcRang(){

    Graphe copieGraphe = *this;



    int k = 0;

    #if DEBUG == 1
        cout<<endl;
        cout<<"DEBUG:"<<endl;
        cout<<"Calcul du rang"<<endl;
    #endif // DEBUG

    while(copieGraphe.tabEtats.size() != 0){

        copieGraphe.recherchePointsEntrees();

        #if DEBUG == 1
            cout<< "Rang k= " <<k;
            copieGraphe.displayPointEntrees();
        #endif // DEBUG

        for(unsigned int i = 0; i<copieGraphe.tabPointEntrees.size(); i++){
            // index du point d'entrées dans tabEtats du graphe "this"
            int posPointEntrees = 0;
            // les tableaux n'ont pas les mêmes indices donc on ne peut pas utiliser chercherPosEtatDansTab()
            for(unsigned int j = 0; j<this->tabEtats.size(); j++){
                if(copieGraphe.tabPointEntrees[i]->getNom() == this->tabEtats[j]->getNom() )
                    posPointEntrees = j;
            }

            // on note le rang sur le graphe "this", et non sur le graphe copié
            this->tabEtats[posPointEntrees]->setRang(k);

            // on supprime le point d'entree du graphe copié
            copieGraphe.supprEtat(copieGraphe.tabPointEntrees[i]);


        }
        unsigned int nbPointEntrees = copieGraphe.tabPointEntrees.size();
        for(unsigned int i = 0; i<nbPointEntrees; i++){
            // on supprime les etats du tableau des points d'entrees car on vient de les traiter
            copieGraphe.tabPointEntrees.pop_back();
        }

        k++;


        #if DEBUG == 1
            cout<< "Graphe apres suppression des points d entrees"<<endl;
            copieGraphe.displayEtatToMatriceAdjIncid();
        #endif // DEBUG
    }

    #if DEBUG == 1
        cout<<":DEBUG"<<endl;
        cout<<endl;
    #endif // DEBUG

}




void Graphe::niveau1(){

    if(this->importe){
        displayGraphe();
        string a;



        cout<<endl;
        cout<<endl;
        this->displayEtatToMatriceAdjIncid();
        cin >> a;
        cout<<endl;
        cout<<endl;
        this->affichageGraphe();

        if(!this->detectionCircuit()){
            this->calcRang();
            this->affichageGraphe();
            this->affichageRang();
        }
        else
            cout<<"Il y a un circuit dans ce graphe, le calcul des rangs ne peut pas etre effectue"<<endl;
    }
}


/**
*   On parcourt en largeur le graphe afin de vérifier si le point d'entrée
*   permet d'accéder à tous les sommets
*/
bool Graphe::verificationPointEntree(){


    vector<Etat*> tab;
    // ici on sait que le graphe n'a qu'un point d'entrée, on l'ajoute au tableau
    tab.push_back(tabPointEntrees[0]);

    unsigned int pointeur = 0;

    while(pointeur < tab.size()){

        if(!tab[pointeur]->successeurs.empty()){
            unsigned int tailleTabSuccesseurs = tab[pointeur]->successeurs.size();
            // on ajoute les successeurs au tableau
            for(unsigned int j=0; j < tailleTabSuccesseurs; j++){
                if(chercherPosEtatDansTab(tab[pointeur]->successeurs[j],tab) == -1)
                    tab.push_back(tab[pointeur]->successeurs[j]);
            }
        }
        pointeur++;

    }
    #if DEBUG == 1
        cout<<"DEBUG: affichage des etats parcourus lors de la verification des points d'entree"<<endl;
        for(unsigned int i = 0; i<tab.size(); i++)
            cout<< "[" <<tab[i]->getNom()<<"]"<<endl;
        cout<<":DEBUG"<<endl;
    #endif // DEBUG

    if((int)tab.size() == this->nbSommet)
        return true;
    else
        return false;
}



bool Graphe::verificationPointSortie(){
    vector<Etat*> tab;
    // ici on sait que le graphe n'a qu'un point de sortie, on l'ajoute au tableau
    tab.push_back(tabPointSorties[0]);

    unsigned int pointeur = 0;

    while(pointeur < tab.size()){

        if(!tab[pointeur]->predecesseurs.empty()){
            unsigned int tailleTabPredecesseur = tab[pointeur]->predecesseurs.size();
            // on ajoute les predecesseurs au tableau
            for(unsigned int j=0; j < tailleTabPredecesseur; j++){
                if(chercherPosEtatDansTab(tab[pointeur]->predecesseurs[j],tab) == -1)
                    tab.push_back(tab[pointeur]->predecesseurs[j]);
            }
        }
        pointeur++;

    }
    #if DEBUG == 1
        cout<<"DEBUG: affichage des etats parcourus lors de la verification"<<endl;
        for(unsigned int i = 0; i<tab.size(); i++)
            cout<< "[" <<tab[i]->getNom()<<"]"<<endl;
        cout<<":DEBUG"<<endl;
    #endif // DEBUG

    if((int)tab.size() == this->nbSommet)
        return true;
    else
        return false;
}

bool Graphe::verificationValeurArcNonNulle(){

    // on parcourt tous les tableaux de poids, et on vérifie que chaque poids est > 0, s'il ne l'est pas on return false

    for(unsigned int i=0; i<this->tabEtats.size(); i++){
        for(unsigned int j = 0; j<this->tabEtats[i]->poidsSuccesseur.size(); j++){
            if(this->tabEtats[i]->poidsSuccesseur[j] < 0)
                return false;
        }
    }
    // on a parcourut tous les poids, ils sont tous >= 0
    return true;

}

/**
*   On vérifie que les arcs partant d'un même sommet ont tous la même valeur
*/
bool Graphe::verificationValeurArc(){

    for(unsigned int i=0; i<this->tabEtats.size(); i++){

        int valeurRef = -1;
        if(this->tabEtats[i]->poidsSuccesseur.size() != 0)
            valeurRef = this->tabEtats[i]->poidsSuccesseur;

        for(unsigned int j = 0; j<this->tabEtats[i]->poidsSuccesseur.size(); j++){
            if(this->tabEtats[i]->poidsSuccesseur[j] != valeurRef)
                return false;
        }
    }
    return true;
}

void Graphe::niveau2(){

    if(this->importe){
        displayGraphe();



        cout<<endl;
        cout<<endl;
        this->displayEtatToMatriceAdjIncid();
        cout<<endl;
        cout<<endl;
        this->affichageGraphe();


        // verification un seul point d'entree
        recherchePointsEntrees();
        if(tabPointEntrees.size() == 1){
                // verification un seul point de sortie
            recherchePointsSorties();
            if(tabPointSorties.size() == 1){
                if(!this->detectionCircuit()){
                    if(verificationPointEntree()){
                        if(verificationPointSortie()){
                            if(verificationValeurArcNonNulle()){
                                if(verificationValeurArc()){
                                    this->calcRang();
                                    this->affichageGraphe();
                                    this->affichageRang();
                                }else{
                                    cout<<" verificationValeurArc faux!"<<endl;
                                }
                            }else{
                                cout<<"Le graphe contient au moins un arc dont la valeur est negative"<<endl;
                            }
                        }else{
                            cout<< "Le graphe n'a pas de point de sortie accessible par tous les sommets"<<endl;
                        }
                    }else{
                        cout<< "Le graphe n'a pas de point d'entree ayant acces a tous les sommets"<<endl;
                    }
                }else{
                    cout<< "Il y a un circuit dans le graphe"<<endl;
                }
            }else{
                cout<<"Il y a plusieurs points de sortie dans le graphe"<<endl;
            }
        }else{
            cout<<"Il y a plusieurs points d'entree dans le graphe"<<endl;
        }

    }

}




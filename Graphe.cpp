//
// Created by SPORE on 06/03/2018.
//


#include "Graphe.h"






using namespace std;

Graphe::Graphe(string fileName) {
    this->fileName = fileName;
    importGraphe(fileName);
}

Graphe::Graphe(Graphe& g){
    this->fileName = g.fileName;
    this->nbSommet = g.nbSommet;
    this->nbArc = g.nbArc;
    this->matAdj = g.matAdj;
    this->matInc = g.matInc;
    this->tabPointEntree = g.tabPointEntree;
}


void Graphe::importGraphe(string fileName) {

    ifstream file(fileName.c_str(), ios::in);  // on ouvre le fichier en lecture, le fichier est dans le même dossier que l'executable


    if(file)  // si l'ouverture a réussi
    {


        file >> this->nbSommet;
        file >> this->nbArc;




        // créer tableau de booléen 2d   (matrice carrée de hauteur nb sommet)  toutes les cases sont initialisées à false


        /* En utilisant un bool**

        matAdj = new bool*[this->nbSommet];
        for(int i = 0; i < this->nbSommet; i++)
        {
            matAdj[i] = new bool[this->nbSommet];
            for(int j = 0; j <this->nbSommet; j++){
                matAdj[i][j] = false;
            }
        }
        */


        // en utilisant vector<vector<bool>>
        for(int i = 0; i < this->nbSommet; i++){
            vector<bool> row;
            for(int j = 0; j <this->nbSommet; j++){
                row.push_back(false);
            }
            matAdj.push_back(row);
        }

        // créer tableau de int 2d  (matrice carrée de hauteur nb sommet) toutes les cases sont initialisées à 0

       /*
       matInc = new double*[this->nbSommet];
        for(int i = 0; i < this->nbSommet; i++)
        {
            matInc[i] = new double[this->nbSommet];
            for(int j = 0; j <this->nbSommet; j++){
                matInc[i][j] = NAN;

            }
        }

        */

        // en utilisant vector< vector<int> >
        for(int i = 0; i < this->nbSommet; i++){
            vector<int> row;
            for(int j = 0; j <this->nbSommet; j++){
                row.push_back(0);
            }
            matInc.push_back(row);
        }




        // remplir matAdj, matInc, tabEtats et tabArc
        int etatDebut, etatFin, poids;

        for(int i = 0; i < this->nbArc; i++){

            file >> etatDebut;

            file >> etatFin;

            file >> poids;


            #if DEBUG == 1
                cout<<endl;
                cout<<endl;
                cout <<"DEBUG : "<<endl;
                cout << "etatDebut: " << etatDebut << " ";

                cout << "etatFin: " << etatFin<< " ";

                cout<< "poids: " << poids << endl;

                cout <<" : DEBUG"<<endl;
                cout<<endl;
                cout<<endl;
            #endif // DEBUG


            // remplir une case matAdj avec true
            matAdj[etatDebut][etatFin] = true;

            //remplir une case matInc avec son poids
            matInc[etatDebut][etatFin] = poids;


        }

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

    if(matAdj.size() != 0){
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
    if(matInc.size() != 0){
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


void Graphe::recherchePointsEntree(){

    // en utilisant la matrice d'adjacence
    int sum = 0;
    for(int j = 0; j<this->nbSommet; j++){
        sum = 0;
        for(int i = 0; i<this->nbSommet; i++){
            //cout<< "matrice d adjacence en  ["<<i<<"]"<<"["<<j<<"] " << matAdj[i][j] <<endl;
            if(matAdj[i][j]){
                sum++;
            }
        }
        cout<<endl;

        if(sum == 0){
            tabPointEntree.push_back(j);
        }
    }

    #if DEBUG == 1
        cout<<endl;
        cout<<endl;
        cout <<"////// DEBUG : "<<endl;
        displayPointEntree();
        cout <<"////// : DEBUG"<<endl;
        cout<<endl;
        cout<<endl;
    #endif // DEBUG


}

void Graphe::displayPointEntree(){
    cout<<endl;
    cout<<endl;

    cout << "Points d'entrees"<<endl;

    // En utilisant la matrice d'adjacence

    if(tabPointEntree.size() == 0)
        cout<<"Il n y a pas de point d entree"<<endl;
    else{
        for(unsigned int i = 0; i<tabPointEntree.size(); i++)
            cout<<"Etat "<< tabPointEntree[i] <<endl;
    }

    cout<<endl;
    cout<<endl;
}


/**
* Retourne true si il y a un circuit false s'il n'y en a pas
*/
bool Graphe::detectionCircuit(){

    // copie des matrices
    Graphe copieGraphe = *this;

    #if DEBUG == 1
        cout<<endl;
        cout<<endl;
        cout <<"////// DEBUG : "<<endl;
        cout << "copieGraphe : " <<endl;
        copieGraphe.displayGraphe();
        cout <<"////// : DEBUG"<<endl;
        cout<<endl;
        cout<<endl;
    #endif // DEBUG

    /* test de copie (à ustiliser avec un graphe dont la matAdj à false pour [0][0]
        matAdj[0][0] = true;

        cout<<endl;
        cout << "111111111111111111"<<endl;
        displayGraphe();
        cout<<endl;
        cout << "2222222222222222"<<endl;
        copieGraphe.displayGraphe();
    */

    // indique s'il n'y a pas de circuit (true), ou s'il y en a un (false)
    bool pasDeCircuit = false;


    // test remise à zero car on fait la recherche dès le début du do while
    // ( on peut aussi éviter de copier le tabPointEntree dans la copieGraphe, à VOIR)
    copieGraphe.tabPointEntree = vector<int>();

    // on effectue la recherche tant qu'on trouve des points d'entrée
    do{
        // on recherche les points d'entrés sur la matrice copiée

        //cout << "entrée avant" <<endl;
        //copieGraphe.displayPointEntree();
        copieGraphe.recherchePointsEntree();
        //cout << "entrée après" <<endl;
        //copieGraphe.displayPointEntree();

        // besoin de fixer la taille, vu qu'on supprime en même temps
        const unsigned int tabPointEntreeSize = copieGraphe.tabPointEntree.size();
        // on selectionne les lignes qui représentent les points d'entrée dans la matAdj
        for(unsigned int k = 0; k<tabPointEntreeSize; k++){

            //cout <<"test " <<k<< copieGraphe.tabPointEntree[k] <<endl;
            for(int j = 0; j<copieGraphe.nbSommet; j++){
                    // on met à false toutes les colonnes sur la ligne d'un point d'entrée
                    matAdj[copieGraphe.tabPointEntree[k]][j] = false;
                    // puis on passe au suivant point d'entrée
            }
            // on supprime le point d'entrée du tableau
            copieGraphe.tabPointEntree.erase(copieGraphe.tabPointEntree.begin());
        }
    }while(copieGraphe.tabPointEntree.size() != 0);


    //TODO: afficher le circuit

    // lorsqu'on ne trouve pas de points
    if(copieGraphe.verifMatAdjVide()){
        pasDeCircuit = false;
    }
    pasDeCircuit = true;
    return pasDeCircuit;

}

bool Graphe::verifMatAdjVide(){
    for(int i=0; i<this->nbSommet; i++){
        for(int j = 0; j<this->nbSommet; j++){
            if(this->matAdj[i][j] != false)
                return false;
        }
    }
    return true;
}

void Graphe::niveau1(){
    // TODO: ajouter un truc du genre if bien importé displayGraphe()
    displayGraphe();
    recherchePointsEntree();
    if(!detectionCircuit())
        cout << "pas de circuit" <<endl;
    else
        cout << "un circuit" <<endl;
}




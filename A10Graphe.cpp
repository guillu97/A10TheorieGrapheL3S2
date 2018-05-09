//
// Created by SPORE on 06/03/2018.
//


#include "A10Graphe.h"
#define SPACE 3


std::ofstream log_file(
        "A10log_file.txt", std::ios_base::out | std::ios_base::app );


using namespace std;



Graphe::Graphe(string fileName, int level) {
    this->fileName = fileName;

    this->nbSommet = 0;
    this->nbArc = 0;
    this->importe = false;

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

Graphe::Graphe(Graphe* autreGraphe){


    this->fileName = autreGraphe->fileName;

    this->nbSommet = autreGraphe->nbSommet;

    this->nbArc = autreGraphe->nbArc;


    this->matAdj = autreGraphe->grapheToMatAdjContraintes();


    this->matInc = autreGraphe->grapheToMatIncContraintes();




    this->remplirGraphe();

    for(unsigned int i=0; i< tabEtats.size(); i++)
        tabEtats[i]->setNom(tabEtats[i]->getNom() + 1);

}


bool Graphe::importGraphe(string fileName) {

    ifstream file(fileName.c_str(), ios::in);  // on ouvre le fichier en lecture, le fichier est dans le même dossier que l'executable


    if(!file){  // si l'ouverture n'a pas réussi
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return false;
    }






    // Un test pour voir si on envoie un graphe de contraintes à cette fonction


    string temp = "";
    getline(file, temp);
    getline(file, temp);



    std::size_t pos = temp.find(" ");      // position of " " in str

    bool grapheNormal = false;
    // si l'on ne trouve pas d'espace sur la deuxième ligne
    if(pos == string::npos)
        grapheNormal = true;

        // met le curseur de lecture du fichier au debut
    file.seekg(ios_base::beg);


    if(!grapheNormal){
        cout<< "Le fichier n'est pas dans le bon format, c'est peut etre un tableau de contrainte" <<endl;
        cout<<endl;
        return false;
    }
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
                log_file <<"DEBUG : lecture du fichier txt "<<endl;
        #endif // DEBUG

        for(int i = 0; i < this->nbArc; i++){

            file >> etatDebut;

            file >> etatFin;

            file >> poids;


            #if DEBUG == 1
                //Log::write_to_log("DEBUG : lecture du fichier txt ");
                log_file << "etatDebut: " << etatDebut << " ";

                log_file<< "etatFin: " << etatFin<< " ";

                log_file<< "poids: " << poids << endl;
            #endif // DEBUG

            // remplir une case matAdj avec true
            matAdj[etatDebut][etatFin] = true;

            //remplir une case matInc avec son poids
            matInc[etatDebut][etatFin] = poids;

        }

        #if DEBUG == 1
                log_file <<": DEBUG "<<endl;
        #endif // DEBUG


        // test
        this->remplirGraphe();

        file.close();  // on ferme le fichier






    if(this->matAdj && this->matInc){
        return true;
    }
    else{
        return false;
    }


}


bool Graphe::importContrainte(string fileName){
    ifstream file(fileName.c_str(), ios::in);  // on ouvre le fichier en lecture, le fichier est dans le même dossier que l'executable

    if (!file){
        // si l'ouverture n'a pas réussi
        cerr << "Impossible d'ouvrir le fichier !" << endl;

        return false;
    }


        // Un test pour voir si on envoie un graphe de contraintes à cette fonction

    string temp = "";
    getline(file, temp);
    getline(file, temp);



    std::size_t pos = temp.find(" ");      // position of " " in str

    bool grapheContraintes = true;
    // si l'on ne trouve pas d'espace sur la deuxième ligne
    if(pos == string::npos)
        grapheContraintes = false;

        // met le curseur de lecture du fichier au debut
    file.seekg(ios_base::beg);


    if(!grapheContraintes){
        cout<< "Le fichier n'est pas dans le bon format, ce n'est pas un tableau de contrainte" <<endl;
        cout<<endl;
        return false;
    }




        file>>this->nbSommet;
        cout<< "nb sommet "<<this->nbSommet<<endl;

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

        //  sauvegarde de ce tableau, car on en a besoin pour la creation des points de sorties
        tabPoidsEtat = tableauPoid;

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
        cout<<"avant remplir graphe"<<endl;

        if(this->remplirGrapheInteract()){
            this->displayGraphe();
            this->displayEtatToMatriceAdjIncid();
            return true;
        }
        else
            return false;



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
        log_file << endl;
        log_file<< "DEBUG : " <<endl;
        log_file<< "Les etats presents: " <<endl;
        for(int i = 0; i<this->nbSommet; i++ ){
            log_file << tabEtats[i]->getNom() << " ";
        }
        log_file<<endl;
        log_file<< ": DEBUG" <<endl;
        log_file<<endl;
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

            log_file << endl;
            log_file << endl;
            log_file << "DEBUG : " <<endl;

            log_file<< "Tous les etats et leurs successeurs : "<<endl;
            for(unsigned int i = 0; i<this->tabEtats.size(); i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                log_file<< "Etat " << tabEtats[i]->getNom() << " :"<<endl;
                log_file<< "successeurs: [ ";
                for(unsigned int j = 0; j<tabEtats[i]->successeurs.size(); j++){
                    log_file << tabEtats[i]->successeurs[j]->getNom() << " ";
                }
                log_file<<"]"<<endl;
            }

            log_file<< "Tous les etats et leurs predecesseurs : "<<endl;
            for(unsigned int i = 0; i<this->tabEtats.size(); i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                log_file<< "Etat " << tabEtats[i]->getNom() << " :"<<endl;
                log_file<< "predecesseurs: [ ";
                for(unsigned int j = 0; j<tabEtats[i]->predecesseurs.size(); j++){
                    log_file << tabEtats[i]->predecesseurs[j]->getNom() << " ";;
                }
                log_file <<"]"<<endl;
            }

            log_file<<": DEBUG"<<endl;
            log_file<< endl;
            log_file<< endl;

        #endif // DEBUG


}

bool Graphe::remplirGrapheInteract(){


    // create a tabEtat with all the states, then we will add the successors
    for(int i = 1; i<=this->nbSommet; i++){
        tabEtats.push_back(new Etat(i));
    }

    #if DEBUG == 1
        log_file<< endl;
        log_file<< "DEBUG : " <<endl;
        log_file<< "Les etats presents: " <<endl;
        for(int i = 0; i<this->nbSommet; i++ ){
            log_file << tabEtats[i]->getNom() << " ";
        }
        log_file<<endl;
        log_file<< ": DEBUG" <<endl;
        log_file <<endl;
    #endif // DEBUG

    bool pasDeCircuit = true;



    for(int etatDebut = 0; etatDebut < this->nbSommet; etatDebut++){
        for(int etatFin = 0; etatFin < this->nbSommet; etatFin++){
                        //we add the successor to the tabEtats
            if(matAdj[etatDebut][etatFin]){
                this->tabEtats[etatDebut]->ajoutSuccesseur(tabEtats[etatFin], this->matInc[etatDebut][etatFin]);
                this->tabEtats[etatFin]->ajoutPredecesseur(tabEtats[etatDebut], this->matInc[etatDebut][etatFin]);


                vector <Etat*> circuit = this->detectionCircuitInteract();

                #if DEBUG == 1
                    displayEtatToMatriceAdjIncid();
                #endif // DEBUG



                if(!circuit.empty()){   // s'il y a un circuit
                    pasDeCircuit = false;


                    // il y a un problème lors de la prise en  compte de la contrainte ‘A a besoin de C’
                    // avec les contraintes déjà intégrées ‘B a besoin de A’ et ‘C a besoin de B’
                    cout<<"Il y a un probleme lors de la prise en  compte de la contrainte \'"
                    <<  etatFin + 1 <<" a besoin de "<<  etatDebut + 1<<"\' "
                    <<"avec les contraintes deja integrees: "<<endl;
                    for(unsigned int i=0; i<circuit.size(); i++){
                        if(circuit[i]->getNom() != etatDebut + 1){
                            for(unsigned int j=0; j<circuit[i]->successeurs.size(); j++)
                                cout<<"\'"<<circuit[i]->successeurs[j]->getNom()<< " a besoin de "<<  circuit[i]->getNom()
                                <<"\'"<<endl;
                        }
                    }
                    cout<<endl;
                    cout<<"Les etats suivant appartiennent a un circuit"<<endl;
                    for(unsigned int i=0; i<circuit.size(); i++){
                        cout<<circuit[i]->getNom()<< " ";
                    }
                    cout<<endl;
                    cout<<endl;
                    cout<<endl;


                }
            }
        }
    }

    return pasDeCircuit;



    #if DEBUG == 1

            log_file << endl;
            log_file << endl;
            log_file << "DEBUG : " <<endl;

            log_file << "Tous les etats et leurs successeurs : "<<endl;
            for(unsigned int i = 0; i<this->tabEtats.size(); i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                log_file << "Etat " << tabEtats[i]->getNom() << " :"<<endl;
                log_file<< "successeurs: [ ";
                for(unsigned int j = 0; j<tabEtats[i]->successeurs.size(); j++){
                    log_file << tabEtats[i]->successeurs[j]->getNom() << " ";
                }
                log_file <<"]"<<endl;
            }

            log_file << "Tous les etats et leurs predecesseurs : "<<endl;
            for(unsigned int i = 0; i<this->tabEtats.size(); i++){
                //vector <Etat*> tempTabSuccesseurs = tabEtats[i]->getSuccesseurs();
                log_file << "Etat " << tabEtats[i]->getNom() << " :"<<endl;
                log_file<< "predecesseurs: [ ";
                for(unsigned int j = 0; j<tabEtats[i]->predecesseurs.size(); j++){
                    log_file << tabEtats[i]->predecesseurs[j]->getNom() << " ";;
                }
                log_file <<"]"<<endl;
            }

            log_file<<": DEBUG"<<endl;
            log_file << endl;
            log_file << endl;

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

    cout << "MatVal: " << endl;
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
    log_file << "****MATRICE D'ADJACENCE****" << endl << endl;
    cout << setw(SPACE) << left<< "//" << "| ";
    log_file << setw(SPACE) << left<< "//" << "| ";
    for(unsigned int j = 0; j < tabEtats.size(); j++){
        cout << setw(SPACE) << left << tabEtats[j]->getNom();
        log_file << setw(SPACE) << left << tabEtats[j]->getNom();
    }
    cout << endl;
    log_file << endl;
    for(unsigned int j = 0; j < tabEtats.size(); j++){
        cout << "-------";
        log_file << "-------";
    }
    cout << endl;
    log_file << endl;
    for(unsigned int i = 0; i < this->tabEtats.size(); i++){
        vector <Etat*> tabSuccesseursSuccesseurs = tabEtats[i]->successeurs;
        unsigned int k = 0;

        cout << setw(SPACE) << left << tabEtats[i]->getNom() << "| ";
        log_file << setw(SPACE) << left << tabEtats[i]->getNom() << "| ";
        for(unsigned int j = 0; j < tabEtats.size(); j++){

            if ( k >= tabSuccesseursSuccesseurs.size()){
                cout << setw(SPACE) << left << 0;
                log_file << setw(SPACE) << left << 0;
            }
            else if(tabSuccesseursSuccesseurs[k]->getNom() == tabEtats[j]->getNom()){
                cout << setw(SPACE) << left << 1;
                log_file << setw(SPACE) << left << 1;
                k++;
            }
            else{
                cout << setw(SPACE) << left << 0;
                log_file << setw(SPACE) << left << 0;
            }
        }
        cout << endl;
        log_file << endl;
    }
    cout<<endl;
    log_file<<endl;
    cout << "****MATRICE DE VALEUR****" << endl << endl;
    log_file << "****MATRICE DE VALEUR****" << endl << endl;
    cout << setw(SPACE) << left<< "//" << "| ";
    log_file << setw(SPACE) << left<< "//" << "| ";
    for(unsigned int j = 0; j < tabEtats.size(); j++){
        cout << setw(SPACE) << left << tabEtats[j]->getNom();
        log_file << setw(SPACE) << left << tabEtats[j]->getNom();
    }
    cout << endl;
    log_file << endl;
    for(unsigned int j = 0; j < tabEtats.size(); j++){
        cout << "-------";
        log_file << "-------";
    }
    cout << endl;
    log_file << endl;
    for(unsigned int i = 0; i < this->tabEtats.size(); i++){
        vector <Etat*> tabSuccesseursSuccesseurs = tabEtats[i]->successeurs;
        vector<int>tabPoidsSuccesseurs = tabEtats[i]->poidsSuccesseur;
        unsigned int k = 0;

        cout << setw(SPACE) << left << tabEtats[i]->getNom() << "| ";
        log_file << setw(SPACE) << left << tabEtats[i]->getNom() << "| ";
        for(unsigned int j = 0; j < tabEtats.size(); j++){

            if ( k >= tabSuccesseursSuccesseurs.size()){
                cout << setw(SPACE) << left << "/";
                log_file << setw(SPACE) << left << "/";
            }
            else if(tabSuccesseursSuccesseurs[k]->getNom() == tabEtats[j]->getNom()){
                cout << setw(SPACE) << left << tabPoidsSuccesseurs[k];
                log_file << setw(SPACE) << left << tabPoidsSuccesseurs[k];
                k++;
            }
            else{
                cout << setw(SPACE) << left << "/";
                log_file << setw(SPACE) << left << "/";
            }
        }
        cout << endl;
        log_file << endl;
    }

}

bool** Graphe::grapheToMatAdj(){

    bool** tempMatAdj = NULL;


        // créer tableau de booléen 2d   (matrice carrée de hauteur nb sommet)  toutes les cases sont initialisées à false
    tempMatAdj = new bool*[this->nbSommet];
    for(int i = 0; i < this->nbSommet; i++)
    {
        tempMatAdj[i] = new bool[this->nbSommet];
        for(int j = 0; j <this->nbSommet; j++){
            tempMatAdj[i][j] = false;
        }
    }




    for(unsigned int i = 0; i < this->tabEtats.size(); i++){
        vector <Etat*> tabSuccesseurs = tabEtats[i]->successeurs;

        int nomEtat =  this->tabEtats[i]->getNom();
        for(unsigned int j = 0; j < tabSuccesseurs.size(); j++){
            tempMatAdj[nomEtat][tabSuccesseurs[j]->getNom()] = true;
        }
    }



    return tempMatAdj;

}

bool** Graphe::grapheToMatAdjContraintes(){

    bool** tempMatAdj = NULL;


        // créer tableau de booléen 2d   (matrice carrée de hauteur nb sommet)  toutes les cases sont initialisées à false
    tempMatAdj = new bool*[this->nbSommet];
    for(int i = 0; i < this->nbSommet; i++)
    {
        tempMatAdj[i] = new bool[this->nbSommet];
        for(int j = 0; j <this->nbSommet; j++){
            tempMatAdj[i][j] = false;
        }
    }




    for(unsigned int i = 0; i < this->tabEtats.size(); i++){
        vector <Etat*> tabSuccesseurs = tabEtats[i]->successeurs;

        int nomEtat =  this->tabEtats[i]->getNom() - 1;
        for(unsigned int j = 0; j < tabSuccesseurs.size(); j++){
            tempMatAdj[nomEtat][tabSuccesseurs[j]->getNom() - 1] = true;
        }
    }



    return tempMatAdj;

}

int** Graphe::grapheToMatInc(){

    int** tempMatInc = NULL;

    // créer tableau de int 2d  (matrice carrée de hauteur nb sommet) toutes les cases sont initialisées à 0
    tempMatInc = new int*[this->nbSommet];
    for(int i = 0; i < this->nbSommet; i++)
    {
        tempMatInc[i] = new int[this->nbSommet];
        for(int j = 0; j <this->nbSommet; j++){
            tempMatInc[i][j] = 0;

        }
    }


    for(unsigned int i = 0; i < this->tabEtats.size(); i++){
        vector <Etat*> tabSuccesseurs = tabEtats[i]->successeurs;
        vector <int> tabPoidsSuccesseurs = tabEtats[i]->poidsSuccesseur;

        int nomEtat =  tabEtats[i]->getNom();
        for(unsigned int j = 0; j < tabSuccesseurs.size(); j++){
            tempMatInc[nomEtat][tabSuccesseurs[j]->getNom()] = tabPoidsSuccesseurs[j];
        }
    }

    return tempMatInc;

}

int** Graphe::grapheToMatIncContraintes(){

    int** tempMatInc = NULL;

    // créer tableau de int 2d  (matrice carrée de hauteur nb sommet) toutes les cases sont initialisées à 0
    tempMatInc = new int*[this->nbSommet];
    for(int i = 0; i < this->nbSommet; i++)
    {
        tempMatInc[i] = new int[this->nbSommet];
        for(int j = 0; j <this->nbSommet; j++){
            tempMatInc[i][j] = 0;

        }
    }


    for(unsigned int i = 0; i < this->tabEtats.size(); i++){
        vector <Etat*> tabSuccesseurs = tabEtats[i]->successeurs;
        vector <int> tabPoidsSuccesseurs = tabEtats[i]->poidsSuccesseur;

        int nomEtat =  tabEtats[i]->getNom() - 1;
        for(unsigned int j = 0; j < tabSuccesseurs.size(); j++){
            tempMatInc[nomEtat][tabSuccesseurs[j]->getNom() - 1] = tabPoidsSuccesseurs[j];
        }
    }

    return tempMatInc;

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

        cout<< "PoidsPredecesseurs: [ ";
        for(unsigned int j = 0; j<tabEtats[i]->predecesseurs.size(); j++){
            cout << tabEtats[i]->poidsPredecesseur[j] << " ";
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

/*
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
*/


    for(unsigned int i = 0; i<tabEtats.size(); i++){
        if(tabEtats[i]->predecesseurs.empty())
            tabPointEntrees.push_back(tabEtats[i]);
    }



/*
    // En UTILISANT la matrice des valeurs

    int sum = 0;
    for(int i = 0; i<this->nbSommet; i++){
        sum = 0;
        for(int j = 0; j<this->nbSommet; j++){
            if(matAdj[j][i] == 1){
                sum++;
            }
        }



        if(sum == 0){
            int pos = 0;
            for(int k = 0; (unsigned int)k<tabEtats.size(); k++){
                if(tabEtats[k]->getNom() == i){
                    pos = i;
                }
            }
            tabPointEntrees.push_back(tabEtats[pos]);
        }
    }
*/
    #if DEBUG == 1
        log_file<< "DEBUG:"<<endl;
        displayPointEntrees();
        log_file<< ":DEBUG"<<endl;


    #endif // DEBUG


}

void Graphe::displayPointEntrees(){
    cout<<endl;
    cout<<endl;

    log_file<<endl;
    log_file<<endl;

    cout << "Points d'entrees"<<endl;
    log_file<< "Points d'entrees"<<endl;

    if(tabPointEntrees.size() == 0){
        cout<<"Il n y a pas de point d entree"<<endl;
        log_file<<"Il n y a pas de point d entree"<<endl;
    }
    else{
          for(unsigned int i = 0; i<tabPointEntrees.size(); i++){
            cout<<"Etat "<< tabPointEntrees[i]->getNom() <<endl;
            log_file<<"Etat "<< tabPointEntrees[i]->getNom() <<endl;
          }
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

    log_file<<endl;
    log_file<<endl;
}

void Graphe::recherchePointsSorties(){

    /*
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

    */
    for(unsigned int i = 0; i<tabEtats.size(); i++){
        if(tabEtats[i]->successeurs.empty())
            tabPointSorties.push_back(tabEtats[i]);
    }

    #if DEBUG == 1
        log_file<< "DEBUG:"<<endl;
        displayPointSorties();
        log_file<< ":DEBUG"<<endl;


    #endif // DEBUG

}

void Graphe::displayPointSorties(){

    log_file<<endl;
    log_file<<endl;

    cout<<endl;
    cout<<endl;

    cout << "Points de sorties"<<endl;
    log_file << "Points de sorties"<<endl;

    if(tabPointEntrees.size() == 0){
        cout<<"Il n y a pas de point de sortie"<<endl;
        log_file<<"Il n y a pas de point de sortie"<<endl;
    }
    else{
          for(unsigned int i = 0; i<tabPointSorties.size(); i++){
            cout<<"Etat "<< tabPointSorties[i]->getNom() <<endl;
            log_file<<"Etat "<< tabPointSorties[i]->getNom() <<endl;
          }
    }
}

vector<Etat*> Graphe::suppr(vector<Etat*> tab, Etat* etat){
    vector<Etat*> temp;
    for(unsigned int i=0; i<tab.size(); i++){
        if(tab[i]->getNom() != etat->getNom())
            temp.push_back(tab[i]);
    }
    return temp;
}

vector<int> Graphe::suppr(vector<int> tab, int poids){
    vector<int> temp;
    for(unsigned int i=0; i<tab.size(); i++){
        if(tab[i] != poids)
            temp.push_back(tab[i]);
    }
    return temp;
}

void Graphe::supprEtat(Etat* etat){
    //int posEtatInTabEtat = chercherPosEtatDansTab(etat, tabEtats);

    int posEtatInTabEtat= -1;
    for(unsigned int pos = 0; pos<this->tabEtats.size(); pos++){
        if(this->tabEtats[pos]->getNom() == etat->getNom()){
            posEtatInTabEtat = pos;
        }
    }

    if(posEtatInTabEtat == -1){
        cout<<"etat non trouve"<<endl;
    }

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



                tabEtats[posEtatInTabEtat]->successeurs[i]->predecesseurs =
                this->suppr(tabEtats[posEtatInTabEtat]->successeurs[i]->predecesseurs, tabEtats[posEtatInTabEtat]->successeurs[i]->predecesseurs[posEtatInTabPredecesseur]  );

                /*
                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->predecesseurs
                .erase(tabEtats[posEtatInTabEtat]
                    ->successeurs[i]
                    ->predecesseurs.begin()
                       + posEtatInTabPredecesseur);
                       */


                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->poidsPredecesseur = this->suppr(tabEtats[posEtatInTabEtat]->successeurs[i]->poidsPredecesseur,
                                                   tabEtats[posEtatInTabEtat]->successeurs[i]->poidsPredecesseur[posEtatInTabPredecesseur]);

                    /*
                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->poidsPredecesseur
                .erase(tabEtats[posEtatInTabEtat]
                    ->successeurs[i]
                    ->poidsPredecesseur.begin()
                       + posEtatInTabPredecesseur);
                       */

            }

            // /!\ c'est une copie faite pour la recherche
            vector<Etat*> successeurDeEtat = successeurs[i]->successeurs;
            int posEtatInTabSuccesseur = chercherPosEtatDansTab(etat, successeurDeEtat);

            if(posEtatInTabSuccesseur != -1){
                // ici on passe par le vrai tableau pet non par la copie

                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->successeurs = this->suppr(tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->successeurs, tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->successeurs[posEtatInTabSuccesseur]);

                /*
                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->successeurs
                .erase(tabEtats[posEtatInTabEtat]
                    ->successeurs[i]
                    ->successeurs.begin()
                       + posEtatInTabSuccesseur);
                       */

                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->poidsSuccesseur = this->suppr(tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->poidsSuccesseur, tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->poidsSuccesseur[posEtatInTabPredecesseur]);

                /*
                tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->poidsSuccesseur
                .erase(tabEtats[posEtatInTabEtat]
                ->successeurs[i]
                ->poidsSuccesseur.begin()
                   + posEtatInTabPredecesseur);
                   */
            }
        }

        tabEtats = this->suppr(tabEtats, tabEtats[posEtatInTabEtat]);
        //tabEtats.erase(tabEtats.begin() + posEtatInTabEtat);
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



            // on supprime l'etat du tableau des points d'entrees car on vient de le traiter

            copieGraphe.tabPointEntrees = copieGraphe.suppr(copieGraphe.tabPointEntrees, copieGraphe.tabPointEntrees[i]);
            //copieGraphe.tabPointEntrees.erase(copieGraphe.tabPointEntrees.begin() + i);

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




vector<Etat*> Graphe::detectionCircuitInteract(){

    Graphe copieGraphe = this;

   // copieGraphe.copieGrapheInteract(*this);











    vector<Etat*> circuit;



    copieGraphe.recherchePointsEntrees();



    while(copieGraphe.tabPointEntrees.size() != 0 && copieGraphe.tabEtats.size() != 0){


        for(unsigned int i = 0; i<copieGraphe.tabPointEntrees.size(); i++){




            // on supprime le point d'entree du graphe copié
            copieGraphe.supprEtat(copieGraphe.tabPointEntrees[i]);


            // on supprime l'etat du tableau des points d'entrees car on vient de le traiter

            copieGraphe.tabPointEntrees = copieGraphe.suppr(copieGraphe.tabPointEntrees, copieGraphe.tabPointEntrees[i]);
            //copieGraphe.tabPointEntrees.erase(copieGraphe.tabPointEntrees.begin() + i);

        }
        copieGraphe.recherchePointsEntrees();
    }

    // s'il y a un circuit
    // on retourne ce circuit
    // s'il n'y a pas de circuit cela retourne un vecteur vide ( à verifier : if(detectionCircuitInteract().empty()) )
    circuit = copieGraphe.tabEtats;
    return circuit;

}


void Graphe::calcRang(){

    Graphe copieGraphe = *this;



    int k = 0;

    #if DEBUG == 1
        log_file<<endl;
        log_file<<"DEBUG:"<<endl;
        log_file<<"Calcul du rang"<<endl;
    #endif // DEBUG

    while(copieGraphe.tabEtats.size() != 0){

        copieGraphe.recherchePointsEntrees();

        #if DEBUG == 1
            log_file<< "Rang k= " <<k;
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
            log_file<< "Graphe apres suppression des points d entrees"<<endl;
            copieGraphe.displayEtatToMatriceAdjIncid();
        #endif // DEBUG
    }

    #if DEBUG == 1
        log_file<<":DEBUG"<<endl;
        log_file<<endl;
    #endif // DEBUG

}

void Graphe::affichageRangTab(){
    cout<<endl;
    cout<<"Rang des etats:"<<endl;

    // recherche du rang max
    int rangMax = 0;
    for(unsigned int i=0; i< tabEtats.size(); i++){
        if(tabEtats[i]->getRang() > rangMax)
            rangMax = tabEtats[i]->getRang();
    }


    cout<<"Rang | Etats"<<endl;
    for(int rang=0; rang<=rangMax; rang++){
        cout<< setw(SPACE) << left << rang<< "  |";
        for(unsigned int i=0; i<tabEtats.size(); i++){
            if(tabEtats[i]->getRang() == rang)
                cout<< setw(SPACE) << left << tabEtats[i]->getNom()<< "  ";
        }
        cout<<endl;
    }
}


void Graphe::niveau1(){

    log_file<<endl;
    log_file<<"---------------------------------------------"<<endl;
    log_file<<"Niveau 1 :"<<endl;
    log_file<<endl;
    if(this->importe){
        displayGraphe();
        string a;



        cout<<endl;
        cout<<endl;
        this->displayEtatToMatriceAdjIncid();
        cout<<"Entrez y pour continuer"<<endl;
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
        log_file<<"DEBUG: affichage des etats parcourus lors de la verification des points d'entree"<<endl;
        for(unsigned int i = 0; i<tab.size(); i++){
            log_file<< "[" <<tab[i]->getNom()<<"]"<<endl;
        }
        log_file<<":DEBUG"<<endl;
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
        log_file<<"DEBUG: affichage des etats parcourus lors de la verification"<<endl;
        for(unsigned int i = 0; i<tab.size(); i++){
            log_file<< "[" <<tab[i]->getNom()<<"]"<<endl;
        }
        log_file<<":DEBUG"<<endl;
    #endif // DEBUG

    if((int)tab.size() == this->nbSommet)
        return true;
    else
        return false;
}

bool Graphe::verificationValeurArcNonNeg(){

    // on parcourt tous les tableaux de poids, et on vérifie que chaque poids est > 0, s'il ne l'est pas on return false

    for(unsigned int i=0; i<this->tabEtats.size(); i++){
        for(unsigned int j = 0; j<this->tabEtats[i]->poidsSuccesseur.size(); j++){
            if(this->tabEtats[i]->poidsSuccesseur[j] < 0){
                return false;
            }
        }
    }
    // on a parcourut tous les poids, ils sont tous >= 0
    return true;

}



bool Graphe::verificationValeurArcNonNegInteract(){

    // on parcourt tous les tableaux de poids, et on vérifie que chaque poids est > 0, s'il ne l'est pas on return false

    for(unsigned int i=0; i<this->tabEtats.size(); i++){
        for(unsigned int j = 0; j<this->tabEtats[i]->poidsSuccesseur.size(); j++){
            if(this->tabEtats[i]->poidsSuccesseur[j] < 0){
                    cout<<"Tache de duree negative:"<<endl;
                    cout<<"Tache: " << tabEtats[i]->getNom()<<endl;
                    cout<<"Duree: " << tabEtats[i]->poidsSuccesseur[j] <<endl;
                    char choix = 'c';
                    do{
                        cout<<"Voulez-vous changer la duree de cette tache? (y/n)"<<endl;
                        cin >> choix;
                    }while(choix != 'y' && choix != 'Y' && choix != 'n' && choix != 'N');

                    if(choix == 'y' || choix == 'Y'){
                        int newVal = -1;
                        do{
                            cout<<"Entrez une nouvelle duree superieure ou egale a 0:"<<endl;
                            cin >> newVal;
                        }while(newVal < 0);

                        // on change tous les poids des arcs de l'etat vers ses successeurs
                        for(unsigned int k = 0; k<this->tabEtats[i]->poidsSuccesseur.size(); k++)
                            tabEtats[i]->poidsSuccesseur[k] = newVal;
                        // on passe directement à l'etat suivant
                        j = this->tabEtats[i]->poidsSuccesseur.size();
                    }
                    else
                        return false;
            }
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
            valeurRef = this->tabEtats[i]->poidsSuccesseur[0];

        for(unsigned int j = 0; j<this->tabEtats[i]->poidsSuccesseur.size(); j++){
            if(this->tabEtats[i]->poidsSuccesseur[j] != valeurRef)
                return false;
        }
    }
    return true;
}

bool Graphe::verificationValeurArcInteract(){

    for(unsigned int i=0; i<this->tabEtats.size(); i++){

        int valeurRef = -1;
        if(this->tabEtats[i]->poidsSuccesseur.size() != 0)
            valeurRef = this->tabEtats[i]->poidsSuccesseur[0];

        for(unsigned int j = 0; j<this->tabEtats[i]->poidsSuccesseur.size(); j++){
            if(this->tabEtats[i]->poidsSuccesseur[j] != valeurRef){
                    cout<<"Probleme de duree de tache, plusieurs durees on ete trouvee pour une seule tache:"<<endl;
                    cout<<"Tache: " << tabEtats[i]->getNom()<<endl;
                    cout<<"Duree: " << tabEtats[i]->poidsSuccesseur[j] <<endl;
                    cout<<"Or la duree de reference pour cette tache etait: " <<valeurRef<<endl;
                    char choix = 'c';
                    do{
                        cout<<"Voulez-vous changer la duree de cette tache? (y/n)"<<endl;
                        cin >> choix;
                    }while(choix != 'y' && choix != 'Y' && choix != 'n' && choix != 'N');

                    if(choix == 'y' || choix == 'Y'){
                        int newVal = -1;
                        do{
                            cout<<"Entrez une nouvelle duree superieure ou egale a 0:"<<endl;
                            cin >> newVal;
                        }while(newVal < 0);

                        // on change tous les poids des arcs de l'etat vers ses successeurs
                        for(unsigned int k = 0; k<this->tabEtats[i]->poidsSuccesseur.size(); k++)
                            tabEtats[i]->poidsSuccesseur[k] = newVal;
                        // on passe directement à l'etat suivant
                        j = this->tabEtats[i]->poidsSuccesseur.size();
                    }
                    else
                        return false;


            }
        }
    }
    return true;
}

void Graphe::calcDatePlusTot(){
    vector<int>file;
    // ici on sait que le graphe n'a qu'un point d'entrée, on l'ajoute au tableau
    file.push_back(tabPointEntrees[0]->getNom());




    #if DEBUG == 1
        log_file<<endl;
        log_file<<endl;
        log_file<<"DEBUG: calcul de la date au plus tot"<<endl;
        int iteration = 0;
    #endif // DEBUG

    while(!file.empty()){

        #if DEBUG == 1
            log_file<< "-----------------------"<<endl;
            log_file<<"Iteration : "<<iteration<<endl;
            log_file<<"La file avant iteration: "<<endl;

            for(unsigned int i = 0; i<file.size(); i++){
                log_file<<file[i]<< " ";
            }
            log_file<<endl;
            iteration++;


            log_file<<endl;

        #endif // DEBUG

            // on cherche l'index de l'etat de la file dans le tabEtats


        int pos = 0;

        /*
        unsigned int i = 0;


        while(i != tabEtats.size() && tabEtats[i]->getNom() != pile[pointeur]){
                i++;
                pos = i;
        }
        */

        for(int i = 0; (unsigned int)i<tabEtats.size(); i++){
            if(tabEtats[i]->getNom() == file[0]){
                pos = i;
            }
        }


        if(!tabEtats[pos]->successeurs.empty()){
            unsigned int tailleTabSuccesseurs = tabEtats[pos]->successeurs.size();

            int dureeVersSuccesseur = tabEtats[pos]->poidsSuccesseur[0];

            int datePlusTotEtat = tabEtats[pos]->getDatePlusTot();

            // on ajoute les successeurs à la file
            for(unsigned int i=0; i < tailleTabSuccesseurs ; i++){
                int datePlusTotSuccesseur = tabEtats[pos]->successeurs[i]->getDatePlusTot();

                if(datePlusTotEtat + dureeVersSuccesseur >= datePlusTotSuccesseur)
                    tabEtats[pos]->successeurs[i]->setDatePlusTot(datePlusTotEtat + dureeVersSuccesseur);

                file.push_back(tabEtats[pos]->successeurs[i]->getNom());
            }

        }
        file.erase(file.begin());
        #if DEBUG == 1
            log_file<<endl;
            log_file<<"La file apres iteration: "<<endl;

            for(unsigned int i = 0; i<file.size(); i++)
                log_file<<file[i]<< " ";
            log_file<<endl;
            log_file<<endl;
            log_file<<"apres iteration:";
            displayDatePlusTot();
        #endif // DEBUG

    }

    #if DEBUG == 1
        log_file<<":"<<endl;
    #endif // DEBUG
}



void Graphe::displayDatePlusTot(){
    cout<<endl;
    cout<<endl;

    log_file<<endl;
    log_file<<endl;


    cout<< "Dates au plus tot des etats" <<endl;
    log_file<< "Dates au plus tot des etats" <<endl;
    for(unsigned int i=0; i< tabEtats.size(); i++){
        cout<< setw(SPACE) << left << tabEtats[i]->getNom()<< "  ";
        log_file<< setw(SPACE) << left << tabEtats[i]->getNom()<< "  ";
    }
    cout<<endl;
    log_file<<endl;
    for(unsigned int i=0; i< tabEtats.size(); i++){
        cout<< setw(SPACE) << left<< tabEtats[i]->getDatePlusTot() << "  ";
        log_file<< setw(SPACE) << left<< tabEtats[i]->getDatePlusTot() << "  ";
    }
    cout<<endl;
    cout<<endl;
    log_file<<endl;
    log_file<<endl;
}

void Graphe::calcDatePlusTard(float pourcentageDatePlusTard){
    vector<int>file;


    int datePlusTardOmega = 0;
    for(unsigned int i=0; i<tabEtats.size(); i++){
        if(datePlusTardOmega <= tabEtats[i]->getDatePlusTot())
            datePlusTardOmega = tabEtats[i]->getDatePlusTot() * pourcentageDatePlusTard;
    }


    // toutes les dates au plus tard des etats sont mises à la date d'omega
    for(unsigned int i=0; i<tabEtats.size(); i++){
        tabEtats[i]->setDatePlusTard(datePlusTardOmega);
    }


    recherchePointsSorties();
        // ici on sait que le graphe n'a qu'un point dde sortie, on l'ajoute au tableau
        // on met la date au plus tard du projet sur omega
    tabPointSorties[0]->setDatePlusTard(datePlusTardOmega);



    // on met omega dans la file
    file.push_back(tabPointSorties[0]->getNom());

    #if DEBUG == 1
        log_file<<endl;
        log_file<<endl;
        log_file<<"DEBUG: calcul de la date au plus tard"<<endl;
        int iteration = 0;
    #endif // DEBUG

    while(!file.empty()){




        #if DEBUG == 1
            log_file<< "-----------------------"<<endl;
            log_file<<"Iteration : "<<iteration<<endl;
            log_file<<"La file avant iteration: "<<endl;

            for(unsigned int i = 0; i<file.size(); i++)
                log_file<<file[i]<< " ";
            log_file<<endl;
            iteration++;


            log_file<<endl;

        #endif // DEBUG

            // on cherche l'index de l'etat de la file dans le tabEtats


        int pos = 0;

        /*
        unsigned int i = 0;


        while(i != tabEtats.size() && tabEtats[i]->
                () != pile[pointeur]){
                i++;
                pos = i;
        }
        */


        for(int i = 0; (unsigned int)i<tabEtats.size(); i++){
            if(tabEtats[i]->getNom() == file[0]){
                pos = i;
            }
        }


        if(!tabEtats[pos]->predecesseurs.empty()){
            unsigned int tailleTabPredecesseurs = tabEtats[pos]->predecesseurs.size();




            int datePlusTardEtat = tabEtats[pos]->getDatePlusTard();




            // on ajoute les predecesseurs à la file
            for(unsigned int i=0; i < tailleTabPredecesseurs ; i++){

                int dureeVersPredecesseur = tabEtats[pos]->poidsPredecesseur[i];
                int datePlustardPredecesseur = tabEtats[pos]->predecesseurs[i]->getDatePlusTard();

                if(datePlusTardEtat - dureeVersPredecesseur <= datePlustardPredecesseur)
                    tabEtats[pos]->predecesseurs[i]->setDatePlusTard(datePlusTardEtat - dureeVersPredecesseur);

                file.push_back(tabEtats[pos]->predecesseurs[i]->getNom());
            }



        }
        file.erase(file.begin());
        #if DEBUG == 1
            log_file<<endl;
            log_file<<"La file apres iteration: "<<endl;

            for(unsigned int i = 0; i<file.size(); i++)
                log_file<<file[i]<< " ";
            log_file<<endl;
            log_file<<endl;
            log_file<<"apres iteration:";
            displayDatePlusTard();
        #endif // DEBUG

    }


    #if DEBUG == 1
        log_file<<":DEBUG"<<endl;
    #endif // DEBUG

}

void Graphe::displayDatePlusTard(){
    cout<<endl;
    cout<<endl;

    log_file<<endl;
    log_file<<endl;


    cout<< "Dates au plus tard des etats" <<endl;
    log_file<< "Dates au plus tard des etats" <<endl;
    for(unsigned int i=0; i< tabEtats.size(); i++){
        cout<< setw(SPACE) << left << tabEtats[i]->getNom()<< "  ";
        log_file<< setw(SPACE) << left << tabEtats[i]->getNom()<< "  ";
    }
    cout<<endl;
    log_file<<endl;
    for(unsigned int i=0; i< tabEtats.size(); i++){
        cout<< setw(SPACE) << left<< tabEtats[i]->getDatePlusTard() << "  ";
        log_file<< setw(SPACE) << left<< tabEtats[i]->getDatePlusTard() << "  ";
    }
    cout<<endl;
    cout<<endl;

    log_file<<endl;
    log_file<<endl;
}


void Graphe::calcMarges(){

    for(unsigned int i=0; i<tabEtats.size(); i++){
        tabEtats[i]->setMarge(tabEtats[i]->getDatePlusTard() - tabEtats[i]->getDatePlusTot());
    }

}

void Graphe::affichageMarge(){
    cout<<endl;
    cout<<endl;


    cout<< "Marges" <<endl;
    for(unsigned int i=0; i< tabEtats.size(); i++){
        cout<< setw(SPACE) << left << tabEtats[i]->getNom()<< "  ";
    }
    cout<<endl;
    for(unsigned int i=0; i< tabEtats.size(); i++){
        cout<< setw(SPACE) << left<< tabEtats[i]->getMarge() << "  ";
    }
    cout<<endl;
    cout<<endl;
}

void Graphe::niveau2(){
    log_file<<endl;
    log_file<<"---------------------------------------------"<<endl;
    log_file<<"Niveau 2 :"<<endl;
    log_file<<endl;
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
                            if(verificationValeurArcNonNeg()){
                                if(verificationValeurArc()){
                                    cout<<endl;
                                    cout<<endl;
                                    cout << "Toutes les proprietes sonts Vraies !";
                                    cout<<endl;
                                    cout<<endl;
                                    this->affichageGraphe();
                                    this->calcRang();
                                    this->affichageRang();
                                    this->affichageRangTab();
                                    this->calcDatePlusTot();
                                    this->displayDatePlusTot();

                                    // 1 signifie 100 pourcents
                                    this->calcDatePlusTard(1);
                                    this->displayDatePlusTard();

                                    this->calcMarges();
                                    this->affichageMarge();

                                    cout<<endl;
                                    cout<<endl;
                                    cout<< "Calcul des dates avec la date au plus tard de fin de projet a 110 pourcents de sa date au plus tot " <<endl;

                                    // 1,10 signifie 110 pourcents
                                    this->calcDatePlusTard(1.10);
                                    this->displayDatePlusTard();
                                    this->calcMarges();
                                    this->affichageMarge();


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
                if(tabPointSorties.size() > 1)
                    cout<<"Il y a plusieurs points de sortie dans le graphe"<<endl;
                else
                    cout<<"Il n'y a pas de points de sortie dans le graphe"<<endl;
            }
        }else{
            cout<<"Il y a plusieurs points d'entree dans le graphe"<<endl;
        }

    }

}

void Graphe::creerPointEntree(){

    // on assume que le tableau des points d'entrees a été créé,
    // le graphe a été importé en mémoire



/*

    // le nom des etats commence à 0, or 0 c'est alpha, donc on ajoute +1 à chaque nom

    for(unsigned int i=0; i<tabEtats.size(); i++){
        tabEtats[i]->setNom(tabEtats[i]->getNom() + 1);
    }
    */

    Etat* alpha = new Etat(0);

    for(unsigned int i=0; i<tabPointEntrees.size(); i++){
            // ajout des successeurs de alpha
        alpha->ajoutSuccesseur(tabPointEntrees[i], 0);
        // ajout des predecesseurs vers alpha
        tabPointEntrees[i]->ajoutPredecesseur(alpha,0);
    }

    tabEtats.insert(tabEtats.begin(), alpha);

    // nouveau tableau des points d'entrees
    tabPointEntrees.erase(tabPointEntrees.begin(), tabPointEntrees.end());
    tabPointEntrees.push_back(alpha);



    for(int i=0; i<this->nbSommet; i++)
        delete matAdj[i];
    delete matAdj;

    for(int i=0; i<this->nbSommet; i++)
        delete matInc[i];
    delete matInc;



    this->nbSommet++;

    this->matAdj = grapheToMatAdj();

    this->matInc = grapheToMatInc();





    #if DEBUG == 1
        log_file<< "DEBUG:"<<endl;
        log_file<<"Nouveau graphe avec le point d'entree alpha ajoute (nom: 0): "<<endl;
        displayEtatToMatriceAdjIncid();
        log_file<<"Fonction Creer point d'entree, test de creation des matrices a partir du nouveau graphe"<<endl;
        displayGraphe();
        log_file<< ":DEBUG"<<endl;
    #endif // DEBUG



}


void Graphe::creerPointSortie(){

    // on assume que le tableau des points de sorties a été créé,
    // le graphe a été importé en mémoire
    // on a déjà ajouté un point d'entrée

    int nomOmega = this->nbSommet;


    Etat* omega = new Etat(nomOmega);




    for(unsigned int i=0; i<tabPointSorties.size(); i++){


        // ajout des predecesseurs d'omega
        omega->ajoutPredecesseur(tabPointSorties[i], tabPoidsEtat[tabPointSorties[i]->getNom() - 1]);


        // ajout des predecesseurs vers omega
        tabPointSorties[i]->ajoutSuccesseur(omega,tabPoidsEtat[tabPointSorties[i]->getNom() - 1]);
    }




    tabEtats.insert(tabEtats.end(), omega);

    // nouveau tableau des points de sortie
    tabPointSorties.erase(tabPointSorties.begin(), tabPointSorties.end());
    for(unsigned int i=0; i<tabPointSorties.size(); i++)
        tabPointSorties = this->suppr(tabPointSorties, tabPointSorties[i]);
    tabPointSorties.push_back(omega);





    // libere les matrices
    for(int i=0; i<this->nbSommet; i++)
        delete matAdj[i];
    delete matAdj;

    for(int i=0; i<this->nbSommet; i++)
        delete matInc[i];
    delete matInc;



    this->nbSommet++;

    // nouvelle matrice d'adjacence
    this->matAdj = grapheToMatAdj();


    // nouvelle matrice d'incidence
    this->matInc = grapheToMatInc();





    #if DEBUG == 1
        log_file<< "DEBUG:"<<endl;
        // nbSomment - 1 car on vient de l'incrementer
        log_file<<"Nouveau graphe avec le point de sortie omega ajoute (nom:" << this->nbSommet - 1<< "): "<<endl;
        displayEtatToMatriceAdjIncid();
        log_file<<"Fonction Creer point de sortie, test de creation des matrices a partir du nouveau graphe"<<endl;
        displayGraphe();
        log_file<< ":DEBUG"<<endl;
    #endif // DEBUG



}

void Graphe::niveau3(){

    log_file<<endl;
    log_file<<"---------------------------------------------"<<endl;
    log_file<<"Niveau 3 :"<<endl;
    log_file<<endl;
    if(this->importe){

         cout<< "Apres import"<<endl;

        displayGraphe();



        cout<<endl;
        cout<<endl;
        this->displayEtatToMatriceAdjIncid();
        cout<<endl;
        cout<<endl;
        this->affichageGraphe();


        // verification un seul point d'entree
        recherchePointsEntrees();
        displayPointEntrees();
        if(tabPointEntrees.size() >= 1){
            cout<<"Creation d'un point d'entree alpha (nom: 0)"<<endl;
            this->creerPointEntree();
            displayEtatToMatriceAdjIncid();
            displayPointEntrees();
        }
        if(tabPointEntrees.size() < 1){
            cout<<"Il n'y a pas de point d'entree"<<endl;
        }



        if(tabPointEntrees.size() == 1){
                // verification un seul point de sortie
            recherchePointsSorties();
            displayPointSorties();
            if(tabPointSorties.size() >= 1){
                cout<<"Creation d'un point de sortie omega (nom:" << this->nbSommet<<")"<<endl;
                this->creerPointSortie();
                displayEtatToMatriceAdjIncid();
                displayPointSorties();
                cout<<endl;
                cout<<endl;
            }
            if(tabPointSorties.size() < 1){
                cout<<"Il n'y a pas de point de sortie"<<endl;
            }

            if(tabPointSorties.size() == 1){
                if(!this->detectionCircuit()){
                    if(verificationPointEntree()){
                        if(verificationPointSortie()){
                            if(verificationValeurArcNonNeg()){
                                if(verificationValeurArc()){
                                    cout<<endl;
                                    cout<<endl;
                                    cout << "Toutes les proprietes sonts Vraies !";
                                    cout<<endl;
                                    cout<<endl;
                                    this->affichageGraphe();
                                    this->calcRang();
                                    this->affichageRang();
                                    this->affichageRangTab();
                                    this->calcDatePlusTot();
                                    this->displayDatePlusTot();

                                    // 1 signifie 100 pourcents
                                    this->calcDatePlusTard(1);
                                    this->displayDatePlusTard();

                                    this->calcMarges();
                                    this->affichageMarge();

                                    cout<<endl;
                                    cout<<endl;
                                    cout<< "Calcul des dates avec la date au plus tard de fin de projet a 110 pourcents de sa date au plus tot " <<endl;

                                    // 1,10 signifie 110 pourcents
                                    this->calcDatePlusTard(1.10);
                                    this->displayDatePlusTard();
                                    this->calcMarges();
                                    this->affichageMarge();


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

void Graphe::niveau4(){

    log_file<<endl;
    log_file<<"---------------------------------------------"<<endl;
    log_file<<"Niveau 4 :"<<endl;
    log_file<<endl;
    if(this->importe){

         cout<< "Apres import"<<endl;

        displayGraphe();



        cout<<endl;
        cout<<endl;
        this->displayEtatToMatriceAdjIncid();
        cout<<endl;
        cout<<endl;
        this->affichageGraphe();


        // verification un seul point d'entree
        recherchePointsEntrees();
        displayPointEntrees();
        if(tabPointEntrees.size() > 1){
            char choix = 'c';
            do{
                cout<<"Il y a plusieurs taches initiales, entrez \"y\" pour creer une tache initiale alpha, \"n\" sinon : "<<endl;
                cin >> choix;
            }while(choix != 'y' && choix != 'Y' && choix != 'n' && choix != 'N');

            if(choix == 'y' || choix == 'Y'){
                cout<<"Creation d'un point d'entree alpha (nom: 0)"<<endl;
                this->creerPointEntree();
                displayEtatToMatriceAdjIncid();
                displayPointEntrees();
            }
        }
        else if(tabPointEntrees.size() == 1){
            cout<<"Creation d'un point d'entree alpha (nom: 0)"<<endl;
            this->creerPointEntree();
            displayEtatToMatriceAdjIncid();
            displayPointEntrees();
        }

        if(tabPointEntrees.size() == 1){



                // verification un seul point de sortie
            recherchePointsSorties();
            displayPointSorties();



            if(tabPointSorties.size() > 1){
                char choix = 'c';
                do{
                    cout<<"Il y a plusieurs taches finales, entrez \"y\" pour creer une tache finale omega, \"n\" sinon : "<<endl;
                    cin >> choix;
                }while(choix != 'y' && choix != 'Y' && choix != 'n' && choix != 'N');

                if(choix == 'y' || choix == 'Y'){
                    cout<<"Creation d'un point de sortie omega (nom:" << this->nbSommet <<")"<<endl;
                    this->creerPointSortie();
                    displayEtatToMatriceAdjIncid();
                    displayPointSorties();
                    cout<<endl;
                    cout<<endl;
                }
            }
            else if(tabPointSorties.size() == 1){
                cout<<"Creation d'un point de sortie omega (nom:" << this->nbSommet <<")"<<endl;
                this->creerPointSortie();
                displayEtatToMatriceAdjIncid();
                displayPointSorties();
            }

            if(tabPointSorties.size() == 1){
                if(!this->detectionCircuit()){
                    if(verificationPointEntree()){
                        if(verificationPointSortie()){
                            if(verificationValeurArcNonNegInteract()){
                                    // normalement, impossible que ce soit faux, à cause de l'importation
                                if(verificationValeurArcInteract()){
                                    cout<<endl;
                                    cout<<endl;
                                    cout << "Toutes les proprietes sonts Vraies !";
                                    cout<<endl;
                                    cout<<endl;
                                    this->affichageGraphe();
                                    this->displayEtatToMatriceAdjIncid();
                                    this->calcRang();
                                    this->affichageRang();
                                    this->affichageRangTab();
                                    this->calcDatePlusTot();
                                    this->displayDatePlusTot();

                                    // 1 signifie 100 pourcents
                                    this->calcDatePlusTard(1);
                                    this->displayDatePlusTard();

                                    this->calcMarges();
                                    this->affichageMarge();

                                    cout<<endl;
                                    cout<<endl;
                                    cout<< "Calcul des dates avec la date au plus tard de fin de projet a 110 pourcents de sa date au plus tot " <<endl;

                                    // 1,10 signifie 110 pourcents
                                    this->calcDatePlusTard(1.10);
                                    this->displayDatePlusTard();
                                    this->calcMarges();
                                    this->affichageMarge();


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




#include <iostream>

#include "Graphe.h"


using namespace std;

int main()
{
    int niveau;
    bool toExit = true;
    cout << "Projet de Theorie des Graphes" << endl << endl;



    do{
        cout <<"Choose your level :"<<endl;
        cout <<"0)Exit" << endl << "1)Level 1" << endl;
        cin >> niveau;

        switch(niveau){
        case 0:{
            cout << "Exit" << endl;
            toExit = false;
            break;
        }
        case 1:{

            string fileName;

            cout << "Hello" << endl;
            cout << "Entrer un nom de fichier avec son extension txt (ex: monTexte.txt)"<< endl;
            cin >> fileName;

            Graphe graphe(fileName);
            graphe.displayGraphe();

            break;
            }
        default:{
                cout << "Please choose a good number" << endl;
                break;
            }
        }
    }
    while(toExit);
    return 0;
}

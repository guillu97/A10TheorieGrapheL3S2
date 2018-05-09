#include <iostream>

#include "A10Graphe.h"


using namespace std;

int main()
{
    int niveau;
    bool toExit = true;
    string fileName;

    cout << "Projet de Theorie des Graphes" << endl << endl;



    do{

        cout <<"Choose your level :"<<endl;
        cout <<"0)Exit" << endl <<
         "1)Level 1" << endl <<
         "2)Level 2" << endl <<
         "3)Level 3" << endl <<
         "4)Level 4" << endl;

        std::cin.clear();
        cin >> niveau;

        switch(niveau){
        case 0:{
            cout << "Exit" << endl;
            toExit = false;
            break;
        }
        case 1:{

            cout << "Bonjour" << endl;
            cout << "Entrer un nom de fichier avec son extension txt (ex: monTexte.txt)"<< endl;
            cin >> fileName;

            cout<<endl;

            cout<<endl;

            Graphe graphe(fileName, 1);

            graphe.niveau1();

            /*
            // tests de copie construct
            Graphe graphe1(fileName);
            cout << "GRAPHE1"<<endl;
            graphe1.displayGraphe();

            Graphe autre = graphe1;
            cout << "GRAPHE AUTRE"<<endl;
            autre.displayGraphe();

            // mettre matAdj public pour le test

            autre.matAdj[0][1]  = false;
            autre.matInc[0][1] = 10;
            cout <<" GRAPHE AUTRE 2 " <<endl;
            autre.displayGraphe();

            cout<<"GRAPHE1   2"<<endl;
            graphe1.displayGraphe();

*/
// test suppr etat
            //graphe.supprEtat(graphe.tabEtats[0]);

            //graphe.recherchePointsEntrees();


            break;
            }
        case 2:{

            cout << "Bonjour" << endl;
            cout << "Entrer un nom de fichier avec son extension txt (ex: monTexte.txt)"<< endl;
            cin >> fileName;

            cout<<endl;

            cout<<endl;

            Graphe graphe(fileName, 1);

            graphe.niveau2();
            break;
        }
        case 3:
            {
                string fileName;

                cout << "Bonjour" << endl;
                cout << "Entrer un nom de fichier avec son extension txt (ex: monTexte.txt)"<< endl;
                cin >> fileName;

                cout<<endl;

                Graphe graphe(fileName, 3);
                graphe.niveau3();

            }
            break;
        case 4:
            {
                string fileName;

                cout << "Bonjour" << endl;
                cout << "Entrer un nom de fichier avec son extension txt (ex: monTexte.txt)"<< endl;
                cin >> fileName;

                cout<<endl;

                Graphe graphe(fileName, 3);
                graphe.niveau4();

            }
            break;
        default:{
                cout << "Please choose a good number" << endl;
                break;
            }
        }
    }
    while(toExit);
    return 0;
}

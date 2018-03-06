#include <iostream>



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
            cout << "Hello" << endl;
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

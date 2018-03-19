#include "Graphe.h"


using namespace std;




int Rang(Graphe) {
    while (i <  this->nbSommet) {
        r = CalculRang(Graphe, i); /*je sais pas si on créé la variable ici ou dans la classe Graphe*/
        cout << i << "a pour rang :" << r << endl;
    }
}

int CalculRang(Graphe, int sommet)
    {
        list rangPredecesseur;
        while (i < this->nbSommet) {
            if (/* i predecesseur de sommet*/) {
                rangPredecesseur.add(CalculRang(Graphe, i))
            }
        }
        if (rangPredecesseur.vide()) return NULL;
        else return rangPredecesseur.max() + 1;
    }

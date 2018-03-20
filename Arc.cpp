#include "Arc.h"


using namespace std;

Arc::Arc(Etat* extremiteInitiale, Etat* extremiteTerminale, int poids){
        this->extremiteInitiale = extremiteInitiale;
        this->extremiteTerminale = extremiteTerminale;
        this->poids = poids;
}


void Arc::afficherArc(){
    cout << "extremiteInitiale = " << extremiteInitiale->getNom() << " extremiteTerminale = " << extremiteTerminale->getNom() << " poid " << poids << endl << endl;
}

Etat* Arc::getExtremiteInitiale(){
    return extremiteInitiale;
}

Etat* Arc::getExtremiteTerminale(){
    return extremiteTerminale;
}

int Arc::getPoids(){
    return poids;
}

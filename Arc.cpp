#include "Arc.h"


using namespace std;

Arc::Arc(Etat& extremiteInitiale, Etat& extremiteTerminale, int poid){
        this->extremiteInitiale = extremiteInitiale;
        this->extremiteTerminale = extremiteTerminale;
        this->poid = poid;
}


void Arc::afficherArc(){
    cout << "extremiteInitiale = " << extremiteInitiale.getNom() << "extremiteTerminale = " << extremiteTerminale.getNom() << "poid" << poid << endl << endl;
}

Etat Arc::getExtremiteInitiale(){
    return extremiteInitiale;
}

Etat Arc::getExtremiteTerminale(){
    return extremiteTerminale;
}

int Arc::getPoid(){
    return poid;
}

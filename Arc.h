#ifndef A10THEORIEGRAPHEL3S2_ARC_H
#define A10THEORIEGRAPHEL3S2_ARC_H

#include "Etat.h"
#include <iostream>

class Arc{
private:
    Etat* extremiteInitiale;
    Etat* extremiteTerminale;
    int poids;

public:
    Arc(Etat* extremiteInitiale, Etat* extremiteTerminale, int poids);

    void afficherArc();

    Etat* getExtremiteInitiale();

    Etat* getExtremiteTerminale();

    int getPoids();

};
#endif //A10THEORIEGRAPHEL3S2_ETAT_H

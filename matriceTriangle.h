#ifndef MATRICETRIANGLE
#define MATRICETRIANGLE

#include "listPoint.h"
#include "listIndice.h"


typedef struct matriceTriangle matriceTriangle;

struct matriceTriangle{
    int taille;
    listIndice* indiceList;
};

// ------ constructeur

matriceTriangle constructeurMatriceTriangle(int taille2);


void addPath(matriceTriangle* matTri, int indice1, int indice2);

#endif


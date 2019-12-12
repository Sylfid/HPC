#ifndef LISTINDICE
#define LISTINDICE

#include "listPoint.h"

typedef struct listIndice listIndice;

struct listIndice{
    int taille;
    int* indice;
};

// ------ constructeur
listIndice constructeurListIndice();
// ------ fonction classe autre
void addIndice(listIndice *listInd, int i);

// ------ fonction triangulation
listPoint2D projectionWithIndice(listPoint2D listPoint, int indice);
listIndice findPointsPathIndice(listPoint2D pts, int nbproces);
listIndice Convex_HullIndice(listPoint2D pts);
listPoint2D getLeftSideList(listPoint2D listPoint, listIndice separator);
listPoint2D getRightSideList(listPoint2D listPoint, listIndice separator);

#endif

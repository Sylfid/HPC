#ifndef LISTINDICE
#define LISTINDICE
#include "listPoint.h"

typedef struct listIndice listIndice;

struct listIndice{
    int taille;
    int* indice;
};

listIndice constructeurListIndice();
void addIndice(listIndice *listInd, int i);
listIndice Convex_HullIndice(listPoint2D pts);
listIndice findPointsPathIndice(listPoint2D pts, int nbproces);
listPoint2D projectionWithIndice(listPoint2D listPoint, int indice);
#endif

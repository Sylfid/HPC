#ifndef LISTINDICE
#define LISTINDICE

#include "listPoint.h"
#include "listIndicelist.h"

typedef struct listIndice listIndice;

struct listIndice{
    int taille;
    int* indice;
};

// ------ constructeur
listIndice constructeurListIndice();
listIndice constructeurListIndiceBtw(int deb, int fin);
// ------ getteur
int getIndice(listIndice listInd, int i);
// ------ fonction classe autre
void addIndice(listIndice *listInd, int i);

// ------ fonction triangulation
listIndice findPointsPathIndice(listPoint2D pts, int nbproces);
listIndice Convex_HullIndice(listPoint2D pts);

listIndice getLeftSideList(listPoint2D listPoint, listIndice separator);
listIndice getRightSideList(listPoint2D listPoint, listIndice separator);
listIndice partition(listPoint2D pts, listIndice ptsPath, listeIndicelist hulls, int num, int nbProces);

#endif

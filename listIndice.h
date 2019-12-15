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
listIndice constructeurListIndiceBtw(int deb, int fin);
// ------ getteur
int getIndice(listIndice listInd, int i);
// ------ fonction classe autre
void addIndice(listIndice *listInd, int i);
void displayListIndice(listIndice liste);

// ------ fonction triangulation
listIndice findPointsPathIndice(listPoint2D pts, int nbproces);
listIndice Convex_HullIndice(listPoint2D pts);
int isLeftSideList(listPoint2D listPoint, listIndice separator, int pointIndice);
int isRightSideList(listPoint2D listPoint, listIndice separator, int pointIndice);
listIndice getMiddleSideList(listPoint2D listPoint, listIndice separatorLeft, listIndice separatorRight);

listIndice getLeftSideList(listPoint2D listPoint, listIndice separator);
listIndice getRightSideList(listPoint2D listPoint, listIndice separator);
int getTailleIndice(listIndice listeIndice);

#endif

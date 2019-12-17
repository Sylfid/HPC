#ifndef HEDGE
#define HEDGE

#include "point.h"
#include "listPoint.h"
#include "listIndice.h"
#include "listIndiceList.h"
#include "maillage.h"
#include <omp.h>

typedef struct hedge hedge;

struct hedge{
    int taille;
    listPoint2D* hedgeList;
};

// ------ constructeur
hedge constructeurHedge(int taille2);
// ------ getteur
listPoint2D getOneHedge(hedge H, int i);
int getTailleHedge(hedge H);
// ------ fonction classe autre
void displayHedge(hedge H);
void addHedge(hedge *H, listPoint2D listPoint);
void addHedgeByPoints(hedge *H, Point2D p1, Point2D p2);

// ------ fonction triangulation
hedge getHedgeDelaunay(listIndiceList list, int nbProcess);
//listPointList separatePointList(listPoint2D listPoint, int nbProcess);
#endif
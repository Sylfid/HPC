#ifndef LISTPOINTLIST
#define LISTPOINTLIST

#include "point.h"
#include "listPoint.h"

typedef struct listPointList listPointList;

struct listPointList{
    int taille;
    listPoint2D* pointList;
};

listPointList separatePointList(listPoint2D listPoint, int nbProcess);
#endif
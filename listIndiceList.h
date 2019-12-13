#ifndef LISTINDICELIST
#define LISTINDICELIST

#include "listPoint.h"

typedef struct listIndiceList listIndiceList;

struct listIndiceList{
    int taille;
    listIndice* indiceList;
    listPoint2D listPoint;
};

// ------ constructeur
listIndiceList constructeurListIndiceList();
void addListIndiceList(listIndiceList *listindicelist, listIndice list);
listIndiceList separatePointList(listPoint2D listPoint, int nbProcess);
listIndice getListIndice(listIndiceList listindicelist, int i);

#endif


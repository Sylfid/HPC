#ifndef LISTINDICELIST
#define LISTINDICELIST

#include "listPoint.h"
#include "listIndice.h"


typedef struct listIndiceList listIndiceList;

struct listIndiceList{
    int taille;
    listIndice* indiceList;
    listPoint2D listPoint;
};

// ------ constructeur
listIndiceList constructeurListIndiceList(listPoint2D list);
listIndiceList constructeurListIndiceListTaille(int taille2,listPoint2D list);
void setListIndice(listIndiceList* Liste, listIndice newlist, int i);

void setListIndice(listIndiceList* Liste, listIndice newlist, int i);
void addListIndiceList(listIndiceList *listindicelist, listIndice list);
listIndiceList separatePointList(listPoint2D listPoint, int nbProcess);
listIndice getListIndice(listIndiceList listindicelist, int i);
listIndice partition(listPoint2D pts, listIndice ptsPath, listIndiceList hulls, int num, int nbProces);

void displayListIndiceList(listIndiceList liste);
#endif

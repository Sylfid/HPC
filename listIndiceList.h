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
// ------ getteur
listIndice getListIndice(listIndiceList listindicelist, int i);
// ------ setteur
void setListIndice(listIndiceList* Liste, listIndice newlist, int i);
// ------ fonction classe autre
void displayListIndiceList(listIndiceList liste);
void addListIndiceList(listIndiceList *listindicelist, listIndice list);

// ------ fonction triangulation
listIndiceList separatePointList(listPoint2D listPoint, int nbProcess);
//listIndice partition(listPoint2D pts, listIndice ptsPath, listIndiceList hulls, int num, int nbProces);


#endif

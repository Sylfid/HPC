#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "listIndice.h"
#include "listIndiceList.h"
#include "listPoint.h"

// --------- constructeur --------- //

listIndiceList constructeurListIndiceList(listPoint2D listPoint2){
    listIndiceList newList;
    newList.taille = 0;
    newList.indiceList = NULL;
    newList.listPoint = listPoint2;
}

void addListIndiceList(listIndiceList *listindicelist, listIndice list){
    listindicelist->taille++;
    listindicelist->indiceList = realloc(listindicelist->indiceList, listindicelist->taille*sizeof(listIndice));
    listindicelist->indiceList[listindicelist->taille] = list;
}


listIndiceList separatePointList(listPoint2D listPoint, int nbProcess){
    listIndiceList newListIndiceList;
    newListIndiceList.listPoint = listPoint;
    newListIndiceList.taille = nbProcess;
    newListIndiceList.indiceList = (listIndice*) malloc(nbProcess*sizeof(listIndice));
    int th_id;
    triByX(&listPoint);
    exit(1);
    listIndice pointForPath = findPointsPathIndice(listPoint, nbProcess);
    exit(1);
#pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        if(th_id<nbProcess){
            listPoint2D projec;
            listIndice group;
            if(th_id == nbProcess - 1){
                projec = projectionWithIndice(listPoint,th_id-1);
            }
            else{
                projec = projectionWithIndice(listPoint,th_id);
            }
            listIndice path = Convex_HullIndice(projec);
            if(th_id == nbProcess - 1){
                group = getRightSideList(listPoint, path);
            }
            else{
                group = getLeftSideList(listPoint, path);
            }
            addListIndiceList(&newListIndiceList, group);
        }
    }
    return newListIndiceList;
}

listIndice getListIndice(listIndiceList listindicelist, int i){
    if(i<0 || i>listindicelist.taille){
        printf("getListIndice : le numero de la liste d'indice n'existe pas");
        exit(1);
    }
    else{
        return listindicelist.indiceList[i];
    }
}

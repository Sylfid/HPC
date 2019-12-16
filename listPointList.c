#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "point.h"
#include "listPoint.h"
#include "listIndice.h"
#include "listPointList.h"


/*listPointList separatePointList(listPoint2D listPoint, int nbProcess){
    listPointList newListPointList;
    newListPointList.taille = nbProcess;
    newListPointList.pointList = (listPoint2D*) malloc(nbProcess*sizeof(listPoint2D));
    int th_id;
    triByX(&listPoint);
    listIndice pointForPath = findPointsPathIndice(listPoint, nbProcess);
#pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        if(th_id<nbProcess){
            listPoint2D projec, group; 
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
            addListPointList(&newListPointList, group, th_id);
        }
    }
    return newListPointList;
}*/


void addListPointList(listPointList *list, listPoint2D listPoint, int i){
    if(i > list->taille-1){
        printf("addListPointList : L'indice donné ne correspond pas à la liste");
        exit(1);
    }
    else{
        freeListPoint2D(&list->pointList[i]);
        int taille2 = getTailleList2D(listPoint);
        list->taille = taille2; 
        list->pointList[i] = constructListPoint2D(taille2);
        for(int j=0; j<taille2; j++){
            setListPoint2DFromPoint(&list->pointList[i], getPoint2D(listPoint, j), j);
        }
    }
}

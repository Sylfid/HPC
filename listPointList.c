#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "point.h"
#include "listPoint.h"
#include "listIndice.h"
#include "listPointList.h"


listPointList separatePointList(listPoint2D listPoint, int nbProcess){
    listPointList newListPointList;
    newListPointList.taille = nbProcess;
    newListPointList.pointList = (listPoint2D*) malloc(nbProcess*sizeof(listPoint2D));
    int th_id;
    triByX(&listPoint);
    listIndice pointForPath = findPointsPathIndice(listPoint, nbProcess);
#pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        if(th_id<nbProcess-1){//PROBLEME TAILLE DE CREATION
            listPoint2D projec = projectionWithIndice(listPoint,th_id);
            listIndice path = Convex_HullIndice(projec);
            listPoint2D group = getLeftSideList(listPoint, path);
        }

    }
    return newListPointList;
}

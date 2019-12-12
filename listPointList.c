#include <stdio.h>
#include <stdlib.h>
#include "listPoint.h"
#include "point.h"
#include "listPointList.h"
#include <omp.h>


listPointList separatePointList(listPoint2D listPoint, int nbProcess){
    listPointList newListPointList;
    newListPointList.taille = nbProcess;
    newListPointList.pointList = (listPoint2D*) malloc(nbProcess*sizeof(listPoint2D));
    int th_id;
    listPoint2D pointForPath = findPointsPath(listPoint, nbProcess);
#pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        if(th_id<nbProcess){
             
        }

    }
    return newListPointList;
}

#include <stdio.h>
#include <stdlib.h>
#include "listPoint.h"


listPoint2D constructListPoint2D(int taille2){
    listPoint2D newListPoint;
    newListPoint.taille = taille2;
    newListPoint.point = (Point2D*) malloc(taille2*sizeof(Point2D));
    return newListPoint;
}

void setListToZero(listPoint2D listPoint){
    for(int i=0; i<listPoint.taille; i++){
        setPoint2D(listPoint.point[i], 0., 0.);
    }
}

void displayListPoint(listPoint2D listPoint){
    for(int i=0; i<listPoint.taille; i++){
        displayPoint2D(listPoint.point[i]);
    }
}


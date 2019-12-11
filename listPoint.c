#include <stdio.h>
#include <stdlib.h>
#include "listPoint.h"
#include "point.h"

listPoint2D constructListPoint2D(int taille2){
    listPoint2D newListPoint;
    newListPoint.taille = taille2;
    newListPoint.point = (Point2D*) malloc(taille2*sizeof(Point2D));
    return newListPoint;
}

listPoint3D constructListPoint3D(int taille2){
    listPoint3D newListPoint;
    newListPoint.taille = taille2;
    newListPoint.point = (Point3D*) malloc(taille2*sizeof(Point3D));
    return newListPoint;
}

void setListPoint2DToZero(listPoint2D listPoint){
    for(int i=0; i<listPoint.taille; i++){
        setPoint2D(listPoint.point[i], 0., 0.);
    }
}

void setListPoint3DToZero(listPoint3D listPoint){
    for(int i=0; i<listPoint.taille; i++){
        setPoint3D(listPoint.point[i], 0., 0., 0.);
    }
}

void displayListPoint2D(listPoint2D listPoint){
    for(int i=0; i<listPoint.taille; i++){
        displayPoint2D(listPoint.point[i]);
        printf("\n");
    }
}

void displayListPoint3D(listPoint3D listPoint){
    for(int i=0; i<listPoint.taille; i++){
        displayPoint3D(listPoint.point[i]);
        printf("\n");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include "point.h"

Point2D constructPoint2D(float x1, float y1){
    Point2D newPoint;
    newPoint.x = x1;
    newPoint.y = y1;
    return newPoint;
}

Point3D constructPoint3D(float x1, float y1, float z1){
    Point3D newPoint;
    newPoint.x = x1;
    newPoint.y = y1;
    newPoint.z = z1;
    return newPoint;
}


void displayPoint2D(Point2D point){
    printf("%f %f", point.x, point.y);
}

void displayPoint3D(Point3D point){
    printf("%f %f %f", point.x, point.y, point.z);
}

void setPoint2D(Point2D point, float x2, float y2){
    point.x = x2;
    point.y = y2;
}

void setPoint3D(Point3D point, float x2, float y2, float z2){
    point.x = x2;
    point.y = y2;
    point.z = z2;
}

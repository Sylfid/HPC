#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
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
    printf("%f %f\n", point.x, point.y);
}

void displayPoint3D(Point3D point){
    printf("%f %f %f\n", point.x, point.y, point.z);
}

void setPoint2D(Point2D *point, float x2, float y2){
    point->x = x2;
    point->y = y2;
}

void setPoint3D(Point3D *point, float x2, float y2, float z2){
    point->x = x2;
    point->y = y2;
    point->z = z2;
}

void setXPoint2D(Point2D *point, float x2){
    point->x = x2;
}

void setYPoint2D(Point2D *point, float y2){
    point->y = y2;
}

void setXPoint3D(Point3D *point, float x2){
    point->x = x2;
}

void setYPoint3D(Point3D *point, float y2){
    point->y = y2;
}

void setZPoint3D(Point3D *point, float z2){
    point->z = z2;
}

float getXPoint2D(Point2D point){
    return point.x;
}

float getYPoint2D(Point2D point){
    return point.y;
}

float getXPoint3D(Point3D point){
    return point.x;
}

float getYPoint3D(Point3D point){
    return point.y;
}

float getZPoint3D(Point3D point){
    return point.z;
}

float sqrt_dif(Point2D p1, Point2D p2){
  // ||p1-p2||^2
  return pow(getXPoint2D(p1)-getXPoint2D(p2),2.)+pow(getYPoint2D(p1)-getYPoint2D(p2),2.);
}

bool orientation(Point2D p1, Point2D p2, Point2D p3){
  // return True si (p1, p2, p3) est un triangle antihoraire
  float val1 = (getYPoint2D(p2) - getYPoint2D(p1)) * (getXPoint2D(p3) - getXPoint2D(p2));
  float val2 = (getXPoint2D(p2) - getXPoint2D(p1)) * (getYPoint2D(p3) - getYPoint2D(p2));
  return val1<val2;
}



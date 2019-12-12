#ifndef LISTPOINT
#define LISTPOINT


#include "point.h"

typedef struct listPoint2D listPoint2D;
typedef struct listPoint3D listPoint3D;

struct listPoint2D{
    int taille;
    Point2D* point;
};

struct listPoint3D{
    int taille;
    Point3D* point;
};

listPoint2D constructListPoint2D(int taille2);
listPoint3D constructListPoint3D(int taille2);
void freeListPoint2D(listPoint2D* listPoint);
void freeListPoint3D(listPoint3D* listPoint);
void setListPoint2DToZero(listPoint2D *listPoint);
void setListPoint3DToZero(listPoint3D *listPoint);
void displayListPoint2D(listPoint2D listPoint);
void displayListPoint3D(listPoint3D listPoint);
listPoint2D constructListPoint2DFromFile(char* fileName);
Point2D getPoint2D(listPoint2D listPoint, int i);
float getXListPoint2D(listPoint2D listPoint, int i);
float getYListPoint2D(listPoint2D listPoint, int i);
float getXListPoint3D(listPoint3D listPoint, int i);
float getYListPoint3D(listPoint3D listPoint, int i);
float getZListPoint3D(listPoint3D listPoint, int i);
int getTailleList2D(listPoint2D listPoint);
int getTailleList3D(listPoint3D listPoint);
void setXListPoint2D(listPoint2D *listPoint, float a, int i);
void setYListPoint2D(listPoint2D *listPoint, float a, int i);
void setListPoint2DFromPoint(listPoint2D *listPoint, Point2D point, int i);
void setXListPoint3D(listPoint3D *listPoint, float a, int i);
void setYListPoint3D(listPoint3D *listPoint, float a, int i);
void setZListPoint3D(listPoint3D *listPoint, float a, int i);
void setListPoint3D(listPoint3D *listPoint, float x2, float y2, float z2, int i);
void setListPoint2D(listPoint2D *listPoint, float x2, float y2, int i);
void setListPoint2DFromPoint(listPoint2D *listPoint, Point2D point, int i);
void addPoint2DFromPoint(listPoint2D *listPoint, Point2D point);
listPoint2D projection(listPoint2D listPoint, Point2D point);
listPoint2D Convex_Hull(listPoint2D pts);
void triByX(listPoint2D *pts);
listPoint2D findPointsPath(listPoint2D pts, int nbproces);
void addPointList2DFromPointList(listPoint2D *listPoint, listPoint2D addListPoint);

#endif

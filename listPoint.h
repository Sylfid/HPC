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
void setListPoint2DToZero(listPoint2D listPoint);
void setListPoint3DToZero(listPoint3D listPoint);
void displayListPoint2D(listPoint2D listPoint);
void displayListPoint3D(listPoint3D listPoint);
listPoint2D constructListPoint2DFromFile(char* fileName);

#endif

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

void setListToZero(listPoint2D listPoint);
void displayListPoint(listPoint2D listPoint);

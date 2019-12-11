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

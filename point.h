#ifndef POINT
#define POINT

typedef struct Point2D Point2D;
typedef struct Point3D Point3D;

struct Point2D{
    float x;
    float y;
};

struct Point3D{
    float x;
    float y;
    float z;
};

Point2D constructPoint2D(float x1, float y1);
Point3D constructPoint3D(float x1, float y1, float z1);
void displayPoint2D(Point2D point);
void displayPoint3D(Point3D point);
void setPoint2D(Point2D *point, float x2, float y2);
void setPoint3D(Point3D *point, float x2, float y2, float z2);
void setXPoint2D(Point2D *point, float x2);
void setYPoint2D(Point2D *point, float y2);
void setXPoint3D(Point3D *point, float x2);
void setYPoint3D(Point3D *point, float y2);
void setZPoint3D(Point3D *point, float y2);
float getXPoint2D(Point2D point);
float getYPoint2D(Point2D point);
float getXPoint3D(Point3D point);
float getYPoint3D(Point3D point);
float getZPoint3D(Point3D point);

#endif

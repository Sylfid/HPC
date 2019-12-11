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

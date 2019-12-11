#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "listPoint.h"


int main()

{

    printf("Hello world!\n");
    Point3D test =  constructPoint3D(1.2,2.66, 4.3);
    listPoint2D list = constructListPoint2DFromFile("test");
    displayListPoint2D(list);
    return 0;

}

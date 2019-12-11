#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "listPoint.h"


int main()

{

    printf("Hello world!\n");
    Point3D test =  constructPoint3D(1.2,2.66, 4.3);
    listPoint2D list = constructListPoint2DFromFile("happy");
    //displayListPoint2D(list);
    displayPoint3D(test);
    return 0;

}

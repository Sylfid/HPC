#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "listPoint.h"


int main()

{

    printf("Hello world!\n");
    Point3D test =  constructPoint3D(1.2,2.66, 4.3);
    listPoint3D list = constructListPoint3D(5);
    setListPoint3DToZero(list);
    displayListPoint3D(list);
    displayPoint3D(test);
    return 0;

}

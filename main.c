#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "listPoint.h"
#include "listPointList.h"
#include "listIndice.h"
#include "listIndiceList.h"


int main()

{

    printf("Hello world!\n");
    listPoint2D list = constructListPoint2DFromFile("test");
    listPoint2D list2 = Convex_Hull(list);
    listIndiceList essai = separatePointList(list, 4);  
    //displayListPoint2D(list2);
    freeListPoint2D(&list);
    freeListPoint2D(&list2);

    return 0;

}

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
    printf("\n");
    displayListPoint2D(list);
    printf("\n");
    listPoint2D list2 = Convex_Hull(list);
    listIndiceList essai = separatePointList(list, 4);  
    displayListIndiceList(essai);
    freeListPoint2D(&list);
    freeListPoint2D(&list2);

    return 0;

}

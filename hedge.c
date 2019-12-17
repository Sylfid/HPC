#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "listPoint.h"
#include "listIndice.h"
#include "hedge.h"

// --------- constructeur --------- //
hedge constructeurHedge(int taille2){
    if(taille2<0){
      printf("constructeurHedge : la taille doit être positive\n");
      exit(1);
    }
    else{
      hedge newList;
      newList.taille = taille2;
      if(taille2 == 0){
          newList.hedgeList = NULL;
      }
      else{
        newList.hedgeList = (listPoint2D*) malloc(taille2*sizeof(listPoint2D));
      }
      return newList;
    }
}


// --------- getteur --------- //

listPoint2D getOneHedge(hedge H, int i){
    if(i<0 || i>H.taille-1){
        printf("getHedge : le numero de l'arrete n'existe pas");
        exit(1);
    }
    else{
        return H.hedgeList[i];
    }
}

int getTailleHedge(hedge H){
  return H.taille;
}


// ------ fonction classe autre ------ //

void displayHedge(hedge H){
    if(H.hedgeList == NULL){
        printf("displayHedge : hedgeList == NULL");
        exit(1);
    }
    listPoint2D h;
    for(int i=0; i<H.taille; i++){
        h=getOneHedge(H,i);
        printf("(%f, %f) ; (%f, %f) \n",getXListPoint2D(h,0),getYListPoint2D(h,0),getXListPoint2D(h,1),getYListPoint2D(h,1));
    }
    printf("\n");
}

void addHedge(hedge *H, listPoint2D listPoint){
  if(getTailleList2D(listPoint)!=2){
    printf("addHedge : On ne peut ajouter qu'une liste de 2 point \n");
    exit(1);
  }
    H->taille++;
    H->hedgeList = realloc(H->hedgeList, H->taille*sizeof(listPoint2D));
    H->hedgeList[H->taille-1] = listPoint;
}


// ------ fonction triangulation ------ //

hedge getHedgeDelaunay(listIndiceList paths, int nbProcess){
  // calcul de le arrets du maillage en combinant les triangle et les convexHull
  // retourner une liste de liste d'indice de taille 2

}

/*listPointList separatePointList(listPoint2D listPoint, int nbProcess){
    listPointList newListPointList;
    newListPointList.taille = nbProcess;
    newListPointList.pointList = (listPoint2D*) malloc(nbProcess*sizeof(listPoint2D));
    int th_id;
    triByX(&listPoint);
    listIndice pointForPath = findPointsPathIndice(listPoint, nbProcess);
#pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        if(th_id<nbProcess){
            listPoint2D projec, group;
            if(th_id == nbProcess - 1){
                projec = projectionWithIndice(listPoint,th_id-1);
            }
            else{
                projec = projectionWithIndice(listPoint,th_id);
            }
            listIndice path = Convex_HullIndice(projec);
            if(th_id == nbProcess - 1){
                group = getRightSideList(listPoint, path);
            }
            else{
                group = getLeftSideList(listPoint, path);
            }
            addListPointList(&newListPointList, group, th_id);
        }
    }
    return newListPointList;
}*/

//
// void addListPointList(listPointList *list, listPoint2D listPoint, int i){
//     if(i > list->taille-1){
//         printf("addListPointList : L'indice donné ne correspond pas à la liste");
//         exit(1);
//     }
//     else{
//         freeListPoint2D(&list->pointList[i]);
//         int taille2 = getTailleList2D(listPoint);
//         list->taille = taille2;
//         list->pointList[i] = constructListPoint2D(taille2);
//         for(int j=0; j<taille2; j++){
//             setListPoint2DFromPoint(&list->pointList[i], getPoint2D(listPoint, j), j);
//         }
//     }
// }

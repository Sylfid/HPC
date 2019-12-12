#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "listIndice.h"
#include "listPoint.h"

listIndice constructeurListIndice(){
    listIndice newList;
    newList.taille = 0;
    newList.indice = NULL;
}

void addIndice(listIndice *listInd, int i){
    listInd->taille++;
    listInd->indice = realloc(listInd->indice, listInd->taille*sizeof(int));
    listInd->indice[listInd->taille-1] = i;
}

listIndice Convex_HullIndice(listPoint2D pts){
  int n = getTailleList2D(pts);

  // Il faut plus de 3 points
  if (n < 3){
    printf("pas assez de point \n");
    exit(1);
  }

  // trouver le point le plus gauche
  int l = 0;
  for(int i = 1; i < n; i++) {
    if(getXListPoint2D(pts,i) < getXListPoint2D(pts,l)){
      l=i;
    }
  }

  // init res avec le point le plus à gauche
  listIndice hull = constructeurListIndice();

  // Construction hull
  int p = l, q;
  bool flag = false;
  do{
    addIndice(&hull, p);
    q = (p + 1) % n;
    for (int x = 0; x < n; x++){
      // On cherche le point q le plus "counterclockwise"
      if (orientation(getPoint2D(pts,p), getPoint2D(pts,x), getPoint2D(pts,q))){
        q = x; // x est plus "counterclockwise" que q
      }
    }
    flag = (getXListPoint2D(pts, p) > getXListPoint2D(pts, q));
    p = q; // à la fin c'est q le plus "counterclockwise"
  } while (p != l && !flag);  // On continu jusqu'a revenir au 1er*/

  return hull;
}

listIndice findPointsPathIndice(listPoint2D pts, int nbproces){
  triByX(pts); // tri selon coordoné x
  listIndice listeIndice = constructeurListIndice();
  for(int i=1 ; i<nbproces ; i++){
    int pas = floor(getTailleList2D(pts)/nbproces);
    addIndice(&listeIndice, i*pas);
  }
  return listeIndice;
}

//A mettre Dans listPoint.c
listPoint2D projectionWithIndice(listPoint2D listPoint, int indice){
  float py = getYPoint2D(listPoint.point[indice]);
  int n = getTailleList2D(listPoint);
  listPoint2D nwList = constructListPoint2D(n);
  for(int i = 0; i<n ; i++){
    setListPoint2D(&nwList,getYListPoint2D(listPoint,i)-py, sqrt_dif(listPoint.point[indice], getPoint2D(listPoint, i)), i);
  }
  return nwList;
}

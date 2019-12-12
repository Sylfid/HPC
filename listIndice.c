#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "listIndice.h"
#include "listPoint.h"

// --------- constructeur --------- //

listIndice constructeurListIndice(){
    listIndice newList;
    newList.taille = 0;
    newList.indice = NULL;
}


// ------ fonction classe autre ------ //

void addIndice(listIndice *listInd, int i){
    listInd->taille++;
    listInd->indice = realloc(listInd->indice, listInd->taille*sizeof(int));
    listInd->indice[listInd->taille-1] = i;
}

// ------ fonction triangulation ------ //

//A mettre Dans listPoint.c
listPoint2D projectionWithIndice(listPoint2D listPoint, int indice){
  // Double projections sur parabole 3D centré en point puis sur plan orthogonal
  // au plan d'origine passant par la ligne verticale passant par point
  float py = getYPoint2D(listPoint.point[indice]);
  int n = getTailleList2D(listPoint);
  listPoint2D nwList = constructListPoint2D(n);
  for(int i = 0; i<n ; i++){
    setListPoint2D(&nwList,getYListPoint2D(listPoint,i)-py, sqrt_dif(listPoint.point[indice], getPoint2D(listPoint, i)), i);
  }
  return nwList;
}

listIndice findPointsPathIndice(listPoint2D pts, int nbproces){
  // Trouve les points optimaux qui sépare le nuage de points selon x
  triByX(&pts); // tri selon coordoné x
  listIndice listeIndice = constructeurListIndice();
  for(int i=1 ; i<nbproces ; i++){
    int pas = floor(getTailleList2D(pts)/nbproces);
    addIndice(&listeIndice, i*pas);
  }
  return listeIndice;
}

listIndice Convex_HullIndice(listPoint2D pts){
  // Calcul de l'envelope convexe
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

listPoint2D getLeftSideList(listPoint2D listPoint, listIndice separator){
    // Retourne les points qui sont à gauche de la ligne separatorlistPoint2D result = constructListPoint2D(0);
    listPoint2D result = constructListPoint2D(0);
    for(int i=0; i<listPoint.taille; i++){
        for(int j=0; j<separator.taille-1; j++){
            if(getYPoint2D(listPoint.point[separator.indice[j]]) < getYPoint2D(listPoint.point[i])
                    && getYPoint2D(listPoint.point[separator.indice[j+1]]) > getYPoint2D(listPoint.point[i])){
                if(orientation(listPoint.point[separator.indice[j]],listPoint.point[separator.indice[j+1]],listPoint.point[i])){
                    addPoint2DFromPoint(&result,listPoint.point[i]);
                }
            }
        }
    }
    for(int i=0; i<separator.taille; i++){
        addPoint2DFromPoint(&result, listPoint.point[i]);
    }
}

listPoint2D getRightSideList(listPoint2D listPoint, listIndice separator){
    // Retourne les points qui sont à droite de la ligne separator
    listPoint2D result = constructListPoint2D(0);
    for(int i=0; i<listPoint.taille; i++){
        for(int j=0; j<separator.taille-1; j++){
            if(getYPoint2D(listPoint.point[separator.indice[j]]) < getYPoint2D(listPoint.point[i])
                    && getYPoint2D(listPoint.point[separator.indice[j+1]]) > getYPoint2D(listPoint.point[i])){
                if(!orientation(listPoint.point[separator.indice[j]],listPoint.point[separator.indice[j+1]],listPoint.point[i])){
                    addPoint2DFromPoint(&result,listPoint.point[i]);
                }
            }
        }
    }
    for(int i=0; i<separator.taille; i++){
        addPoint2DFromPoint(&result, listPoint.point[i]);
    }
}

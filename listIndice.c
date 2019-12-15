#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "listIndice.h"
#include "listPoint.h"
#include "listIndiceList.h"

// --------- constructeur --------- //

listIndice constructeurListIndice(){
    listIndice newList;
    newList.taille = 0;
    newList.indice = NULL;
    return newList;
}

listIndice constructeurListIndiceBtw(int deb, int fin){
  // construit une liste d'indice comptenant les i in [deb, fin[
    listIndice newList;
    if(fin<deb){
      printf("le début doit etre plus petit que la fin \n");
      exit(1);
    }
    newList.taille = fin-deb;
    newList.indice = (int*) malloc((fin-deb)*sizeof(int));
    for (int i = deb; i < fin; i++) {
      newList.indice[i-deb]=i;
    }
}


// -------- getteur -------- //
int getIndice(listIndice listInd, int i){
  return listInd.indice[i];
}


// ------ fonction classe autre ------ //

void addIndice(listIndice *listInd, int i){
    listInd->taille = listInd->taille+1;
    listInd->indice = realloc(listInd->indice, listInd->taille*sizeof(int));
    /*int *newInd = (int*)malloc(listInd->taille*sizeof(int));
    printf("%d\n", listInd->taille);
    exit(1);
    for(int j=0; j<listInd->taille-1; j++){
        newInd[j] = listInd->indice[j];
    }

    exit(1);
    newInd[listInd->taille-1]=i;
    free(listInd->indice);
    listInd->indice = newInd;*/
    listInd->indice[listInd->taille-1] = i;
}

// ------ fonction triangulation ------ //

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

listIndice getLeftSideList(listPoint2D listPoint, listIndice separator){
    // Retourne les points qui sont à gauche de la ligne separatorlistPoint2D result = constructListPoint2D(0);
    listIndice result = constructeurListIndice();
    for(int i=0; i<listPoint.taille; i++){
        for(int j=0; j<separator.taille-1; j++){
            if(getYPoint2D(listPoint.point[separator.indice[j]]) <= getYPoint2D(listPoint.point[i])
                    && getYPoint2D(listPoint.point[separator.indice[j+1]]) > getYPoint2D(listPoint.point[i])){
                if(orientation2(listPoint.point[separator.indice[j]],listPoint.point[separator.indice[j+1]],listPoint.point[i])){
                    addIndice(&result, i);
                }
            }
        }
    }
    for(int i=0; i<separator.taille; i++){
        addIndice(&result, separator.indice[i]);
    }
    return result;
}

int getTailleIndice(listIndice listeIndice){
    return listeIndice.taille;
}

listIndice getRightSideList(listPoint2D listPoint, listIndice separator){
    // Retourne les points qui sont à droite de la ligne separator
    listIndice result = constructeurListIndice();
    for(int i=0; i<listPoint.taille; i++){
        for(int j=0; j<separator.taille-1; j++){
            if(getYPoint2D(listPoint.point[separator.indice[j]]) <= getYPoint2D(listPoint.point[i])
                    && getYPoint2D(listPoint.point[separator.indice[j+1]]) > getYPoint2D(listPoint.point[i])){//Oublie potentiellement quelque points
                if(!orientation2(listPoint.point[separator.indice[j]],listPoint.point[separator.indice[j+1]],listPoint.point[i])){
                    addIndice(&result, i);
                }
            }
        }
    }
    for(int i=0; i<separator.taille; i++){
        printf("\n a %d %d \n", separator.indice[i], i);
        addIndice(&result, separator.indice[i]);
    }
    return result;
}

void displayListIndice(listIndice liste){
    for(int i=0; i<liste.taille; i++){
        printf("%d ", liste.indice[i]);
    }
    printf("\n");
}

int isLeftSideList(listPoint2D listPoint, listIndice separator, int pointIndice){

    listIndice result = constructeurListIndice();
    for(int j=0; j<separator.taille-1; j++){
        if(getYPoint2D(listPoint.point[separator.indice[j]]) <= getYPoint2D(listPoint.point[pointIndice])
                && getYPoint2D(listPoint.point[separator.indice[j+1]]) > getYPoint2D(listPoint.point[pointIndice])){
            if(orientation2(listPoint.point[separator.indice[j]],listPoint.point[separator.indice[j+1]],listPoint.point[pointIndice])){
                return 1;
            }
        }
    }
    for(int i=0; i<separator.taille; i++){
        if(separator.indice[i]==pointIndice){
            return 1;
        }
    }
    return 0;
}

int isRightSideList(listPoint2D listPoint, listIndice separator, int pointIndice){

    listIndice result = constructeurListIndice();
    for(int j=0; j<separator.taille-1; j++){
        if(getYPoint2D(listPoint.point[separator.indice[j]]) <= getYPoint2D(listPoint.point[pointIndice])
                && getYPoint2D(listPoint.point[separator.indice[j+1]]) > getYPoint2D(listPoint.point[pointIndice])){
            if(!orientation2(listPoint.point[separator.indice[j]],listPoint.point[separator.indice[j+1]],listPoint.point[pointIndice])){
                return 1;
            }
        }
    }
    for(int i=0; i<separator.taille; i++){
        if(separator.indice[i]==pointIndice){
            return 1;
        }
    }
    return 0;
}

listIndice getMiddleSideList(listPoint2D listPoint, listIndice separatorLeft, listIndice separatorRight){
    listIndice newList = constructeurListIndice();
    for(int i=0; i<listPoint.taille; i++){
        if(isRightSideList(listPoint, separatorLeft, i) && 
                isLeftSideList(listPoint, separatorRight,i)){
            addIndice(&newList, i);
        }
    }
}

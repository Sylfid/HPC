#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "listIndice.h"
#include "listPoint.h"
#include "listIndicelist.h"

// --------- constructeur --------- //

listIndice constructeurListIndice(){
    listIndice newList;
    newList.taille = 0;
    newList.indice = NULL;
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
    listInd->taille++;
    listInd->indice = realloc(listInd->indice, listInd->taille*sizeof(int));
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

listIndice partition(listPoint2D pts, listIndice ptsPath, listeIndicelist hulls, int num, int nbProces){
  if (num >= nbProces || num < 0){
    printf("le numéro n'est pas valide (num in [0 nbProces[])\n");
    exit(1);
  }
  else if num == 0{ // partition la plus à gauche
    int pi = getIndice(ptsPath, num);
    listIndice hull = getIndicelist(hulls, num);
     // on met les indice des point d'avant p_0
    listIndice part = constructeurListIndiceBtw(0,pi);
    for(int i = 0 ; i < getTailleIndice(hull) ; i++){
      int hi = getIndice(hull,i);
      if (hi>=pi){ // on ajoute les points le l'envelope qui n'y sont pas
        addIndice(&part,hi);
      }
    }
  }
  else if num == nbProces-1{ // partition la plus à droite
    int pi = getIndice(ptsPath, num);
    listIndice hull = getIndicelist(hulls, num);
     // on met les indice des point d'apres p_m
    listIndice part = constructeurListIndiceBtw(pi,getTailleList2D(pts));
    for(int i = 0 ; i < getTailleIndice(hull) ; i++){
      int hi = getIndice(hull,i);
      if (hi<pi){ // on ajoute les points le l'envelope qui n'y sont pas
        addIndice(&part,hi);
      }
    }
  }
  else {
    int pdeb = getIndice(ptsPath, num-1);
    int pfin = getIndice(ptsPath, num);
    listIndice hullG = getIndicelist(hulls, num-1);
    listIndice hullD = getIndicelist(hulls, num);
     // on met les indice des point entre p_i-1 et p_i
    listIndice part = constructeurListIndiceBtw(pdeb,pfin;
    for(int i = 0 ; i < getTailleIndice(hullG) ; i++){
      int hi = getIndice(hullG,i);
      if (hi<pdeb){ // on ajoute les points le l'envelope qui n'y sont pas
        addIndice(&part,hi);
      }
    }
    for(int j = 0 ; j < getTailleIndice(hullD) ; i++){
      int hi = getIndice(hullG,j);
      if (hi>=pfin){ // on ajoute les points le l'envelope qui n'y sont pas
        addIndice(&part,hi);
      }
    }
  }
  return part;
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

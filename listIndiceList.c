#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "listIndice.h"
#include "listIndiceList.h"
#include "listPoint.h"

// --------- constructeur --------- //

listIndiceList constructeurListIndiceList(listPoint2D listPoint2){
    listIndiceList newList;
    newList.taille = 0;
    newList.indiceList = NULL;
    newList.listPoint = listPoint2;
    return newList;
}

listIndiceList constructeurListIndiceListTaille(int taille2,listPoint2D list){
  listIndiceList newList;
  newList.taille = taille2;
  if(taille2 == 0){
      newList.indiceList = NULL;
  }
  else{
    newList.indiceList = (listIndice*) malloc(taille2*sizeof(listIndice));
  }
  newList.listPoint = listPoint2;
  return newList;
}

void setListIndice(listIndiceList* Liste, indiceList newlist, int i){
  Liste->indiceList[i] = newlist;
}


void addListIndiceList(listIndiceList *listindicelist, listIndice list){
    listindicelist->taille++;
    listindicelist->indiceList = realloc(listindicelist->indiceList, listindicelist->taille*sizeof(listIndice));
    listindicelist->indiceList[listindicelist->taille-1] = list;
}


listIndiceList separatePointList(listPoint2D listPoint, int nbProcess){
    listIndiceList newListIndiceList;
    newListIndiceList.listPoint = listPoint;
    newListIndiceList.taille = nbProcess;
    newListIndiceList.indiceList = (listIndice*) malloc(nbProcess*sizeof(listIndice));
    triByX(&listPoint);
    listIndice pointForPath = findPointsPathIndice(listPoint, nbProcess);
    listPoint2D projec;
    listIndice group;
#pragma omp parallel private(projec) private(group)
    {
        int th_id = omp_get_thread_num();
        if(th_id<nbProcess){
            /*if(th_id == nbProcess - 1){
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
            }*/
            addListIndiceList(&newListIndiceList, group);
        }
    }
    return newListIndiceList;
}

listIndice getListIndice(listIndiceList listindicelist, int i){
    if(i<0 || i>listindicelist.taille){
        printf("getListIndice : le numero de la liste d'indice n'existe pas");
        exit(1);
    }
    else{
        return listindicelist.indiceList[i];
    }
}



listIndice partition(listPoint2D pts, listIndice ptsPath, listIndiceList hulls, int num, int nbProces){
  listIndice part;
  if (num >= nbProces || num < 0){
    printf("le numéro n'est pas valide (num in [0 nbProces[])\n");
    exit(1);
  }
  else if (num == 0){ // partition la plus à gauche
    int pi = getIndice(ptsPath, num);
    listIndice hull = getListIndice(hulls, num);
     // on met les indice des point d'avant p_0
    part = constructeurListIndiceBtw(0,pi);
    for(int i = 0 ; i < getTailleIndice(hull) ; i++){
      int hi = getIndice(hull,i);
      if (hi>=pi){ // on ajoute les points le l'envelope qui n'y sont pas
        addIndice(&part,hi);
      }
    }
  }
  else if (num == nbProces-1){ // partition la plus à droite
    int pi = getIndice(ptsPath, num);
    listIndice hull = getListIndice(hulls, num);
     // on met les indice des point d'apres p_m
    part = constructeurListIndiceBtw(pi,getTailleList2D(pts));
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
    listIndice hullG = getListIndice(hulls, num-1);
    listIndice hullD = getListIndice(hulls, num);
     // on met les indice des point entre p_i-1 et p_i
    part = constructeurListIndiceBtw(pdeb,pfin);
    for(int i = 0 ; i < getTailleIndice(hullG) ; i++){
      int hi = getIndice(hullG,i);
      if (hi<pdeb){ // on ajoute les points le l'envelope qui n'y sont pas
        addIndice(&part,hi);
      }
    }
    for(int j = 0 ; j < getTailleIndice(hullD) ; j++){
      int hi = getIndice(hullG,j);
      if (hi>=pfin){ // on ajoute les points le l'envelope qui n'y sont pas
        addIndice(&part,hi);
      }
    }
  }
  return part;
}

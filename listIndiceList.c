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
  newList.listPoint = list;
  return newList;
}


// --------- getteur --------- //

listIndice getListIndice(listIndiceList listindicelist, int i){
    if(i<0 || i>listindicelist.taille-1){
        printf("getListIndice : le numero de la liste d'indice n'existe pas");
        exit(1);
    }
    else{
        return listindicelist.indiceList[i];
    }
}


// --------- setteur --------- //

void setListIndice(listIndiceList* Liste, listIndice newlist, int i){
    if(i<0 || i>Liste->taille-1){
        printf("setListIndice : l'indice n'est pas valide");
        exit(1);
    }
    Liste->indiceList[i] = newlist;
}


// ------ fonction classe autre ------ //

void displayListIndiceList(listIndiceList liste){
    if(liste.indiceList == NULL){
        printf("displayListIndiceList : listeIndice.indice == NULL");
        exit(1);
    }
    for(int i=0; i<liste.taille; i++){
        displayListIndice(liste.indiceList[i]);
    }
    printf("\n");
}

void addListIndiceList(listIndiceList *listindicelist, listIndice list){
    listindicelist->taille++;
    listindicelist->indiceList = realloc(listindicelist->indiceList, listindicelist->taille*sizeof(listIndice));
    listindicelist->indiceList[listindicelist->taille-1] = list;
}


// ------ fonction triangulation ------ //

listIndiceList separatePointList(listPoint2D listPoint, int nbProcess){
  // partition des points parallélisé pour le calcul des la triangulation
    listIndiceList newListIndiceList;
    listPoint2D copyList = constructListPoint2DFromListPoint(listPoint);
    newListIndiceList.listPoint = copyList;
    newListIndiceList.taille = nbProcess;
    newListIndiceList.indiceList = (listIndice*) malloc(nbProcess*sizeof(listIndice));
    triByX(&copyList);
    listIndice pointForPath = findPointsPathIndice(copyList, nbProcess);
    printf("\n");
    displayListIndice(pointForPath);
    printf("\n");
    listIndiceList path = constructeurListIndiceListTaille(nbProcess-1, copyList);
#pragma omp parallel
    {
        int th_id = omp_get_thread_num();
        listPoint2D projec;
        if(th_id < nbProcess-1){
            projec = projectionWithIndice(copyList,getIndice(pointForPath,th_id));
            setListIndice(&path, Convex_HullIndice(projec), th_id);
        }
    }
    displayListIndiceList(path);
#pragma omp parallel
    {
        int th_id = omp_get_thread_num();
        listIndice group;
        if(th_id < nbProcess){
            if(th_id == nbProcess - 1){
                group = getRightSideList(copyList, path.indiceList[th_id-1]);
            }
            else if(th_id==0){
                group = getLeftSideList(copyList, path.indiceList[0]);
            }
            else{
                group = getMiddleSideList(copyList, path.indiceList[th_id-1], path.indiceList[th_id]);
            }
            setListIndice(&newListIndiceList, group, th_id);
        }
    }
    return newListIndiceList;
}

// listIndice partition(listPoint2D pts, listIndice ptsPath, listIndiceList hulls, int num, int nbProces){
//   listIndice part;
//   if (num >= nbProces || num < 0){
//     printf("le numéro n'est pas valide (num in [0 nbProces[])\n");
//     exit(1);
//   }
//   else if (num == 0){ // partition la plus à gauche
//     int pi = getIndice(ptsPath, num);
//     listIndice hull = getListIndice(hulls, num);
//      // on met les indice des point d'avant p_0
//     part = constructeurListIndiceBtw(0,pi);
//     for(int i = 0 ; i < getTailleIndice(hull) ; i++){
//       int hi = getIndice(hull,i);
//       if (hi>=pi){ // on ajoute les points le l'envelope qui n'y sont pas
//         addIndice(&part,hi);
//       }
//     }
//   }
//   else if (num == nbProces-1){ // partition la plus à droite
//     int pi = getIndice(ptsPath, num-1);
//     listIndice hull = getListIndice(hulls, num-1);
//      // on met les indice des point d'apres p_m
//     part = constructeurListIndiceBtw(pi,getTailleList2D(pts));
//     for(int i = 0 ; i < getTailleIndice(hull) ; i++){
//       int hi = getIndice(hull,i);
//       if (hi<pi){ // on ajoute les points le l'envelope qui n'y sont pas
//         addIndice(&part,hi);
//       }
//     }
//   }
//   else {
//     int pdeb = getIndice(ptsPath, num-1);
//     int pfin = getIndice(ptsPath, num);
//     listIndice hullG = getListIndice(hulls, num-1);
//     listIndice hullD = getListIndice(hulls, num);
//      // on met les indice des point entre p_i-1 et p_i
//     part = constructeurListIndiceBtw(pdeb,pfin);
//     for(int i = 0 ; i < getTailleIndice(hullG) ; i++){
//       int hi = getIndice(hullG,i);
//       if (hi<pdeb){ // on ajoute les points le l'envelope qui n'y sont pas
//         addIndice(&part,hi);
//       }
//     }
//     for(int j = 0 ; j < getTailleIndice(hullD) ; j++){
//       int hi = getIndice(hullG,j);
//       if (hi>=pfin){ // on ajoute les points le l'envelope qui n'y sont pas
//         addIndice(&part,hi);
//       }
//     }
//   }
//   return part;
// }


void removeListIndice(listIndiceList *list, int i){
    list->taille--;
    listIndice *tampon = list->indiceList;
    //list->indiceList = malloc(
}

listIndiceList getAllTrianglePossible(listPoint2D listPoint){
    listIndiceList newList = constructeurListIndiceList(listPoint);
    listIndice newTriangle = constructeurListIndiceTaille(3);
    for(int i=0; i<listPoint.taille-2; i++){
        for(int j=0; j<listPoint.taille-1; j++){
            for(int k=j; j<listPoint.taille; k++){
                setIndice(&newTriangle, i, 1);
                setIndice(&newTriangle, j, 2);
                setIndice(&newTriangle, k, 3);
            }
        }
    }
}

listIndiceList getTriangulation(listIndiceList list){
    listIndiceList triangulation = getAllTrianglePossible(list.listPoint);
}

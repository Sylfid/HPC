#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "listIndice.h"
#include "listIndiceList.h"
#include "listPoint.h"
#include "matriceTriangle.h"
#include "maillage.h"
#include "hedge.h"

matriceTriangle constructeurMatriceTriangle(int taille2){
    matriceTriangle newMatrice;
    newMatrice.taille = taille2;
    newMatrice.indiceList = (listIndice*) malloc(taille2*sizeof(listIndice));
    for(int i=0; i<taille2; i++){
        newMatrice.indiceList[i] = constructeurListIndice(i+1);
        for(int j=0; j<i+1; j++){
            setIndice(&newMatrice.indiceList[i], 0, j); 
        }
    }
    return newMatrice;
}

void addPath(matriceTriangle* matTri, int indice1, int indice2){
    if(indice1 <0 || indice1 > matTri->taille-1 || indice2<0 || indice2 > matTri->taille-1){
        printf("addPath : Ce chemin n'existe pas");
        exit(1);
    }
    else{
        int minIndice, maxIndice;
        if(indice1 < indice2){
            minIndice = indice1;
            maxIndice = indice2;
        }
        else{
            minIndice = indice2;
            maxIndice = indice1;
        }
        setIndice(&matTri->indiceList[maxIndice], 1, minIndice);  
    }
}


matriceTriangle calcmatTriDelaunay(listIndiceList list, int nbProcess){
// calcul de le arrets du maillage en combinant les triangle et les convexHull
// retourner une liste de liste de 2 points
  maillage allTriangles = getTriangulation(list,nbProcess);
  listPoint2D pts = getPointMaillage(allTriangles);
    matriceTriangle newMatTri = constructeurMatriceTriangle(getTailleList2D(pts));
  // listIndiceList test = constructeurListIndiceList(pts);
  listIndiceList pathTriangles;
  listIndice triangle;
  Point2D a, b, c;
  for(int j=0 ; j<getTailleMaillage(allTriangles) ; j++){ // chaque path
    pathTriangles = getListIndiceList(allTriangles,j);
    for(int i=0 ; i<getTailleListIndice(pathTriangles) ; i++){ // chaque triangle
      triangle = getListIndice(pathTriangles,i);
      a = getPoint2D(pts,getIndice(triangle,0));
      b = getPoint2D(pts,getIndice(triangle,1));
      c = getPoint2D(pts,getIndice(triangle,2));
      
      addHedgeByPoints(&res, a, c);
      addHedgeByPoints(&res, b, c);
    }
  }
  return res;
}

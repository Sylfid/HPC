#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "point.h"
#include "listPoint.h"
#include "listPointList.h"
#include "listIndice.h"


int main()

{
    printf("Triangulation de Denaulay\n");
    // Choix nombre de thread
    int nthreads = 4; // m = nombre de threads
    omp_set_num_threads(nthreads);
    int id

    // Definition des variable
    listPoint2D P; // Ensemble des points
    listeIndice pPath; // Indices des nthreads m-1 de séparation
    listPoint2D proj; // projection parabole 3D + plan orthogonal
    listIndiceList H; // list de lonqueure m-1, H[i]=liste des indice des points
                      // de la frontière convexe entre Q[i-1] et Q[i]
    H = constructeurListIndiceList(P);
    listIndiceList Q; // list de lonqueure m, Q[i]=liste indice des pts
                      // de la ième partition de l'espace
    Q = constructeurListIndiceListTaille(nthreads, P);

    // Chargement des points dans le fichier test
    P = constructListPoint2DFromFile("test");
    // Tri les points selon leure coordonée x
    triByX(&P);
    // Trouver les points de la partition
    pPath = findPointsPathIndice(P,nthreads);
    for(int i = 0 ; i < getTailleIndice(pPath) ; i++){
      // calcul des frontières pour tout i
       proj = projectionWithIndice(P, getIndice(pPath, i));
       addListIndiceList(H, Convex_HullIndice(proj));
    }

    // paralélisation de la partition
    listIndice part;
    #pragma omp parallel private(id,partition) shared(nthreads, Q)
   {
      omp_get_thread_num();
      if(id<nthreads){
          part = partition(P, pPath, H, id, nthreads);
          setListIndice(&Q, part, id);
      }
   }


    return 0;

}

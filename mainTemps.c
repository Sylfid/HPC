#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "listPoint.h"
#include "hedge.h"
#include "listIndice.h"
#include "listIndiceList.h"
#include "maillage.h"
#include "matriceTriangle.h"
#include <time.h>


int main()

{
  float tps;
  clock_t t1, t2;
  int nthreads;
  int max = 100; // omp_get_max_threads()+1;

  printf("\n\nm = %d \n", max);
  printf("y = [");


  // Definition des variable
  listPoint2D P; // Ensemble des points
  listIndiceList Q; // list de lonqueure m, Q[i]=liste indice des pts
                    // de la ième partition de l'espace
  maillage T; // list des liste des triangles de Delaunay par path
              // triangle = list de 3 indices
  hedge H; // list des aretes de maillage de Delaunay
                    // arete = list de 2 point
  // Chargement des points dans le fichier test
  P = constructListPoint2DFromFile("test500");


  // printf("Threads | Temps \n");
  for(int i=2 ; i<max ; i++){
    // Choix nombre de thread
    nthreads = i; // m = nombre de threads
    omp_set_num_threads(nthreads);

    t1 = clock();
    // Partition des points
    Q = separatePointList(P, nthreads);

    // calcul de arretes de la triangulation
    H = calcHedgeDelaunay(Q, nthreads);

    t2 = clock();

    tps = (float)(t2-t1)/CLOCKS_PER_SEC;
    // if(nthreads<10){
    //   printf("   %d    |  %f  \n",nthreads, tps);
    // }
    // else{
    //   printf("  %d    |  %f  \n",nthreads, tps);
    // }
    if(i<max-1){
      printf("%f, ",tps);
    }
    else{
      printf("%f]\n\n",tps);
    }

  }

  return 0;

}

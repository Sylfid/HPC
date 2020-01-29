#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "listPoint.h"
#include "hedge.h"
#include "listIndice.h"
#include "listIndiceList.h"
#include "maillage.h"
#include "matriceTriangle.h"


int main()

{
    printf(" - - - - - - Triangulation de Denaulay - - - - - - \n");
    // Choix nombre de thread
    int nthreads = 2; // m = nombre de threads
    omp_set_num_threads(nthreads);
    // Definition des variable
    listPoint2D P; // Ensemble des points
    listIndiceList Q; // list de lonqueure m, Q[i]=liste indice des pts
                      // de la ième partition de l'espace
    maillage T; // list des liste des triangles de Delaunay par path
                // triangle = list de 3 indices
    hedge H; // list des aretes de maillage de Delaunay
                      // arete = list de 2 point
    // Chargement des points dans le fichier test
    P = constructListPoint2DFromFile("test3");
    printf(" - - - - - - - fichier téléchargé - - - - - - - \n");
    // Partition des points
    Q = separatePointList(P, nthreads);
    printf(" - - - - - ensemble des points partitioné - - - - - \n");
    // calcul de arretes de la triangulation
    H = calcHedgeDelaunay(Q, nthreads);
    printf(" - - - - - maillage calculée - - - - - \n");

    //Afficher les résultats
    displayHedge(H);
    printf("Poiur %d threads il y a %d arrete \n",nthreads, getTailleHedge(H));

  printf(" - - - FIN - - - \n");
  return 0;

}

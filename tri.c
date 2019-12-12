#include "listPoint.h"
#include "point.h"

void triByX(listPoint2D pts){
  // tri par insertion en fonction des coordonées x des points
  int j;
  int n = getTailleList2D(pts);
  Point2D save;
  for(int i=1 ; i<n ; i++) { // parcour de la liste
    if (getXListPoint2D(pts,i) < getXListPoint2D(pts,i-1)) {
      // point mal placé
      j = 0;
      while (getXListPoint2D(pts,j) < getXListPoint2D(pts,i)) j++;
      // j : nouvelle position du point
      save = getPoint2D(pts, i); // on sauvegarde le point
      for(int k = i-1 ; k >= j ; k--){
        // translation des autres points
        setListPoint2DFromPoint(&pts, getPoint2D(pts,k), k+1);
      }
      setListPoint2DFromPoint(&pts, save, j);
    }
  }
}

listPoint2D findPointsPath(listPoint2D pts, int nbproces){
  triByX(pts); // tri selon coordoné x
  listPoint2D pointsPath = constructListPoint2D(nbproces-1);
  for(int i=1 ; i<nbproces ; i++){
    int pas = floor(getTailleList2D(pts)/nbproces);
    setListPoint2DFromPoint(&pointsPath, getPoint2D(pts, i*pas), i-1);
  }
}

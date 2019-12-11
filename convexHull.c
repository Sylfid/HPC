/* source :
 * https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
 */
 #include "listPoint.h"
 #include "point.h"
 #include <stdbool.h>
 #include <stdio.h>
 #include <stdlib.h>

// Orientation du triangle (p, q, r).
// val = 0 --> p, q, r colineaires
// val > 0 --> Clockwise
// val < 0 --> Counterclockwise
// return True si c'est antihoraire
bool orientation(Point2D p, Point2D q, Point2D r) {
  float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  return val<0;
}

// Calcul la distant entre 2 points
int dist(Point2D p1, Point2D p2){
  return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// Calcul de l'envelope convexe
/* source :
https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
*/
listPoint2D Convex_Hull(listPoint2D pts){
  int n = getTailleList2D(pts);

  // Il faut plus de 3 points
  if (n < 3){
    printf("pas assez de point \n");
    exit(1);
  }

  // trouver le point le plus gauche
  int l = 0;
  for(int i = 1; i < n; i++) {
    if(getXListPoint2D(pts,i) < getYListPoint2D(pts,l)){
      l=i;
    }
  }

  // init res avec le point le plus à gauche
  listPoint2D hull = constructListPoint2D(0); // le 0 ça marche ??
  // setListPoint2D(hull, getPoint2D(pts, l), 0);

  // Construction hull
  int p = l, q;
  do{
    // addListPoint2D(hull, getPoint2D(pts, p))
    q = (p + 1) % n;
    for (int x = 0; x < n; x++){
      // On cherche le point q le plus "counterclockwise"
      if (orientation(getPoint2D(pts,p), getPoint2D(pts,x), getPoint2D(pts,q))){
        q = x; // x est plus "counterclockwise" que q
      }
    }
    p = q; // à la fin c'est q le plus "counterclockwise"
  } while (p != l);  // On continu jusqu'a revenir au 1er

  return hull;
}

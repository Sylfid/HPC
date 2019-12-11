/* source :
 * https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
 */
 #include "listPoint.h"
 #include "point.h"
 #include <stdbool.h>
 #include <stdio.h>
 #include <stdlib.h>

typedef struct {
  double x;
  double y;
} point_t;

typedef point_t* point_ptr_t;

 bool ccw(const Point2D *a, const Point2D *b, const Point2D *c) {
     return (b->x - a->x) * (c->y - a->y) > (b->y - a->y) * (c->x - a->x);
 }

// inverser deux points
void swap(Point2D *v1, Point2D *v2){
   Point2D temp = *v1;
   *v1 = *v2;
   *v2 = temp;
}

//If the points co linear=0, clockwise>0;anticlockwise<0
int orientation(Point2D p, Point2D q, Point2D r) {
  int val = (int)(q.y - p.y) * (r.x - q.x) - ( int)(q.x - p.x) * (r.y - q.y);
  return val;
}

//calcul la distant entre 2 points
int dist(Point2D p1, Point2D p2){
  return (int)(p1.x - p2.x)*(p1.x - p2.x) + ( int)(p1.y - p2.y)*(p1.y - p2.y);
}

listPoint2D Convex_Hull(listPoint2D pts){
  // Calcul convex hull of a set of points.
  int n = getTailleList2D(pts);
  // Il faut plus de 3 points
  if (n < 3){
    printf("pas assez de point \n");
    exit(1)
  }
  // trouver le point le plus gauche
  int l = 0;
  for(int i = 1; i < n; i++) {
    if(getXListPoint2D(pts,i) < getYListPoint2D(pts,l)){
      l=i;
    }
  }
  // init res
  listPoint2D hull = constructListPoint2D(1)
  // mettre hull[0] = getPoint2D(pts,l)
         // Start from leftmost point, keep moving
         // counterclockwise until reach the start point
         // again. This loop runs O(h) times where h is
         // number of points in result or output.
         int p = l, q;
         do
         { 
             // Add current point to result
             hull.Add(points[p]);

             // Search for a point 'q' such that
             // orientation(p, x, q) is counterclockwise
             // for all points 'x'. The idea is to keep
             // track of last visited most counterclock-
             // wise point in q. If any point 'i' is more
             // counterclock-wise than q, then update q.
             q = (p + 1) % n;

             for (int i = 0; i < n; i++)
             {
             // If i is more counterclockwise than
             // current q, then update q
             if (orientation(points[p], points[i], points[q])
                                                 < 0)
                 q = i;
             }

             // Now q is the most counterclockwise with
             // respect to p. Set p as q for next iteration,
             // so that q is added to result 'hull'
             p = q;

         } while (p != l); // While we don't come to first
                         // point

         // Print Result
         foreach (Point temp in hull)
             Console.WriteLine("(" + temp.x + ", " +
                                 temp.y + ")");
     }

/* source :
https://rosettacode.org/wiki/Convex_hull#C.2B.2B
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tPoint {
    int x, y;
} Point;

typedef struct tNode {
    Point data;
    struct tNode *next;
} Node;

bool ccw(const Point *a, const Point *b, const Point *c) {
    return (b->x - a->x) * (c->y - a->y)
         > (b->y - a->y) * (c->x - a->x);
}

int comp(const void *lhs, const void *rhs) {
    Point lp = *((Point *)lhs);
    Point rp = *((Point *)rhs);
    if (lp.x < rp.x) return -1;
    if (rp.x < lp.x) return 1;
    return 0;
}

void freeNode(Node *ptr) {
    if (ptr == NULL) {
        return;
    }

    freeNode(ptr->next);
    ptr->next = NULL;
    free(ptr);
}

Node* pushBack(Node *ptr, Point data) {
    Node *tmp = ptr;

    if (ptr == NULL) {
        ptr = (Node*)malloc(sizeof(Node));
        ptr->data = data;
        ptr->next = NULL;
        return ptr;
    }

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    tmp->next = (Node*)malloc(sizeof(Node));
    tmp->next->data = data;
    tmp->next->next = NULL;
    return ptr;
}

Node* popBack(Node *ptr) {
    Node *tmp = ptr;

    if (ptr == NULL) {
        return NULL;
    }
    if (ptr->next == NULL) {
        free(ptr);
        return NULL;
    }

    while (tmp->next->next != NULL) {
        tmp = tmp->next;
    }

    free(tmp->next);
    tmp->next = NULL;
    return ptr;
}

void print(Node *ptr) {
    printf("[");
    if (ptr != NULL) {
        printf("(%d, %d)", ptr->data.x, ptr->data.y);
        ptr = ptr->next;
    }
    while (ptr != NULL) {
        printf(", (%d, %d)", ptr->data.x, ptr->data.y);
        ptr = ptr->next;
    }
    printf("]");
}

Node* convexHull(int len, Point p[]) {
    Node *h = NULL;
    Node *hptr = NULL;
    size_t hLen = 0;
    int i;

    qsort(p, len, sizeof(Point), comp);

    /* lower hull */
    for (i = 0; i < len; ++i) {
        while (hLen >= 2) {
            hptr = h;
            while (hptr->next->next != NULL) {
                hptr = hptr->next;
            }
            if (ccw(&hptr->data, &hptr->next->data, &p[i])) {
                break;
            }

            h = popBack(h);
            hLen--;
        }

        h = pushBack(h, p[i]);
        hLen++;
    }

    /* upper hull */
    for (i = len - 1; i >= 0; i--) {
        while (hLen >= 2) {
            hptr = h;
            while (hptr->next->next != NULL) {
                hptr = hptr->next;
            }
            if (ccw(&hptr->data, &hptr->next->data, &p[i])) {
                break;
            }

            h = popBack(h);
            hLen--;
        }

        h = pushBack(h, p[i]);
        hLen++;
    }

    popBack(h);
    return h;
}

int main() {
    Point points[] = {
        {16,  3}, {12, 17}, { 0,  6}, {-4, -6}, {16,  6},
        {16, -7}, {16, -3}, {17, -4}, { 5, 19}, {19, -8},
        { 3, 16}, {12, 13}, { 3, -4}, {17,  5}, {-3, 15},
        {-3, -9}, { 0, 11}, {-9, -3}, {-4, -2}, {12, 10}
    };

    Node *hull = convexHull(sizeof(points) / sizeof(Point), points);
    printf("Convex Hull: ");
    print(hull);
    printf("\n");

    freeNode(hull);
    hull = NULL;

    return 0;
}


/* source :
https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
*/
// C# program to find convex hull of a set of points. Refer
// https://www.geeksforgeeks.org/orientation-3-ordered-points/
// for explanation of orientation()
using System;
using System.Collections.Generic;

public class Point
{
    public int x, y;
    public Point(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
}

public class GFG
{

    // To find orientation of ordered triplet (p, q, r).
    // The function returns following values
    // 0 --> p, q and r are colinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    public static int orientation(Point p, Point q, Point r)
    {
        int val = (q.y - p.y) * (r.x - q.x) -
                (q.x - p.x) * (r.y - q.y);

        if (val == 0) return 0; // collinear
        return (val > 0)? 1: 2; // clock or counterclock wise
    }

    // Prints convex hull of a set of n points.
    public static void convexHull(Point []points, int n)
    {
        // There must be at least 3 points
        if (n < 3) return;

        // Initialize Result
        List<Point> hull = new List<Point>();

        // Find the leftmost point
        int l = 0;
        for (int i = 1; i < n; i++)
            if (points[i].x < points[l].x)
                l = i;

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
                                                == 2)
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

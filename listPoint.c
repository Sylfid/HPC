#include <stdio.h>
#include <stdlib.h>
#include "listPoint.h"
#include "point.h"
#include <math.h>
#include <stdbool.h>

listPoint2D constructListPoint2D(int taille2){
    listPoint2D newListPoint;
    newListPoint.taille = taille2;
    if(taille2 == 0){
        newListPoint.point = NULL;
    }
    else{
        newListPoint.point = (Point2D*) malloc(taille2*sizeof(Point2D));
    }
    return newListPoint;
}

listPoint3D constructListPoint3D(int taille2){
    listPoint3D newListPoint;
    newListPoint.taille = taille2;
    newListPoint.point = (Point3D*) malloc(taille2*sizeof(Point3D));
    return newListPoint;
}

void freeListPoint2D(listPoint2D* listPoint){
    free(listPoint->point);
}

void freeListPoint3D(listPoint3D* listPoint){
    free(listPoint->point);
}

listPoint2D constructListPoint2DFromFile(char* fileName){
    FILE* file = NULL;
    file = fopen(fileName, "r");
    if (file != NULL){
        char a;
        int firstLine = 1, flag = 1, lecNb = 0;
        double valeur=0.;
        int composante = 0, compteurDec = 0, compteurPoint = 0, negativite = 1, tailleList = 0;
        int decimal = 0;
        listPoint2D newList;

        while(firstLine && flag){
            a = fgetc(file);
            if(a == 10){
                firstLine = 0;
            }
            else if(a>47 && a<58){
                tailleList = tailleList * 10 + (a-48);
            }
            else{
                printf("Le fichier du nuage de points n'est pas au bon format\n");
                exit(1);
            }
        }
        newList.point = (Point2D*) malloc(tailleList * sizeof(Point2D));
        newList.taille = tailleList;
        printf("%d \n", tailleList);
        a = fgetc(file);
        while(a != EOF && flag){
            if(a>47 && a<58){
                lecNb = 1;
                if(decimal){
                    compteurDec = compteurDec+1;
                }
                if(compteurDec == 0){
                    valeur = valeur*10 + (a-48);
                }
                else{
                    valeur = valeur + pow(10.,-(double)compteurDec)*(a-48);
                }
            }
            else if(a == 32){
                if(lecNb){
                    if(composante == 0){
                        setXPoint2D(&newList.point[compteurPoint],negativite*valeur);
                        //printf("%f aa \n", getXPoint2D(newList.point[compteurPoint]));
                    }
                    else{
                        printf("Il y a trop d'argument sur la ligne %d \n", compteurPoint);
                        exit(1);
                    }
                    composante = (composante + 1);
                    decimal = 0;
                    compteurDec = 0;
                    valeur = 0.;
                    negativite = 1;
                }
                lecNb = 0;
            }
            else if(a == 10){
                setYPoint2D(&newList.point[compteurPoint], negativite * valeur);
                composante = 0;
                valeur = 0.;
                decimal = 0;
                compteurDec = 0;
                compteurPoint ++;
                negativite = 1;
                lecNb = 0;
                if(compteurPoint >= newList.taille){
                    a = fgetc(file);
                    if(a != EOF){
                        printf("Le fichier est mal calibre\n");
                        exit(1);
                    }
                    flag = 0;
                }
            }
            else if(a == 46){
                decimal = 1;
            }
            else if(a == 45){
                negativite = -1;
            }
            else{
                printf("Un caractere du fichier est illisible : ");
                printf("%c\n", a);
            }
            a = fgetc(file);
        }
        if(compteurPoint != newList.taille){
            printf("Le fichier est mal calibre\n");
            exit(1);
        }
        fclose(file);
        return newList;

    }
    else{
        printf("Impossible d'ouvrir le fichier ");
        printf("%s\n", fileName);
        exit(1);
    }
}

void setListPoint2DToZero(listPoint2D *listPoint){
    for(int i=0; i<listPoint->taille; i++){
        setPoint2D(&listPoint->point[i], 0., 0.);
    }
}

void setListPoint3DToZero(listPoint3D *listPoint){
    for(int i=0; i<listPoint->taille; i++){
        setPoint3D(&listPoint->point[i], 0., 0., 0.);
    }
}

void displayListPoint2D(listPoint2D listPoint){
    for(int i=0; i<listPoint.taille; i++){
        displayPoint2D(listPoint.point[i]);
        printf("\n");
    }
}

void displayListPoint3D(listPoint3D listPoint){
    for(int i=0; i<listPoint.taille; i++){
        displayPoint3D(listPoint.point[i]);
        printf("\n");
    }
}

Point2D getPoint2D(listPoint2D listPoint, int i){
    if(i >= listPoint.taille || i<0){
        printf("getPoint2D : le numero du point est invalide");
        exit(1);
    }
    return listPoint.point[i];
}

float getXListPoint2D(listPoint2D listPoint, int i){
    if(i >= listPoint.taille || i<0){
        printf("getXListPoint2D : le numero du point est invalide");
        exit(1);
    }
    return getXPoint2D(listPoint.point[i]);
}

float getYListPoint2D(listPoint2D listPoint, int i){
    if(i >= listPoint.taille || i<0){
        printf("getYListPoint2D : le numero du point est invalide");
        exit(1);
    }
    return getYPoint2D(listPoint.point[i]);
}

float getXListPoint3D(listPoint3D listPoint, int i){
    return getXPoint3D(listPoint.point[i]);
}

float getYListPoint3D(listPoint3D listPoint, int i){
    return getYPoint3D(listPoint.point[i]);
}

float getZListPoint3D(listPoint3D listPoint, int i){
    return getZPoint3D(listPoint.point[i]);
}

int getTailleList2D(listPoint2D listPoint){
    return listPoint.taille;
}

int getTailleList3D(listPoint3D listPoint){
    return listPoint.taille;
}

void setXListPoint2D(listPoint2D *listPoint, float a, int i){
    if(i >= listPoint->taille || i<0){
        printf("setXListPoint2D : le numero du point est invalide\n");
        exit(1);
    }
    printf("%d %d\n",listPoint->taille, i);
    //setXPoint2D(&listPoint->point[i],a);
    listPoint->point[i].x = a;
}

void setYListPoint2D(listPoint2D *listPoint, float a, int i){
    if(i >= listPoint->taille || i<0){
        printf("setYListPoint2D : le numero du point est invalide\n");
        exit(1);
    }
    setYPoint2D(&listPoint->point[i],a);
}

void setXListPoint3D(listPoint3D *listPoint, float a, int i){
    setXPoint3D(&listPoint->point[i],a);
}

void setYListPoint3D(listPoint3D *listPoint, float a, int i){
    setYPoint3D(&listPoint->point[i],a);
}

void setZListPoint3D(listPoint3D *listPoint, float a, int i){
    setZPoint3D(&listPoint->point[i],a);
}

void setListPoint3D(listPoint3D *listPoint, float x2, float y2, float z2, int i){
    setPoint3D(&listPoint->point[i], x2, y2, z2);
}

void setListPoint2D(listPoint2D *listPoint, float x2, float y2, int i){
    if(i >= listPoint->taille || i<0){
        printf("setListPoint2D : le numero du point est invalide");
        exit(1);
    }
    setPoint2D(&listPoint->point[i], x2, y2);
}

listPoint3D projectionOnParaboloid(listPoint2D listPoint, float a, float b){
    if(a == 0 || b == 0){
    }
    else{
        listPoint3D newList = constructListPoint3D(getTailleList2D(listPoint));
        float x2 = 0., y2 = 0., z2 = 0.;
        for(int i=0; i<getTailleList2D(listPoint); i++){
            x2 = getXListPoint2D(listPoint, i);
            y2 = getYListPoint2D(listPoint, i);
            z2 = (x2/a)*(x2/a) + (y2/b)*(y2/b);
            setListPoint3D(&newList, x2, y2, z2, i);
        }
        return newList;
    }
}

void setListPoint2DFromPoint(listPoint2D *listPoint, Point2D point, int i){
    if(i >= listPoint->taille || i<0){
        printf("setListPoint2DFromPoint : le numero du point est invalide\n");
        exit(1);
    }
    setXListPoint2D(listPoint, getXPoint2D(point), i);
    setYListPoint2D(listPoint, getYPoint2D(point), i);
}

void addPoint2DFromPoint(listPoint2D *listPoint, Point2D point){
    listPoint->taille++;
    listPoint->point = realloc(listPoint->point, listPoint->taille*sizeof(listPoint2D));
    setListPoint2DFromPoint(listPoint, point, listPoint->taille-1);
}

void addPoint2D(listPoint2D *listPoint, float x2, float y2){
    listPoint->taille++;
    listPoint->point = realloc(listPoint->point, listPoint->taille*sizeof(listPoint2D));
    setListPoint2D(listPoint, x2, y2, listPoint->taille-1);
}

listPoint2D projection(listPoint2D listPoint, int j){
  Point2D p = getPoint2D(listPoint, j);
  float py = getXPoint2D(p);
  int n = getTailleList2D(listPoint);
  listPoint2D nwList = constructListPoint2D(n);
  for(int i = 0; i<n ; i++){
    setListPoint2D(&nwList,getYListPoint2D(listPoint,i)-py, sqrt_dif(p, getPoint2D(listPoint, i)), i);
  }
  return nwList;
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
    if(getXListPoint2D(pts,i) < getXListPoint2D(pts,l)){
      l=i;
    }
  }

  // init res avec le point le plus à gauche
  listPoint2D hull = constructListPoint2D(0);

  // Construction hull
  int p = l, q;
  bool flag = false;
  do{
    addPoint2DFromPoint(&hull, getPoint2D(pts, p));
    q = (p + 1) % n;
    for (int x = 0; x < n; x++){
      // On cherche le point q le plus "counterclockwise"
      if (orientation(getPoint2D(pts,p), getPoint2D(pts,x), getPoint2D(pts,q))){
        q = x; // x est plus "counterclockwise" que q
      }
    }
    flag = (getXListPoint2D(pts, p) > getXListPoint2D(pts, q));
    p = q; // à la fin c'est q le plus "counterclockwise"
  } while (p != l && !flag);  // On continu jusqu'a revenir au 1er*/

  return hull;
}

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

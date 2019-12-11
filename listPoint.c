#include <stdio.h>
#include <stdlib.h>
#include "listPoint.h"
#include "point.h"
#include <math.h>

listPoint2D constructListPoint2D(int taille2){
    listPoint2D newListPoint;
    newListPoint.taille = taille2;
    newListPoint.point = (Point2D*) malloc(taille2*sizeof(Point2D));
    return newListPoint;
}

listPoint3D constructListPoint3D(int taille2){
    listPoint3D newListPoint;
    newListPoint.taille = taille2;
    newListPoint.point = (Point3D*) malloc(taille2*sizeof(Point3D));
    return newListPoint;
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
                printf("Un caractere du fichier est illisible ");
                printf("\n");
            }
            a = fgetc(file);
        }
        if(compteurPoint != newList.taille){
            printf("Le fichier est mal calibre\n");
            exit(1);
        }
        return newList;

        fclose(file);
    }
    else{
        printf("Impossible d'ouvrir le fichier ");
        printf(fileName);
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

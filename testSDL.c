#include <SDL2/SDL.h>
#include <stdio.h>
#include "listPoint.h"
#include "hedge.h"
#include <math.h>

float min2(float x, float y){
    if(x < y){
        return x;
    }
    else{
        return y;
    }
}
float max2(float x, float y){
    if(x > y){
        return x;
    }
    else{
        return y;
    }
}

SDL_Point* getSDLPoint(listPoint2D listPoint){
    int listTaille = getTailleList2D(listPoint);
    SDL_Point* list = (SDL_Point*) malloc(listTaille*sizeof(SDL_Point));
    float xmin=getXListPoint2D(listPoint,0);
    float xmax=getXListPoint2D(listPoint,0);
    float ymin=getYListPoint2D(listPoint,0);
    float ymax=getYListPoint2D(listPoint,0);
    int xact, yact;
    for(int i=0; i<listTaille; i++){
        xact = getXListPoint2D(listPoint, i);
        yact = getYListPoint2D(listPoint, i);
        xmin = min2(xmin, xact); 
        xmax = max2(xmax, xact);
        ymin = min2(ymin, yact); 
        ymax = max2(ymax, yact);
    }
    for(int i=0; i<listTaille; i++){
        list[i].x = 640*(getXListPoint2D(listPoint,i) - xmin)/(xmax-xmin);
        list[i].y = 480*(getYListPoint2D(listPoint,i) - ymin)/(ymax-ymin);
    }
    return list;
}

void displayListPointInterface(SDL_Renderer* ren, listPoint2D listPoint){
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    if (SDL_RenderDrawPoints(ren, getSDLPoint(listPoint), getTailleList2D(listPoint)) != 0){
        fprintf(stderr,"SDL_RenderDrawPoints Error: %s",SDL_GetError());
        SDL_Quit();
    }
    //SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_RenderPresent(ren);

}

void displayHedgeInterface(SDL_Renderer* ren, hedge edge){
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    listPoint2D actualEdge;
    for(int i=0; i<getTailleHedge(edge); i++){
        actualEdge = getOneHedge(edge, i);
        if ( SDL_RenderDrawLines(ren, getSDLPoint(getOneHedge(edge,i)),2) != 0){
            fprintf(stderr,"SDL_RenderDrawLine Error: %s",SDL_GetError());
            SDL_Quit();
        }
    }
    //SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_RenderPresent(ren);
}


int main(int argc, char** argv)
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Création de la fenêtre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  640,
                                                                  480,
                                                                  SDL_WINDOW_SHOWN);

        if( pWindow )
        {
            SDL_Renderer *ren = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (ren == NULL){
                SDL_DestroyWindow(pWindow);
                fprintf(stderr,"SDL_CreateRenderer Error: %s",SDL_GetError());
                SDL_Quit();
                return 1;
            }
            /*SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
            SDL_Point point = {320, 240};
            if (SDL_RenderDrawPoints(ren, &point, 1) != 0){
                SDL_DestroyWindow(pWindow);
                fprintf(stderr,"SDL_RenderDrawPoints Error: %s",SDL_GetError());
                SDL_Quit();
                return 1;
            }*/
            listPoint2D list = constructListPoint2DFromFile("test3");
            displayListPointInterface(ren, list);
            listIndiceList Q = separatePointList(list, 4);
            hedge newedge = calcHedgeDelaunay(Q, 4);
            displayHedge(newedge);
            displayHedgeInterface(ren, newedge);
            SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
            SDL_Rect rectangle;
            rectangle.x = 590;
            rectangle.y = 430;
            rectangle.w = 50;
            rectangle.h = 50;
            SDL_RenderFillRect(ren, &rectangle);
            //Render the rect to the screen
            SDL_RenderPresent(ren);

            SDL_Delay(5000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */

            SDL_DestroyWindow(pWindow);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();

    return 0;
}

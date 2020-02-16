# HPC : Triangulation de Delaunay
## Contexte
Ce projet consiste à calculer la triangulation de Delaunay pour un ensemble de points en utilisant la programmation multi-thread.



## Interface, bibliothèque
* openMp
* sdl2/SDL
* stdio
* math



## Fonctionnement
### Création des ensembles de points
* Fichier sous le format :

[nombre de points]

[coordonnée x] [coordonnée y] 

[coordonnée x] [coordonnée y] 

[coordonnée x] [coordonnée y] 

...


* Création automatique :

Fichier : constructeurListPoint.c

1 - mettre le nombre de points désiré dans la variable : nbPoint

2 - choisir les valeurs de coordonnées max et min dans les variables : MAX et MIN

3 - choisir le nom du fichier sortant : file = fopen("NOM_FICHIER", "w+");


Compiler et exécuter
```
gcc constructeurListPoint.c -o constructeurListPoint
./constructeurListPoint.o
rm constructeurListPoint.o
```


### Exécution du programme
Choix du fichier qui contient l'ensemble de points dans les fichiers main[].c ou dans testDSL.c (pour l'affichage)

```
make
./main[]
```
* mainFinal : calcul la triangulation et affiche les coordonnées des points des arêtes obtenues.

* mainInterface : calcul la triangulation et affiche le maillage dans une fenêtre graphique.

* mainTemps : calcul le temps d'exécution du programme pour différents nombres de points et affiche les résultats dans les terminals. Pour tracer les courbes : copier les résultats dans le terminal et les coller dans le fichier trace.py puis exécuter avec la commande :
```
python trace.py
```


## Auteurs
* **Rémy Lavainne**
* **Michelle Malara**

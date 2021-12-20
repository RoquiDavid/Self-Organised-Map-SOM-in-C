#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct vec{
    double *v; //Tableau contenant les vecteur donnee
    double norme; //Norme du tableau de vecteur
    char *etiquette; //Tableau contenant les etiquettes (label) des donnees
}vec;
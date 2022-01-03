#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
    double *weight; //Vecteur poid
    double act; //Fonction d'activation (distance euclidienne)
    int id; //Nom de la données (classe de la données)
    char label; //Label of the node
    char **stats; // Statistical array that give us a better precision
}node;

//Structure d'une best matching unit
typedef struct bmu{
    int c;  //Colonne de la bmu
    int l;  //Ligne de la bmu
    struct bmu *next; //reference vers le potentiel "gagnant" suivant
}bmu;

//Structure de la "grille" du reseau du     SOM
typedef struct net{
    int nb_colonne; //Nombre de colonne
    int nb_ligne;   //Nombre de ligne
    int nb_node; //Nombre de neuronnes
    struct bmu *best_unit; //Coordonées de la BMU
    struct node** map;  //Reference vers la matrice de neuronne
    int nb_iteration;   //Nombre d'iteration
    double alpha;   //Taux d apprentissage (learning rate)
    int taille_voisinnage;  //Taille du voisionnage autorisee
}net;


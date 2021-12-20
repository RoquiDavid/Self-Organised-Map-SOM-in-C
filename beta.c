#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "function.c"
//#include "net.h"

void modif(int **array, int col, int ligne, int max)
{

    int cpt = 0;
    int perim = 1;
    int limit = 3;
    while (cpt < max)
    {
        // TOP
        for (int i = col + 1 * perim; i >= col - 1 * perim; i--)
        {
            if (cpt >= max)
            {
                break;
            }

            array[ligne - 1 * perim][i] = 2;

            cpt++;
        }

         // LEFT
        for (int i = ligne - 1 * perim+1 ; i <= ligne + 1 * perim; i++)
        {
            if (cpt >= max)
            {
                break;
            }

            array[i][col - 1 * perim] = 4;

            cpt++;
        }
        // BOT
        for (int i = col - 1 * perim + 1; i <= col + 1 * perim; i++)
        {
            if (cpt >= max)
            {
                break;
            }
            array[ligne + 1 * perim][i] = 3;

            cpt++;
        }
       
        //RIGHT
        for (int i = ligne + 1 * perim - 1; i >= ligne - 1 * perim; i--)
        {

            if (cpt >= max)
            {
                break;
            }

            array[i][col + 1 * perim] = 5;

            cpt++;
        }

        perim++;
    }
}

int main(int argc, char *argv[], char *env[])
{

    int **i = (int **)malloc(sizeof(int *) * 10);

    for (int k = 0; k < 10; k++)
    {
        i[k] = (int *)malloc(sizeof(int) * 10);
    }
    int cpt = 0;
    for (int l = 0; l < 10; l++)
    {
        for (int a = 0; a < 10; a++)
        {
            i[l][a] = 1;
            cpt++;
        }
    }

    for (int l = 0; l < 10; l++)
    {
        for (int a = 0; a < 10; a++)
        {
            printf("%d ", i[l][a]);
        }
        printf("\n");
    }

    modif(i, 6, 6, 22);

    printf("\n");
    for (int l = 0; l < 10; l++)
    {
        for (int a = 0; a < 10; a++)
        {
            printf("%d ", i[l][a]);
        }
        printf("\n");
    }
    /*double random_data;
    double min = 2;
    double max  =3;
    random_data = (double) rand() / ((double) RAND_MAX + 1);
    printf("%f",min + random_data * (max - min));
    /*
    int *a = (int *)malloc(sizeof(int) * 3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    int *b = (int *)malloc(sizeof(int) * 3);

    b = a;

    for (int k=0; k<3; k++) {
        printf("%d",b[k]);
    }
    /*
    double *a = (double *)calloc(10,sizeof(double));
    for(int i = 0; i < 10; i++){
        a[i] = i;
    }
    for(int t = 0; t < 2000; t ++){
        swap(a + (rand() % 9), a + (rand() % 9));
    }
    printf("\n");
    for(int i = 0; i < 10; i++){
        printf("X[%d] = %f\n", i, a[i]);
    }
    /*

    for(int i = 0; i < 10; i++){
        printf("X[%d] = %f\n", i, a[i]);
    }
    bmu * b1 = (bmu*)calloc(1,sizeof(bmu));
    bmu * b2 = (bmu*)calloc(1,sizeof(bmu));
    bmu * b3 = (bmu*)calloc(1,sizeof(bmu));

    b1->c = 1;
    b2->c = 2;
    b3->c = 3;

    b1->l = 1;
    b2->l = 2;
    b3->l = 3;

    b1->next = b2;
    b2->next = b3;
    b3->next = NULL;


    bmu *tmp = b1;
    bmu *head = b1;
    while(tmp != NULL){
        if(tmp->next == NULL){
            printf("%d, %d\n", tmp->c, tmp->l);
        }
        else{
            printf("%d, %d\n", tmp->c, tmp->l);
        }
        tmp = tmp->next;
    }
    head->next = NULL;
    tmp = head;
    while(tmp != NULL){
        if(tmp->next == NULL){
            printf("%d, %d\n", tmp->c, tmp->l);
        }
        else{
            printf("%d, %d\n", tmp->c, tmp->l);
        }
        tmp = tmp->next;
    }
    /*
    char **class_flower =(char **) malloc(sizeof (char *)*150);
    for (int i = 0; i <  150; i ++){
        // A chaque indice ligne on alloue colonnes
        class_flower[i] = (char * ) malloc(sizeof(char) * 256);
    }
    int i = 0;





    double a [10] = {1,2,3,4,5,6,7,8,9,10};
    double b [6] = {4,5,6,7,7,7};
    double c [6] = {7,8,9,8,8,8};

    double borne_supp = max(a);
    double borne_inf = min(a);

    double *a1 = (double * ) malloc(sizeof(double) * 3);
    double *a2 = (double * ) malloc(sizeof(double) * 3);

    vec_random(borne_inf, borne_supp, a1, 3);
    vec_random(borne_inf, borne_supp, a2, 3);


    for (int i =0; i < 3; i ++){
        printf("%d : %f\n",i,a1[i]);
    }
    printf("\n");;
    for (int i =0; i < 3; i ++){
        printf("%d : %f\n",i,a1[i]);
    }

    for (int i =0; i < 3; i ++){
        printf("%d : %f\n",i,a2[i]);
    }
    printf("dist: %f",dist_eucli(a1, a2,3));

    /*
    for (int i =0; i < 10; i ++){
        printf("%d : %f\n",i,a1[i]);
    }

    for (int i =0; i < 10; i ++){
        printf("%d : %f\n",i,a2[i]);
    }

    /*
    double **fusion = malloc(sizeof (double *)*3);


    for (int i = 0; i <  3; i ++){
        // A chaque indice ligne on alloue colonnes
        fusion[i] = (double * ) malloc(sizeof(double) * 6);
    }


    fusion[0] = a;
    fusion[1] = b;
    fusion[2] = c;


    double norme = normalizebis(a, sizeof(a)/sizeof(a[0]));
    for (int i =0; i < sizeof(a)/sizeof(a[0]); i ++){
        a[i] = a[i] / norme;
        printf("%d : %f\n",i,a[i]);
    }

    double borne_supp = max(a);
    double borne_inf = min(a);
    printf("random: %f\n", randomRange(borne_inf, borne_supp));


    printf("moyenne: %f",moyenne(a));



    /*
    for (int i = 0; i <  3; i ++){

        for (int j = 0; j <  6; j ++){
        // A chaque indice ligne on alloue colonnes
            //printf("%f,  ", fusion[i][j]);
        }
        //printf("\n");
    }

    */

    return 0;
}
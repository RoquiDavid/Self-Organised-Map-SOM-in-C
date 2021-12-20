#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "function.h"



//Function use to calculate euclidian distance
double dist_eucli(double *vector1, double *vector2, int size){
    double dist = 1;
    for(int i = 0; i < size; i ++){
        dist*= (vector2[i] - vector1[i]);
    }
    return sqrt(dist);

}

//Function use to calcutate the norme of a vector and normalize him
void normalize(double *vector_data, int size){
    double sum = 0;
    
    //For each elements in the array we power him to 2 and add him to the sum
    for (int i =0; i < size; i ++){
        //printf("%f\n",array[i]);
        sum += sum + (vector_data[i]*vector_data[i]);
    }
    //Square root the sum (the norm)
    sum = sqrt(sum);
    
    //Normalize the vector
    for (int i =0; i < size; i ++){
        vector_data[i] = vector_data[i] / sum;
    }
}

//Function use to calcutate the norme and return her
double normalizebis(double *vector_data, int size){
    double sum = 0;
    
    //For each elements in the array we power him to 2 and add him to the sum
    for (int i =0; i < size; i ++){
        //printf("%f\n",array[i]);
        sum += sum + (vector_data[i]*vector_data[i]);
    }
    //Square root the sum (the norm)
    sum = sqrt(sum);
    return sum;
}


//Function that allows us to calculate the mean of an array
double moyenne (double *vector_data, int size_vec){
    double sum;
    sum = 0;

   for(int i = 0; i < size_vec; i++) {
      sum+=vector_data[i];
   }
   return sum/(double)size_vec;

}

//Function that allows us to calculate the minimum of an array
double min(double *vector_data){

    double min = INFINITY;
    for(int i = 0; i < vector_data[i]; i++){
        if(vector_data[i] < min){
            min = vector_data[i];
        }
    }
    return min;
}


//Function that allows us to calculate the maximum of an array
double max(double *vector_data)
{
    double max = 0;
    for(int i = 0; i < vector_data[i]; i++){
        if(vector_data[i] > max){
            max = vector_data[i];
        }
    }
    return max;
}

//Function that generate random double
double randomRange(double min, double max)
{
    double random_data;
    random_data = (double) rand() / ((double) RAND_MAX + 1);

    //printf("min: %f\n",min);
    return (min + random_data * (max - min));

}

//Function tht generate random vector
void vec_random(double moyenne, double *weight, int size)
{
    double min = moyenne -0.15;
    double max = moyenne + 0.15;
    double *vec_tmp;
    for (int i = 0; i < size; i++){
        weight[i] = randomRange(min, max);
    }

}


//Function that swap two array index
void swap(vec *index1, vec *index2){
    struct vec temp;
    temp = *index1;
    *index1 = *index2;
    *index2 = temp;
}


//Fonction that allow to spread the vector thought the nearest neightbors
void spread(net reseau, int col, int ligne, int max_col, int max_ligne, double *data, int data_size)
{

    int cpt = 0;
    int perim = 1;
    int limit = 3;
    int nb_ite = round(reseau.taille_voisinnage/4);
    int ite = 0;
    while (cpt < reseau.taille_voisinnage || ite != nb_ite)
    {
        // TOP
        for (int i = col + 1 * perim; i >= col - 1 * perim; i--)
        {
            if(i<0 || i>=max_col || ligne - 1 * perim <0){
                //printf("ok2: %d", i);
                continue;
            }
            if (cpt >= reseau.taille_voisinnage)
            {   
                break;
            }
            for(int j = 0; j < data_size; j++){
                reseau.map[col][ligne].weight[j] * reseau.alpha * abs((reseau.map[col][ligne].weight[j] - data[j]));
            }

            cpt++;
        }

         // LEFT
        for (int i = ligne - 1 * perim+1 ; i <= ligne + 1 * perim; i++)
        {
            if(i<0 || i>=max_ligne || col - 1 * perim < 0){
                //printf("ok3");
                continue;
            }
            if (cpt >= reseau.taille_voisinnage)
            {
                break;
            }

            for(int j = 0; j < data_size; j++){
                reseau.map[col][ligne].weight[j] * reseau.alpha * abs((reseau.map[col][ligne].weight[j] - data[j]));
            }

            cpt++;
        }
        // BOT
        for (int i = col - 1 * perim + 1; i <= col + 1 * perim; i++)
        {
            if(i<0 || i>=max_col || ligne + 1 * perim >= max_ligne){
                //printf("ok4");
                continue;
            }
            if (cpt >= reseau.taille_voisinnage)
            {
                break;
            }
            
            for(int j = 0; j < data_size; j++){
                reseau.map[col][ligne].weight[j] * reseau.alpha * abs((reseau.map[col][ligne].weight[j] - data[j]));
            }
            cpt++;
        }

        //RIGHT
        for (int i = ligne + 1 * perim - 1; i >= ligne - 1 * perim; i--)
        {
            if(i<0 || i>=max_ligne || col + 1 * perim >= max_col){
                //printf("ok5");
                continue;
            }
            if (cpt >= reseau.taille_voisinnage)
            {
                break;
            }

            for(int j = 0; j < data_size; j++){
                reseau.map[col][ligne].weight[j] * reseau.alpha * abs((reseau.map[col][ligne].weight[j] - data[j]));
            }
            cpt++;
        }
        ite++;
        //printf("ite: %d nb_ite: %d", ite, nb_ite);
        perim++;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "net.h"

#include "data_manager.h"
//Function use to calculate euclidian distance
double dist_eucli(double *vector1, double *vector2, int size);

//Function use to calcutate the norme of a vector
void normalize(double *array, int size);

//Function use to calcutate the norme and return her
double normalizebis(double *array, int size);

//Function that allows us to calculate the mean of an array
double moyenne (double *vector_data, int size_vec);

//Function that allows us to calculate the minimum of an array
double min(double *vector_data);

//Function that allows us to calculate the maximum of an array
double max(double *vector_data);

//Function tht generate random vector
void vec_random(double moyenne, double *weight, int size);

//Function that swap two array index
void swap(vec *index1, vec *index2);

//Function that generate random double
double randomRange(double min, double max);

//Fonction that allow to spread the vector thought the nearest neightbors
void spread(net reseau, int col, int ligne, int max_col, int max_ligne, double *data, int data_size);

//Function that allow to find the number of occurence of a string
//in an array
char *find_frequency(char **string_array, char **string_to_find, int size_string_array, int size_string_to_find);


//Function use to calculate euclidian distance of single number
double dist_eucli_single(double number1, double number2);


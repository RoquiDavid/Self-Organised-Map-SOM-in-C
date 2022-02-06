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
void vec_random(double *moyenne, double *weight, int size);

//Function that swap two array index
void swap(int *array_index, int size_array);

//Function that generate random double
double randomRange(double min, double max);

//Fonction that allow to spread the vector thought the nearest neightbors
void spread(net *reseau, int bmu_col, int bmu_ligne, double *data, int data_size);

//Function that allow to find the number of occurence of a string
//in an array
char *find_frequency(char **string_array, char **string_to_find, int size_string_array, int size_string_to_find);

//Function use to calculate euclidian distance of single number
double dist_eucli_single(double number1, double number2);

//Function to check memory allocation
int malloc_check_dvec(double *array);

//Function to check memory allocation of a 2D double array
int malloc_check_dmatrix(double **array);

//Function to initialize the network
int init_net(net *SOM, int nb_iteration, int nb_line_data, double *moyenne_data,int vec_size, int zoom, double learning_rate);

//Function to train the network
void net_training(net *reseau, int nb_iteration, vec *matrix_data, int nb_line_data, int vec_size);

//Function to test the network
void test_net(net *reseau, vec* data, char **flower_label, int nb_data_line, int vec_size);
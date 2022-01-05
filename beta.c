#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//Size of the data vector
#define SIZE 4

void init_index_array(int *array_index,int size_array)
{
    for(int i = 0; i < size_array; i++){
        array_index[i] = i;
    }

}

void swap(int *array_index, int size_array){
    int rnd_index;
    int temp;
    for(int i = 0; i < size_array; i++){
        rnd_index = rand() % size_array;
        temp = array_index[i];
        array_index[i] = array_index[rnd_index];
        array_index[rnd_index] = temp;
    }
    
}

int main (int argc, char *argv[], char *env[]){

    int *test = (int *)calloc(150,sizeof(int));
    init_index_array(test, 150);
    
    for(int i = 0; i < 150; i++){
        printf("%d \n",test[i]);
    }

    swap(test,150);

    for(int i = 0; i < 150; i++){
        printf("%d \n",test[i]);
    }

return 0;
}

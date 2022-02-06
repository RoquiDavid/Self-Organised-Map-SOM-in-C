#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "function.h"
#include <unistd.h>
#include <GL/glut.h>
#include <time.h>

//Function use to calculate euclidian distance of a vectors
double dist_eucli(double *vector1, double *vector2, int size){
    double dist = 0;
    for(int i = 0; i < size; i ++){
        dist+= pow((vector2[i] - vector1[i]),2);
    }
    return sqrt(dist);

}
//Function use to calculate euclidian distance of single number
double dist_eucli_single(double number1, double number2){
    double dist = pow((number1 - number1),2);
    return sqrt(dist);

}

//Function use to calcutate the norme of a vector and normalize him
void normalize(double *vector_data, int size){
    //Normalize the vector
    for (int i =0; i < size; i ++){
        vector_data[i] = vector_data[i] / normalizebis(vector_data,size);
    }
}

//Function use to calcutate the norme and return her
double normalizebis(double *vector_data, int size){
    double sum = 0;
    //For each elements in the array we power him to 2 and add him to the sum
    for (int i =0; i < size; i ++){
        sum = sum + pow(vector_data[i],2);
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
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);

}

//Function tht generate random vector
void vec_random(double *moyenne, double *weight, int size)
{
    for (int i = 0; i < size; i++){
        weight[i] = randomRange(abs(moyenne[i]-0.02), (moyenne[i]+0.06));
        //printf("%lf ", weight[i]);
    }
    //printf("\n");

}

//Function to initialize array index
void init_index_array(int *array_index,int size_array)
{
    for(int i = 0; i < size_array; i++){
        array_index[i] = i;
    }

}

//Functino to swap array index
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


double difference(double *vector1, double *vector2, int size){
    int diff = 0;
    for(int i = 0; i < size; i ++){
        diff = diff + fabs(vector1[i] - vector2[i]);
    }
    return diff;
}
//Fonction that allow to spread the vector thought the nearest neightbors
void spread(net *reseau, int bmu_col, int bmu_ligne, double *data, int data_size)
{
    //Initialisation des bornes inferieures et superieurs
    int born_sup_c = bmu_col;
    int born_sup_l = bmu_ligne;

    int born_inf_c = bmu_col;
    int born_inf_l = bmu_ligne;

    //On cherche les valeurs des borns inf et supp
    for(int i = 0; i< reseau->taille_voisinnage; i++){

        if(born_sup_c - 1>=0 ){
            born_sup_c--;
        }
        if(born_sup_l - 1 >= 0 ){
            born_sup_l--;
        }

        if(born_inf_c + 1 <reseau->nb_colonne ){
            born_inf_c++;
        }
        if(born_inf_l + 1 <reseau->nb_ligne){
            born_inf_l++;
        }
    }
    //On parcours le voisinnage dans le perimètres des bornes sup et inf
    for(int col = born_sup_c; col <= born_inf_c; col++){
        for(int ligne = born_sup_l; ligne <= born_inf_l; ligne++){
            for(int j = 0; j < data_size; j++){
                //On inject le vecteur
               reseau->map[col][ligne].weight[j] += reseau->alpha *  (data[j] - reseau->map[col][ligne].weight[j]);
            }
        }
    }
}

//Function that allow to find the number of occurence of a string
//in an array

char *find_frequency(char **string_array, char **string_to_find, int size_string_array, int size_string_to_find){
    int *freq = (int *)calloc(size_string_to_find,sizeof(int));


    int index_max = 0;
    
    //Compare the string with each elements array
    for(int i = 0; i < size_string_to_find; i++){

            for(int j = 0; j < size_string_array; j ++){
                if(string_array[j]!= NULL){
                    if(!strcmp(string_to_find[i],string_array[j])){
                        freq[i]+=1;
                    }
                }
                
        }
    }
    
    int max = freq[0];
    //Get the string which have the most occurence in the array
    for(int i = 0; i < size_string_to_find; i++){

        if(freq[i]>max){
            max = freq[i];
            index_max = i;
        }
    }
    
    return string_to_find[index_max];
}

//Function to check memory allocation
int malloc_check_dvec(double *array){
    if(array==NULL){
        return 0;
    }
    return 1;
}
//Function to check memory allocation of a 2D double array
int malloc_check_dmatrix(double **array){
    if(array==NULL){
        return 0;
    }
    return 1;
}


//Function that allow us to initialize the net
int init_net(net *SOM, int nb_iteration, int nb_line_data, double *moyenne_data,int vec_size, int zoom, double learning_rate){
    // We can go up 4* more we multiply less we zoom in
    SOM->nb_node = 5*sqrt(nb_line_data)*zoom;

    SOM->nb_colonne = SOM->nb_node/10;

    SOM->nb_ligne = 10;

    SOM->alpha = learning_rate;

    SOM->best_unit = (bmu *)calloc(1,sizeof(bmu));
    if(SOM->best_unit == NULL){
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    SOM->nb_iteration = nb_iteration;
    
    int voisi = 0;
    int perimetre = 1;
    while(voisi <round(0.5 * SOM->nb_node)){
        voisi += 8*perimetre;
        perimetre++;
    }
    SOM->taille_voisinnage = perimetre;
    
    SOM->map = ( node **)calloc(SOM->nb_colonne,sizeof( node *));
    if(SOM->map == NULL){
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < SOM->nb_colonne; i++)
    {
        SOM->map[i] = ( node *)calloc(SOM->nb_ligne,sizeof( node ));
        if(SOM->map[i] == NULL){
            printf("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }

    int cpt = 0;

    for(int i = 0; i < SOM->nb_colonne; i++){
        
        for(int j = 0; j < SOM->nb_ligne; j++){

            //Initialize the memory vector

            SOM->map[i][j].weight = (double *)calloc(vec_size, sizeof(double));
            if(SOM->map[i][j].weight == NULL){
                printf("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
        
        
            vec_random(moyenne_data, SOM->map[i][j].weight, vec_size);
            for(int k =0; k < vec_size; k++){
                //printf("%lf ",SOM->map[i][j].weight[k]);
            }
            //Normlize the memory vector
            normalize(SOM->map[i][j].weight,vec_size);
            
            SOM->map[i][j].act = 0;

            SOM->map[i][j].id = cpt;
            //Initialize the stats array
            SOM->map[i][j].stats = (char **)calloc(nb_line_data, sizeof(char *));
            
            if(SOM->map[i][j].stats == NULL){
                printf("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            
            cpt ++;

        }
    }
    return 1;
}



void net_training(net *reseau, int nb_iteration, vec *matrix_data, int nb_line_data, int vec_size){
    //State of the iteration
    int epoch = 0;
    //The minimum of the euclidian distance thought the net node
    double min = INFINITY;

    int linked_empty = 1;
    //Variable to record the size of the linked_list of BMU(s)
    int size_linked_list = 0;


   

    struct bmu *head = (bmu*)calloc(1,sizeof(bmu));
    if(head==NULL){
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    //We initialize the head of linked list
    head->c = 0;
    head->l = 0;
    head->next = NULL;

    int ite_reduc = nb_iteration/reseau->taille_voisinnage;
    //We iteration nb_iteration times
    //We swap the data array
    double alpha_init = reseau->alpha;
    int *array_index = (int *)calloc(nb_line_data,sizeof(int));
    init_index_array(array_index, nb_line_data);
    for(epoch = 0; epoch < nb_iteration; epoch ++){
        //Diminuer tous les phase_ite/taille_rayon_voisinnage
        swap(array_index, nb_line_data);
        reseau->alpha = alpha_init * (1-((float)epoch/(float)nb_iteration));

        if( !(epoch%ite_reduc) && (reseau->taille_voisinnage > 1)){
            reseau->taille_voisinnage--;
        }
        // For each data line we calculate the euclidian distance tought all the net node
        for( int num_data_ligne = 0; num_data_ligne < nb_line_data; num_data_ligne ++){


            for(int num_col = 0; num_col < reseau->nb_colonne; num_col ++){
                
                for(int num_ligne = 0; num_ligne < reseau->nb_ligne; num_ligne ++){
                    
                    reseau->map[num_col][num_ligne].act = dist_eucli(matrix_data[array_index[num_data_ligne]].v, reseau->map[num_col][num_ligne].weight, vec_size);
                    
                    //We check if we have find the minimum of the array 
                    //And actualize the bmu
                    if(reseau->map[num_col][num_ligne].act < min )
                    {   
                        //If we find a better bmu we "reset" the linked list
                        //We free the old linked list
                        while (head != NULL) {
                            struct bmu *tmp_bmu = head;
                            head = head->next;
                            free(tmp_bmu);
                        }
                        
                        
                        

                        size_linked_list = 1;
                        head = (bmu*)calloc(1,sizeof(bmu));
                        head->c = num_col;
                        head->l = num_ligne;
                        head->next = NULL;
                        min = reseau->map[num_col][num_ligne].act;
                        linked_empty = 0;
                        continue;
                    }
                    //If we find a second bmu we add her to the linked list
                    if(reseau->map[num_col][num_ligne].act == min  && !linked_empty){

                        bmu *current_node = head;
                        bmu *new_node;
                        while ( current_node != NULL && current_node->next != NULL) {
                            current_node = current_node->next;
                        }

                        new_node = (bmu *) malloc(sizeof(bmu));
                        new_node->c = num_col;
                        new_node->l = num_ligne;
                        new_node->next= NULL;
                        current_node->next = new_node;
                        size_linked_list++;
                    }
                    

                }
            }
            
            
            if(head == NULL){
                printf("BMU linked list is empty");
            }

            //Generate a random number for the winner
            int random_winner = rand() % size_linked_list+1;
            //The counter of the winner linked list
            int cpt_current_winner = 1;
            
            bmu *current_node = head;
            srand ( time(NULL) );
            //We look for the winner for spread
            while(random_winner != cpt_current_winner){   
                current_node = current_node->next;
                cpt_current_winner++;
            }
            spread(reseau, current_node->c, current_node->l, (matrix_data[array_index[num_data_ligne]].v), vec_size);
            min = INFINITY;
        }

    }
    
}


//Function that allow us to test the network (after the training)
void test_net(net *reseau, vec* data, char **flower_label, int nb_data_line, int vec_size){
    double min = INFINITY;

    int *array_index = (int *)calloc(nb_data_line,sizeof(int));
    init_index_array(array_index, nb_data_line);

    swap(array_index, nb_data_line);

    // For each data line we calculate the euclidian distance tought all the net node
    //Mettre boucle sur num_data_ligne
        for(int num_col = 0; num_col < reseau->nb_colonne; num_col ++){
            
            
            for(int num_ligne = 0; num_ligne < reseau->nb_ligne; num_ligne ++){
                
                for( int num_data_ligne = 0; num_data_ligne < nb_data_line; num_data_ligne ++){
                    
                    if(dist_eucli(reseau->map[num_col][num_ligne].weight, data[array_index[num_data_ligne]].v, vec_size) < min){
                        reseau->map[num_col][num_ligne].stats[num_data_ligne] = data[array_index[num_data_ligne]].etiquette;
                        min = dist_eucli(reseau->map[num_col][num_ligne].weight, data[array_index[num_data_ligne]].v, vec_size);
                    }
                    
                }
                
                if(!strcmp(find_frequency(reseau->map[num_col][num_ligne].stats, flower_label, nb_data_line, 3), "Iris-versicolor")){
                        reseau->map[num_col][num_ligne].label = 'O';
                }
                if(!strcmp(find_frequency(reseau->map[num_col][num_ligne].stats, flower_label, nb_data_line, 3), "Iris-setosa")){
                        reseau->map[num_col][num_ligne].label = 'S';
                }
                if(!strcmp(find_frequency(reseau->map[num_col][num_ligne].stats, flower_label, nb_data_line, 3), "Iris-virginica")){
                        reseau->map[num_col][num_ligne].label = 'A';
                }
                
            min = INFINITY;
        }
        
    }
}



//Function to display the actual map
void display_map(net reseau, int vec_size){

    for(int i = 0; i < reseau.nb_colonne; i ++){

        for(int j = 0; j < reseau.nb_ligne; j++){

            for(int k =0; k < vec_size; k++){
                printf("%lf ",reseau.map[i][j].weight[k]);
            } 

            printf("\n");
        }
    }
    printf("\n\n\n");
}


//Function to display the final labeled map
void display_final_result(net reseau){
    //Display the final map
    for(int i = 0; i < reseau.nb_colonne; i ++){

        for(int j = 0; j < reseau.nb_ligne; j++){
            
            printf("%c",reseau.map[i][j].label);

        }
        printf("\n");
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "data_manager.h"
#include "function.c"
#include "net.h"
//Size of the data vector
#define SIZE 4
#define finale_nb_lines 150





int main (int argc, char *argv[], char *env[]){

///////////////////////////////////////////////////////////////////////////////
//                         DATA INITIALISAITON PART                          //
///////////////////////////////////////////////////////////////////////////////

    
    FILE *fp = fopen("data/iris.data","r");

    char line[256];
    int file_len = 0;
    int ret;
    size_t len = 0;
    ssize_t read;
    char ch;
    int lines;
    char chr;
    chr = getc(fp);

    while (chr != EOF)
    {
        if (chr == '\n')
        {
            lines = lines + 1;
        }
        //take next character from file.
        chr = getc(fp);
    }

    fp = fopen("data/iris.data","r");

    if (fp == NULL)
        exit(EXIT_FAILURE);



    //Vector initialisation
    double *sepal_length = calloc(lines,sizeof(double));
    double *sepal_width = calloc(lines,sizeof(double));
    double *petal_length = calloc(lines,sizeof(double));
    double *petal_width = calloc(lines,sizeof(double));
    char **class_flower =(char **) calloc(lines,sizeof(char *));

    //Initialisation of temporary vec that will handle data for an example
    double *tmp_vector = (double *)calloc(SIZE,sizeof(double));
    
    for (int i = 0; i <  lines; i ++){
        // At each line index we allocate space for a string
        class_flower[i] = (char * ) calloc(256,sizeof(char));
    }

    //Array of struc initialisation
    struct vec* matrix_data = calloc(lines,sizeof(struct vec));

    for (int i = 0; i <  lines; i ++){
        // At each line index we allocate space for a string
        matrix_data[i].v = (double * ) calloc(SIZE,sizeof(double));
    }
    char tmp [256];

    
    int i = 0;
    int k = 0;
    
    
    while (ret = fscanf(fp," %s ", line)) {

        if(ret == EOF){
            break;
        }
        
        //We parse each element from the txt file an assign them to a vector

        //NOTE: We use k index to affect value to the k index of the vec. I've tried
        //To use a temporary vec but when I used that implementation 
        //the whole mtrix_data.v field only took  the last value of 
        //temporary vec

        strcpy(tmp, strtok(line,","));
        sepal_length[i] = atof(tmp);

        matrix_data[i].v[k] = sepal_length[i];
        k++;
        strcpy(tmp, strtok( NULL, "," ));
        sepal_width[i] = atof(tmp);

        matrix_data[i].v[k] = sepal_width[i];
        k++;

        strcpy(tmp, strtok( NULL, "," ));
        petal_length[i] = atof(tmp);

        matrix_data[i].v[k] = petal_length[i];
        k++;

        strcpy(tmp, strtok( NULL, "," ));
        petal_width[i] = atof(tmp);

        matrix_data[i].v[k] = petal_width[i];
        k++;
        //Change the delimiter to "\n" for the end of the line 
        strcpy(tmp, strtok( NULL, "\n" ));
        strcpy(class_flower[i], tmp);
        

        tmp_vector[0] = sepal_length[i];
        tmp_vector[1] = sepal_width[i];
        tmp_vector[2] = petal_length[i];
        tmp_vector[3] =  petal_width[i];

        /*
        printf("before norm: \n");
        for(int b = 0; b < SIZE; b++){
            printf("%f",matrix_data[i].v[b]);
        } 
        printf("\n After normalize: \n");
        normalize(matrix_data[i].v,SIZE);
        for(int b = 0; b < SIZE; b++){
            printf("%f",matrix_data[i].v[b]);
        } 
        printf("\n");

        */
        
        matrix_data[i].norme = normalizebis(tmp_vector,sizeof(tmp_vector)/sizeof(tmp_vector[0]));
        matrix_data[i].etiquette = class_flower[i];
        //printf("%d: %s\n", i,class_flower[i]);
        
        
        //printf("%f, %f, %f, %f, %s\n", sepal_length[i], sepal_width[i], petal_length[i], petal_width[i], class_flower[i]);
        k = 0;
        i++;
    }
    
    
    fclose(fp);
    
    for(int i = 0; i< finale_nb_lines; i++){
        printf("%s\n", matrix_data[i].etiquette);
    }
    
    /*
    for( int i = 0; i < finale_nb_lines; i ++){
        for(int j = 0; j < SIZE; j ++){
            printf("%f ",matrix_data[i].v[j]);
        }
        printf("%f, %s\n", matrix_data[i].norme, matrix_data[i].etiquette);
    }
    */

    
   //Shuffle the data
   /*
    size_t q;
    for (q = 0; q < finale_nb_lines - 1; q++) 
    {
        size_t j = q + rand() / (RAND_MAX / (finale_nb_lines - q) + 1);
        vec tmp = matrix_data[j];
        matrix_data[j] = matrix_data[q];
        matrix_data[q] = tmp;
    }
    */
   
    /*
    printf("After \n\n\n");
    for( int i = 0; i < finale_nb_lines; i ++){
        for(int j = 0; j < SIZE; j ++){
            printf("%f ",matrix_data[i].v[j]);
        }
        printf("%f, %s\n", matrix_data[i].norme, matrix_data[i].etiquette);
    }
    printf("Size: %d", lines);
    /*
    printf("Size: %d", finale_nb_lines);
    for(int j = 0; j < lines; j ++){
        printf("%d: %f \n",j,sepal_length[j]);
    }
    
    printf("Size: %d", lines);
    */



///////////////////////////////////////////////////////////////////////////////
//                         NETWORK INITIALISAITON PART                       //
///////////////////////////////////////////////////////////////////////////////

//We calculate the mean of each vector for the random initialisation


normalize(petal_length,SIZE);
normalize(petal_width,SIZE);
normalize(sepal_length,SIZE);
normalize(sepal_width,SIZE);

/*
for (int k=0; k<finale_nb_lines; k++) { 
        printf("%f\n",sepal_width[k]);
}
*/
double mean = 0;
    for(int i = 0; i < finale_nb_lines; i ++){
        mean += petal_length[i];   
    }
    mean = mean/finale_nb_lines;
double moyenne_petal_length = mean;
mean = 0;

    for(int i = 0; i < finale_nb_lines; i ++){
        mean += petal_width[i];   
    }
    mean = mean/finale_nb_lines;
double moyenne_petal_width = mean;
mean = 0;

    for(int i = 0; i < finale_nb_lines; i ++){
        mean += sepal_length[i];   
    }
    mean = mean/finale_nb_lines;
double moyenne_sepal_length = mean;
mean = 0;

    for(int i = 0; i < finale_nb_lines; i ++){
        mean += sepal_width[i];   
    }
    mean = mean/finale_nb_lines;
double moyenne_sepal_width = mean;
mean = 0;


/*
double moyenne_petal_length = moyenne(petal_length, finale_nb_lines);
double moyenne_sepal_length = moyenne(sepal_length, finale_nb_lines);
double moyenne_sepal_width = moyenne(sepal_width, finale_nb_lines);
double moyenne_petal_width = moyenne(petal_width, finale_nb_lines);
*/



free(sepal_length);
free(sepal_width);
free(petal_length);
free(petal_width);


printf("moyenne_sepal_length: %f \n",moyenne_sepal_length);
printf("moyenne_sepal_width: %f \n",moyenne_sepal_width);
printf("moyenne_petal_length: %f \n",moyenne_petal_length);
printf("moyenne_petal_width: %f \n",moyenne_petal_width);


double vec_moyenne[SIZE] = {moyenne_sepal_length, moyenne_sepal_width, moyenne_petal_length, moyenne_petal_width};



//double data_moyenne = moyenne(vec_moyenne, finale_nb_lines);
  for(int i = 0; i < SIZE; i ++){
        mean += vec_moyenne[i];   
    }
    mean = mean/finale_nb_lines;
double data_moyenne = mean;
printf("moy %f fff\n",data_moyenne);
mean = 0;
struct net SOM;
// We can go up 4* more we multiply less we zoom in
SOM.nb_node = 5*sqrt(finale_nb_lines)*2;

//We assotiate the nb of col and line
SOM.nb_colonne = round(sqrt(SOM.nb_node));
SOM.nb_ligne = round(sqrt(SOM.nb_node));

SOM.best_unit = (bmu *)calloc(1,sizeof(bmu));

SOM.nb_iteration = 1;
SOM.alpha = 0.7;
SOM.taille_voisinnage = SOM.nb_node/2;


//Initialisaiton of the map
SOM.map = (struct node **)calloc(SOM.nb_colonne, sizeof(struct node *));


for(int i = 0; i < SOM.nb_ligne; i++)
{
    SOM.map[i] = (struct node *)calloc(SOM.nb_ligne, sizeof(struct node));

}


printf("nb_col: %d\n", SOM.nb_colonne);
printf("nb_ligne: %d\n", SOM.nb_ligne);

//We initialise each node of the network
int cpt = 0;




for(int i = 0; i < SOM.nb_colonne; i++){
    
    for(int j = 0; j < SOM.nb_ligne; j++){
        //printf("ok");
        
        //Initialize the memory vector
        SOM.map[i][j].weight = (double *)calloc(SIZE, sizeof(double));
        vec_random(data_moyenne, SOM.map[i][j].weight, SIZE);
        //Normlize the memory vector
        normalize(SOM.map[i][j].weight,SIZE);

        //printf("moy %f fff\n",data_moyenne);
        SOM.map[i][j].act;
        SOM.map[i][j].id = cpt;
        cpt ++;
        
    }
    
    
}



/*
for( int i = 0; i < finale_nb_lines; i ++){
    for(int j = 0; j < SIZE; j ++){
        normalize(matrix_data[i].v,SIZE);
    }
    printf("\n");
}


for( int i = 0; i < finale_nb_lines; i ++){
    for(int j = 0; j < SIZE; j ++){
        printf("%f ",matrix_data[i].v[j]);
    }
    printf("\n");
}
*/

for( int i = 0; i < SOM.nb_colonne; i ++){
    for(int j = 0; j < SOM.nb_ligne; j ++){
        for(int k = 0; k < SIZE; k++){
            printf("%f ",SOM.map[i][j].weight[k]);
            //printf("SOM[%d][%d][%d] ",i,j,k);
        }
        printf("\n");
        
    }
}


///////////////////////////////////////////////////////////////////////////////
//                          NETWORK TRAINING PART                            //
///////////////////////////////////////////////////////////////////////////////

//State of the iteration
int epoch;
//The minimum of the euclidian distance thought the net node
double min = INFINITY;

//Array of the min value
double * minimum_array = (double * )calloc(SOM.nb_node, sizeof(double));
int linked_empty = 1;


struct bmu *tmp_bmu = (bmu*)calloc(1,sizeof(bmu));
struct bmu *head = (bmu*)calloc(1,sizeof(bmu));

//We initialize the head of linked list
head->c = 0;
head->l = 0;
head->next = NULL;
//We iteration nb_iteration times
//We swap the data array

for(int i = 0; i < finale_nb_lines; i++){
    swap(matrix_data + (rand() % finale_nb_lines), matrix_data + (rand() % finale_nb_lines));
}
for(epoch = 0; epoch < SOM.nb_iteration; epoch ++){
    
    if(epoch>500){
        SOM.alpha = SOM.alpha * (1-(epoch/SOM.nb_iteration));
    }

    /*
    if(epoch>500 && epoch <502){
        SOM.taille_voisinnage = 0.20 * SOM.taille_voisinnage;
    }
    
    
    if(epoch>1000 && epoch < 1500){
        SOM.alpha = SOM.alpha * (1-(epoch/SOM.nb_iteration));
        SOM.taille_voisinnage = 0.20 * SOM.taille_voisinnage;
    }

    if(epoch>1500 && epoch < 2000){
        SOM.alpha = SOM.alpha * (1-(epoch/SOM.nb_iteration));
        SOM.taille_voisinnage = 0.10 * SOM.taille_voisinnage;
    }
    
    */
    
    
    // For each data line we calculate the euclidian distance tought all the net node
    for( int num_data_ligne = 0; num_data_ligne < finale_nb_lines; num_data_ligne ++){


        for(int num_col = 0; num_col < SOM.nb_colonne; num_col ++){
            
            for(int num_ligne = 0; num_ligne < SOM.nb_ligne; num_ligne ++){
                
                //SOM.map[num_col][num_ligne].act = dist_eucli(matrix_data[num_data_ligne].v, SOM.map[num_col][num_ligne].weight, SIZE);
                
                //We check if we have find the minimum of the array 
                //And actualize the bmu
                if(SOM.map[num_col][num_ligne].act < min )
                {   
                    //If we find a better bmu we "reset" the linked list
                    head->c = num_col;
                    head->l = num_ligne;
                    head->next = NULL;
                    min = SOM.map[num_col][num_ligne].act;

                    //printf("BMU1: c: %d, l: %d\n",   head->c, head->l);
                    linked_empty = 0;
                    continue;
                    //printf("BMU: c: %d, l: %d\n",   SOM.best_unit->c, SOM.best_unit->l);
                }
                //If we find a second bmu we add her to the linked list
                if(SOM.map[num_col][num_ligne].act == min  && !linked_empty){

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
                    //printf("BMU2: c: %d, l: %d\n",head->c, head->l);
                }
                

            }
        }
        
        //printf("min: %f\n", min);
        
        if(head == NULL){
            printf("BMU linked list is empty");
        }

        //Now we iteratate throught the BMU(s) and spread the data to the neightboor
        //tmp_bmu = head;
        int cpt_node = 0;
        int col_bmu;
        int line_bmu;
        bmu *current_node = head;
        while(current_node != NULL){
            //printf("BMU: c: %d, l: %d\n",   current_node->c, current_node->l);
            //printf("ok");
            //We spread until reach 50% of the total node
            //TODO:
            //  Faire le bon parcours des voisins
            while(cpt_node < SOM.taille_voisinnage){
                col_bmu = current_node->c;
                line_bmu = current_node->l;
                printf("vois de: %d %d : ",current_node->c,current_node->l);
                for(int col = current_node->c; col < SOM.nb_colonne; col++){
                    

                    for(int line = current_node->l; line < SOM.nb_ligne; line++){
                        //We spread the data of the bmu to his neightboor
                        //By thie formula
                        printf("%d %d\n", col, line);
                        for(int i = 0; i< SIZE; i ++){
                            //SOM.map[col][line].weight[i] = SOM.map[col][line].weight[i] * SOM.alpha * dist_eucli(matrix_data[num_data_ligne].v, SOM.map[col][line].weight, SIZE);
                            //SOM.map[col][line].weight[i] = SOM.map[col][line].weight[i] * SOM.alpha * abs((SOM.map[col][line].weight[i] - matrix_data[num_data_ligne].v[i]));
                            //printf("%f ",(double)abs((SOM.map[col][line].weight[i] - matrix_data[num_data_ligne].v[i])));
                        }
                        
                    cpt_node++;
                    }
                }    

            }
            current_node= current_node->next;
            cpt_node = 0;
        }
        min = INFINITY;
    }

}
for (int k=0; k<3; k++) { 
        for (int m=0; m<3; m++) { 
            printf("ok");
        }
    }
/*

///////////////////////////////////////////////////////////////////////////////
//                            NETWORK TESTING PART                           //
///////////////////////////////////////////////////////////////////////////////
    
for(int i = 0; i < finale_nb_lines; i++){
        swap(matrix_data + (rand() % finale_nb_lines), matrix_data + (rand() % finale_nb_lines));
    }

    // For each data line we calculate the euclidian distance tought all the net node
    


    for(int num_col = 0; num_col < SOM.nb_colonne; num_col ++){
        
        for(int num_ligne = 0; num_ligne < SOM.nb_ligne; num_ligne ++){
            
            for( int num_data_ligne = 0; num_data_ligne < finale_nb_lines; num_data_ligne ++){

                if(dist_eucli(matrix_data[num_data_ligne].v, SOM.map[num_col][num_ligne].weight, SIZE) < min){

                    if(!strcmp(matrix_data[num_data_ligne].etiquette, "Iris-setosa")){
                        SOM.map[num_col][num_ligne].label = 'S';
                    }
                    if(!strcmp(matrix_data[num_data_ligne].etiquette, "Iris-virginica")){
                        SOM.map[num_col][num_ligne].label = 'A';
                    }
                    if(!strcmp(matrix_data[num_data_ligne].etiquette, "Iris-versicolor")){
                        SOM.map[num_col][num_ligne].label = 'O';
                    }
                    
                    min = SOM.map[num_col][num_ligne].act;
                }
                min = INFINITY;
            }
        }
    }
    //printf("min: %f\n", min);
    
    if(head == NULL){
        printf("BMU linked list is empty");
    }
    /*
        //Now we iteratate throught the BMU(s) and spread the data to the neightboor
        //tmp_bmu = head;
        int cpt_node = 0;
        while(SOM.best_unit != NULL){
            //printf("BMU: c: %d, l: %d\n",   SOM.best_unit->c, SOM.best_unit->l);
            
            if(!strcmp(matrix_data[num_data_ligne].etiquette, "Iris-virginica")){
                SOM.map[SOM.best_unit->c][SOM.best_unit->l].label = 'A';
            }
            if(!strcmp(matrix_data[num_data_ligne].etiquette, "Iris-versicolor")){
                SOM.map[SOM.best_unit->c][SOM.best_unit->l].label = 'O';
            }
            if(!strcmp(matrix_data[num_data_ligne].etiquette, "Iris-setosa")){
                SOM.map[SOM.best_unit->c][SOM.best_unit->l].label = 'S';
            }
            
            SOM.best_unit = SOM.best_unit->next;
        }*/
        
    



/*
for(int i = 0; i < SOM.nb_colonne; i ++){

    for(int j = 0; j < SOM.nb_ligne; j++){
        
        printf("%c",SOM.map[i][j].label);

    }
    printf("\n");

}*/


    

    
/*

for(int i = 0; i < SIZE; i++){
    printf("%f\n",SOM.map[0][0].weight[i]);
}




    //double **matrix_data = calloc(4,sizeof (double *));
    //TODO:
    // Shuffle les indices
    /*
    for (int i = 0; i <  4; i ++){
        // A chaque indice ligne on alloue colonnes
        matrix_data[i] = (double * ) calloc(lines,sizeof(double));
    }
    
    matrix_data[0] = sepal_length;
    matrix_data[1] = sepal_width;
    matrix_data[2] = petal_length;
    matrix_data[3] = petal_width;

    for (int i = 0; i <  lines; i ++){

        for (int j = 0; j <  4; j ++){
        // A chaque indice ligne on alloue colonnes
            //printf("%f, ", matrix_data[j][i]);
        }
        //printf("\n");
    }





    for (int x = 0; x< lines; x++){
            //printf("%d: %s\n", x,class_flower[x]);
        }
    for (int i = 0; i< lines; i++){
        //printf("%f, %f, %f, %f\n", sepal_length[i], sepal_width[i], petal_length[i], petal_width[i]);
        
        
    }
    */
    
    return 0;
}
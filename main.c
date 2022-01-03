#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "function.c"

//Size of the data vector
#define SIZE 4

//Global definition of variablesfor opengl
//mydisplay function
struct net SOM;
int x = 50, y = 50;
int isBlack = 1;


//red square rendering 
void redbox(int x, int y)
{
    glColor3f(1.0,0.0,0.0);
    //OpenGl quadrilatère
	glBegin(GL_QUADS);
    //Set up the "arretes" of the box
	glVertex2i(x, y);
	glVertex2i(x, y + 50);
	glVertex2i(x + 50, y + 50);
	glVertex2i(x + 50, y);
	glEnd();
}

//red square rendering 
void bluebox(int x, int y)
{

    glColor3f(0.0,0.0,1.0);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x, y + 50);
	glVertex2i(x + 50, y + 50);
	glVertex2i(x + 50, y);
	glEnd();
}

//red square rendering 
void greenBox(int x, int y)
{

    glColor3f(0.0,1.0,0.0);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x, y + 50);
	glVertex2i(x + 50, y + 50);
	glVertex2i(x + 50, y);
	glEnd();
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);

    //We check for label corresponding color
	for (int i = 0; i < SOM.nb_colonne; i++)
	{
		
		for (int j = 0; j < SOM.nb_ligne; j++)
		{
			if (SOM.map[i][j].label == 'S')
			{
				bluebox(x, y);
			}
			if (SOM.map[i][j].label == 'A')
			{
				greenBox(x, y);
			}
            if (SOM.map[i][j].label == 'O')
			{
				redbox(x, y);
			}
			x += 50;
		}
		y += 50;
		x = 50;
	}

	bluebox(100, 100);
	greenBox(150, 100);
    redbox(200, 100);
	glFlush();
}


void myInit(void)
{
    //Specify clear values for the color buffers
	glClearColor(1.0, 1.0, 1.0, 0.0);
    //Specify the type of color definition
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
    //Define the current state of the matrix
	glMatrixMode(GL_PROJECTION);
    //Replace the current matrix with the identity matrix
	glLoadIdentity();
    //define a 2D orthographic projection matrix
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main (int argc, char *argv[], char *env[]){

///////////////////////////////////////////////////////////////////////////////
//                         DATA INITIALISAITON PART                          //
///////////////////////////////////////////////////////////////////////////////

    
    FILE *fp = fopen("data/iris.data","r");

    char line[256];
    int ret;
    int lines = 0;
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

    printf("l: %d\n",lines);
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
    

    //Check the memory allocation

    if(!malloc_check_dvec(sepal_length)){
        printf("Memory allocation failed1");
        return 0;
    }

    if(!malloc_check_dvec(sepal_width)){
        printf("Memory allocation failed2");
        return 0;
    }

    if(!malloc_check_dvec(petal_length)){
        printf("Memory allocation failed3");
        return 0;
    }

    if(!malloc_check_dvec(petal_width)){
        printf("Memory allocation failed4");
        return 0;
    }

    if(class_flower == NULL){
        printf("Memory allocation failed5");
        return 0;
    }

    if(!malloc_check_dvec(tmp_vector)){
        printf("Memory allocation failed6");
        return 0;
    }

    


    for (int i = 0; i <  lines; i ++){
        // At each line index we allocate space for a string
        class_flower[i] = (char * ) calloc(256,sizeof(char));
        if(class_flower[i] == NULL){
            printf("Memory allocation failed");
            return 0;
        }
    }

    //Array of struc initialisation
    struct vec* matrix_data = calloc(lines,sizeof(struct vec));

    for (int i = 0; i <  lines; i ++){
        // At each line index we allocate space for a string
        matrix_data[i].v = (double * ) calloc(SIZE,sizeof(double));
        if(!malloc_check_dvec (matrix_data[i].v)){
            printf("Memory allocation failed");
            return 0;
        }
    }
    char tmp [256];

    
    int indice = 0;
    int k_pos = 0;
    
    
    while ((ret) = fscanf(fp," %s ", line)) {

        if(ret == EOF){
            break;
        }
        
        //We parse each element from the txt file an assign them to a vector

        //NOTE: We use k index to affect value to the k index of the vec. I've tried
        //To use a temporary vec but when I used that implementation 
        //the whole mtrix_data.v field only took  the last value of 
        //temporary vec

        strcpy(tmp, strtok(line,","));
        sepal_length[indice] = atof(tmp);

        matrix_data[indice].v[k_pos] = sepal_length[indice];
        k_pos++;
        strcpy(tmp, strtok( NULL, "," ));
        sepal_width[indice] = atof(tmp);

        matrix_data[indice].v[k_pos] = sepal_width[indice];
        k_pos++;

        strcpy(tmp, strtok( NULL, "," ));
        petal_length[indice] = atof(tmp);

        matrix_data[indice].v[k_pos] = petal_length[indice];
        k_pos++;

        strcpy(tmp, strtok( NULL, "," ));
        petal_width[indice] = atof(tmp);

        matrix_data[indice].v[k_pos] = petal_width[indice];
        k_pos++;
        //Change the delimiter to "\n" for the end of the line 
        strcpy(tmp, strtok( NULL, "\n" ));
        strcpy(class_flower[indice], tmp);
        

        tmp_vector[0] = sepal_length[indice];
        tmp_vector[1] = sepal_width[indice];
        tmp_vector[2] = petal_length[indice];
        tmp_vector[3] =  petal_width[indice];
        
        matrix_data[indice].norme = normalizebis(tmp_vector,sizeof(tmp_vector)/sizeof(tmp_vector[0]));
        matrix_data[indice].etiquette = class_flower[indice];

        k_pos = 0;
        indice++;
    }
    
    
    fclose(fp);

//Normalize data
for( int i = 0; i < lines; i ++){
    normalize(matrix_data[i].v,SIZE);
    
}


///////////////////////////////////////////////////////////////////////////////
//                         NETWORK INITIALISAITON PART                       //
///////////////////////////////////////////////////////////////////////////////

normalize(petal_length,lines);
normalize(sepal_length,lines);
normalize(sepal_width,lines);
normalize(petal_width,lines);

double moyenne_petal_length = moyenne(petal_length, lines);
double moyenne_sepal_length = moyenne(sepal_length, lines);
double moyenne_sepal_width = moyenne(sepal_width, lines);
double moyenne_petal_width = moyenne(petal_width, lines);



free(sepal_length);
free(sepal_width);
free(petal_length);
free(petal_width);


printf("moyenne_sepal_length: %f \n",moyenne_sepal_length);
printf("moyenne_sepal_width: %f \n",moyenne_sepal_width);
printf("moyenne_petal_length: %f \n",moyenne_petal_length);
printf("moyenne_petal_width: %f \n",moyenne_petal_width);

//Mean vector
double *vec_moyenne = (double *)calloc(SIZE,sizeof(double));
vec_moyenne[0] = moyenne_sepal_length;
vec_moyenne[1] = moyenne_petal_width;
vec_moyenne[2] = moyenne_petal_length;
vec_moyenne[3] = moyenne_sepal_width;



//We initialise each node of the network
init_net(&SOM, 6, 10, 2000, lines, vec_moyenne, SIZE,1, 0.9);


printf("\n Après initialisation: \n");
display_map(SOM,SIZE);


///////////////////////////////////////////////////////////////////////////////
//                          NETWORK TRAINING PART                            //
///////////////////////////////////////////////////////////////////////////////


//Memory allocation for the linked lists of the bmus
struct bmu *tmp_bmu = (bmu*)calloc(1,sizeof(bmu));
if(tmp_bmu==NULL){
    printf("Memory allocation failed");
    return 0;
}

struct bmu *head = (bmu*)calloc(1,sizeof(bmu));
if(head==NULL){
    printf("Memory allocation failed");
    return 0;
}

//Call the training function of the map
net_training(&SOM, tmp_bmu, head, matrix_data, lines, SIZE);

printf("\n Après training: \n");
display_map(SOM,SIZE);

///////////////////////////////////////////////////////////////////////////////
//                            NETWORK TESTING PART                           //
///////////////////////////////////////////////////////////////////////////////

//Array initialization ofr string to find
char **unique_flower = (char **)calloc(3,sizeof(char *));
unique_flower[0]= "Iris-versicolor";
unique_flower[1]= "Iris-virginica";
unique_flower[2]= "Iris-setosa";

//Test the network to produce the final result
test_net(&SOM, matrix_data, unique_flower, lines, SIZE);

//Display the final net
display_final_result(SOM);


//Initialize glut library
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//Size of the window
glutInitWindowSize(800, 600);
//Position of the window
glutInitWindowPosition(100, 150);
//Create the glut window title
glutCreateWindow("Graphical render of self-organised map(SOM)");
//Call the display opengl function
glutDisplayFunc(myDisplay);
//Call the initialisation function
myInit();
//Call the glut "routine" loop
glutMainLoop();




//Free the memory
free(matrix_data);
free(head);
free(tmp_bmu);
free(vec_moyenne);
free(unique_flower);

return 0;
}

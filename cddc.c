#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------ VARIABLES ---------------------------------------------------------------------//
#define WIDTH 680
#define HEIGHT 680
#define FPS 60
#define GRAVITY 0.5
#define POPULAÇÃO 10
#define NUMBER_ELITES 40
#define MUTATION 0.05


bool COLISSION_UP = false; 
bool COLISSION_DOWN = false;

bool NEXT_POPULATION = false;

int PIPE_GAP = 180; //INPUT 1
int DEADS = 0;

//------------------------------------------------------------------------- STRUCTS -------------------------------------------------------------------------//

struct PIPES {

    float PIPE_X_AXIS;
    int HEIGHT_PIPEUP;
    int HEIGHT_PIPEDOWN;

};


typedef struct {

    double GENES [26]; //3 INPUTS * 5 NEURONS HIDDEN LAYER = 15 + 5 BIAS = 20. 20 + 5 WEIGHTS + 1 FINAL BIAS = 26
    double FITNESS;
    double STORED_FITNESS;

    bool ALIVE;

    double INITIAL_POSITION_X;
    double INITIAL_POSITION_Y; //INPUT 2
    double VELOCITY_Y; //INPUT 3


    //nfgnfgndfn
    double HIDDEN_NEURONS [5];
    double RELU_HIDDEN_NEURONS [5];
    double OUTPUT;

 
} INDIVIDUAL;


//------------------------------------------------------------------------ COMPARE FUNCTION -------------------------------------------------------------------------

int COMPARAR_FITNESS (const void *a, const void *b) {
    
	INDIVIDUAL *ind1 = (INDIVIDUAL *)a;
   	INDIVIDUAL *ind2 = (INDIVIDUAL *)b;

    
    	if (ind1 -> STORED_FITNESS < ind2 -> STORED_FITNESS) return 1;
    	if (ind1 -> STORED_FITNESS > ind2 -> STORED_FITNESS) return -1;
    	return 0;
}


//------------------------------------------------------------------------- ACTIVATION FUNCTIONS --------------------------------------------------------------------//


double SIGMOID_ACTIVATION_FUNCTION (double x) {

    return 1.0 / (1.0 + exp(-x));
}


double RELU_ACTIVATION_FUNCTION (double x) {

    if (x < 0) {

        return 0;                
    }

    return x;
}


//------------------------------------------------------------------------- INITIAL POPULATION ------------------------------------------------------------//


void FIRST_RANDOM_POPULATION (INDIVIDUAL x []) { //SE PASSAR SEM SER APONTADOR, PASSA APENAS UMA CÓPIA, PODE GERAR PROBLEMAS DE MEMÓRIA E SOBREPOSIÇÃO


    for (int i = 0; i < POPULAÇÃO; i++) {
        for (int j = 0; j < ((3 * 5) + 5 + 5); j++) {

            x[i].GENES[j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        }
            x[i].GENES[25] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    
            
            
            x[i].FITNESS = 0;
            x[i].STORED_FITNESS = 0;
            x[i].ALIVE = true;

            x[i].INITIAL_POSITION_X = 150;
            x[i].INITIAL_POSITION_Y = ((double)rand() / RAND_MAX) * HEIGHT;
            x[i].VELOCITY_Y = 0.5;
    }
}


//------------------------------------------------------------------------- IMPLEMENTATION NEURAL NETWORK ------------------------------------------------------------//


double NEURAL_NETWORK_GENETIC_ALGORITHM (INDIVIDUAL x [], double INPUT1, double INPUT2, double INPUT3) {

        
    for (int i = 0; i < POPULAÇÃO; i++) {

    int index = 0;
        
        for (int k = 0; k < 5; k++) {
           
            x[i].HIDDEN_NEURONS[k] = INPUT1 * x[i].GENES[index++] +
                                     INPUT2 * x[i].GENES[index++] +
                                     INPUT3 * x[i].GENES[index++];
                                                
                                     
            x[i].HIDDEN_NEURONS[k] += x[i].GENES[index++];
                        
            }

               
        for (int j = 0; j < 5; j++) {
            
            x[i].RELU_HIDDEN_NEURONS[j] = RELU_ACTIVATION_FUNCTION (x[i].HIDDEN_NEURONS[j]);
        
            }
        

        x[i].OUTPUT = 0;
        for (int z = 0; z < 5; z++) {

            x[i].OUTPUT += x[i].RELU_HIDDEN_NEURONS[z] * x[i].GENES[index++];
        }

        x[i].OUTPUT += x[i].GENES[25];

        x[i].OUTPUT = SIGMOID_ACTIVATION_FUNCTION(x[i].OUTPUT);

    } 
                
}

//------------------------------------------------------------------------- NEW_GEN ----------------------------------------------------------------------------------//


void FILHOS (INDIVIDUAL *PAI1, INDIVIDUAL *PAI2, INDIVIDUAL *FILHO, int NÚMERO_GENES) { //TEM QUE SER USADO APONTADOR PARA CONSEGUIR ALTERAR ORIGINALMENTE


	for (int i = 0; i < NÚMERO_GENES; i++) {
        
        int NUM_RANDOM = (rand() % 2);
            
            if (NUM_RANDOM == 0) {
    
                FILHO -> GENES[i] = PAI1 -> GENES [i];              
        } 

            else {

                FILHO -> GENES [i] = PAI2 -> GENES[i];	
        }
    
    }


	for (int i = 0; i < NÚMERO_GENES; i++) {

		if ((rand() / (double)RAND_MAX) < MUTATION) {

			FILHO -> GENES[i] += ((double)rand() / RAND_MAX) * 0.2 - 0.1;	

		}
	}
}



void NEXT_GEN (INDIVIDUAL x [], int NUMBER_ELITES) {

    qsort (x, POPULAÇÃO, sizeof(INDIVIDUAL), COMPARAR_FITNESS);

    INDIVIDUAL new_gen [POPULAÇÃO];
    
    for (int i = 0; i < NUMBER_ELITES; i++) {

        new_gen [i] = x [i];
        
    }


    for (int i = NUMBER_ELITES; i < POPULAÇÃO; i++) {

		int PAI1 = rand() % (NUMBER_ELITES);
       
		int PAI2 = rand() % (NUMBER_ELITES);
   
		FILHOS (&new_gen[PAI1], &new_gen[PAI2], &new_gen[i], NÚMERO_DE_GENES);
	
	}
    

    for (int i = 0; i < POPULAÇÃO; i++) {

        x[i] = new_gen[i]; //REPLACEMENT DA POPULAÇÃO
        
        x[i].FITNESS = 0;
        x[i].STORED_FITNESS = 0;
        x[i].ALIVE = true;

        x[i].INITIAL_POSITION_X = 150;
        x[i].INITIAL_POSITION_Y = ((double)rand() / RAND_MAX) * HEIGHT;
        x[i].VELOCITY_Y = 0.5;

    }
}



//------------------------------------------------------------------------- MAIN -------------------------------------------------------------------------------------//

double RUN (INDIVIDUAL x [], int HITBOX_BONECO_X, int HITBOX_BONECO_Y, struct PIPES colunas[], Texture2D BONECO) {
        
    

    for (int i = 0; i < POPULAÇÃO; i++) {

        if (x[i].ALIVE == false) {
           
            continue;
        
        }
   

        x[i].FITNESS ++;

        x[i].VELOCITY_Y += GRAVITY;
        x[i].INITIAL_POSITION_Y += x[i].VELOCITY_Y;


        




        Rectangle BONECOHITBOX = {
                                x[i].INITIAL_POSITION_X + (BONECO.width * 0.6 - HITBOX_BONECO_X) / 2,
                                x[i].INITIAL_POSITION_Y + (BONECO.height * 0.55 - HITBOX_BONECO_Y) / 2,
                                HITBOX_BONECO_X,
                                HITBOX_BONECO_Y
                        };

        
    
        for (int j = 0; j < 50; j++) {


            Rectangle PIPECIMA = {colunas[j].pipe_x, 0, 90, colunas[j].altura_pipeteto};
            Rectangle PIPEBAIXO = {colunas[j].pipe_x + 2, (HEIGHT - colunas[j].altura_pipechão), 90, colunas[j].altura_pipechão};



            COLLISION_UP = CheckCollisionRecs (BONECOHITBOX, PIPECIMA);
            COLLISION_DOWN = CheckCollisionRecs (BONECOHITBOX, PIPEBAIXO);


            if (COLLISION_UP == true || COLLISION_DOWN == true) {

			    x[i].ALIVE = false;
                x[i].STORED_FITNESS = x[i].FITNESS;
                DEAD += 1;

           }


        if (x[i].INITIAL_POSITION_Y > (HEIGHT - 50) || x[i].INITIAL_POSITION_Y <= 0) {

            x[i].ALIVE = false;
            x[i].STORED_FITNESS = x[i].FITNESS;

    }


        output = REDE (x[i].INITIAL_POSITION_Y / (double) HEIGHT,
                       PIPE_GAP / (double) HEIGHT,
                       (double) indivíduos[i].MOV_Y / (double) HEIGHT,
                       (double) (indivíduos[i].CENTRO_COORDENADA_PIPE - indivíduos[i].POS_INICIAL_Y) / (double) HEIGHT,
                        indivíduos[i].genes);

        
        //bool deseja_saltar = (output > 0.5f);


        //if (deseja_saltar && indivíduos[i].MOV_Y >= -0.1f) { 

          if (output > 0) {
            indivíduos[i].MOV_Y = -8.8f;
            }

        }


}




int main () {

    srand(time(NULL));

    InitWindow(WIDTH, HEIGHT, "NeuroFlap");
	SetTargetFPS(FPS);

	Texture2D BONECO = LoadTexture("Background/flappybird2.png");


	struct PIPES colunas [50];
	float pipe_x = 640; //POSIçÃO INICIAL DO PRIMEIRO DUO DE PIPES
	
    for (int i = 0; i < 50; i++) {
	
		int pipe_cima_max = HEIGHT - GAP_PIPE - 50;

		int height1 = rand() % (pipe_cima_max - 50) + 50;

		int height2 = HEIGHT - height1 - GAP_PIPE; 


		int altura_pipeteto = height1;
		int altura_pipechão = height2;
		

		colunas[i].pipe_x = pipe_x;
		colunas[i].altura_pipeteto = altura_pipeteto;
		colunas[i].altura_pipechão = altura_pipechão;
		

		pipe_x += 300; //CRIA DUOS DE PIPES DE 200 EM 200
	}

	
	int HITBOX_BONECO_X = BONECO.width * 0.5 * 0.75; //LARGURA * ESCALA * METAD
	int HITBOX_BONECO_Y = BONECO.height * 0.5 * 0.71;


    INDIVIDUAL x [POPULAÇÃO];

    FIRST_RANDOM_POPULATION (x);

    
    
    return 0;
}





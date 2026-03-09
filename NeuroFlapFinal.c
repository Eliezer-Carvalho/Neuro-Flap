#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//--------------------------------------------------------------------------------- VARIÁVEIS ---------------------------------------------------------------------------


#define LARGURA 680
#define ALTURA 680 
#define FPS 60 
#define GRAVIDADE 0.5 
#define POPULAÇÃO 250 
#define ELITES 25 
#define TAXA_DE_MUTAÇÃO 0.05 
#define NÚMERO_TUBOS 75
#define NÚMERO_GENES 26

bool COLISÃO_CIMA = false;
bool COLISÃO_BAIXO = false;
bool NEXT_POPULATION = false;

int TUBO_GAP = 180; //INPUT 1
int MORTES = 0;


//--------------------------------------------------------------------------------- STRUCTS -----------------------------------------------------------------------------


struct TUBOS {
    
    float POS_EIXO_X;
    int ALTURA_TUBO_CIMA;
    int ALTURA_TUBO_BAIXO;
   
};


typedef struct {
    
    double GENES [NÚMERO_GENES]; 
    
    double FITNESS; 
    double STORED_FITNESS; 

    bool VIVO; 

    
    double POS_INICIAL_X; 
    double POS_INICIAL_Y;
    double VELOCIDADE_Y;

} PESSOA;



//------------------------------------------------------------------------ FUNCTIONS -------------------------------------------------------------------------


int COMPARAR_FITNESS (const void *a, const void *b);

double FUNÇÃO_ATIVAÇÃO_SIGMOID (double x);
double FUNÇÃO_ATIVAÇÃO_ReLU (double x);
    
void GERAÇÃO_0 (PESSOA x []);

double MULTILAYER_PERCEPTRON (PESSOA x [], double INPUT1, double INPUT2, double INPUT3);

void NEXT_GERAÇÕES (PESSOA x [], int ELITES);
void FILHOS_NEXT_GERAÇÕES (PESSOA *PAI1, PESSOA *PAI2, PESSOA *FILHO, int NÚMERO_GENES);

void MAIN_LOOP (PESSOA x [], int HITBOX_BONECO_X, int HITBOX_BONECO_Y, struct TUBOS colunas[], Texture2D Flappy)



//------------------------------------------------------------------------ MAIN -----------------------------------------------------------------------------------------

void main () {

    srand(time(NULL));

    InitWindow (LARGURA, ALTURA, "Neuro Flap");
    SetTargetFPS (FPS);

    Texture2D Flappy = LoadTexture("Background/flappybird2.png");

    
    struct TUBOS colunas [NÚMERO_TUBOS];
    float POS_INICIAL_X_PRIMEIRO_PIPE = 680;


    for (int i = 0; i < NÚMERO_TUBOS; i++) {
	
        int ALTURA_MAX_TUBO_CIMA = ALTURA - TUBO_GAP - 50;
        int ALTURA_TUBO_CIMA = rand() % (ALTURA_MAX_TUBO_CIMA - 50) + 50;
        int ALTURA_TUBO_BAIXO = ALTURA - ALTURA_TUBO_CIMA - TUBO_GAP;

       
        colunas[i].POS_EIXO_X = POS_INICIAL_X_PRIMEIRO_PIPE;
        colunas[i].ALTURA_TUBO_CIMA = ALTURA_TUBO_CIMA;
        colunas[i].ALTURA_TUBO_BAIXO = ALTURA_TUBO_BAIXO;

        colunas[i].POS_EIXO_X += 300;

	}


    int HITBOX_FLAPPY_X = Flappy.width * 0.5 * 0.75; 
	int HITBOX_FLAPPY_Y = Flappy.height * 0.5 * 0.71;


    PESSOA x [POPULAÇÃO];
    
    GERAÇÃO_O (x);


    while (!WindowShouldClose()) {






//
//
//
//
//
//
//





    }   

}


//-------------------------------------------------------------------------- fim ---------------------------------------------------------------------------------------












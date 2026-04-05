#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>


#define LARGURA 640
#define ALTURA 360
#define FPS 60
#define GRAVIDADE 0.5
#define NÚMERO_TUBOS 200
#define NÚMERO_NEURÓNIOS_CAMADA_OCULTA 5



double GENES [31] = {-0.596091, -0.923310, -0.820793, -0.368714, -0.602345, -0.039632, -0.457684, 0.295823, 0.657382, -0.281872, -0.119622, 0.426760, -0.524716, 0.544149, 0.625958, 0.016093, -0.205925, 0.677372, 0.902922, -0.471069, -0.701636, 0.944586, -0.777863, 0.119959, -0.799539, -0.642989, 0.085010, -0.901643, -0.930897, -0.200175, -0.571187};


bool COLISÃO_CIMA_REDE_NEURAL = false;
bool COLISÃO_BAIXO_REDE_NEURAL = false;

bool COLISÃO_CIMA_UTILIZADOR = false;
bool COLISÃO_BAIXO_UTILIZADOR = false;

bool GAME_MODE = true;
bool WINNER = false;

int TUBO_GAP = 180;
int SCORE = 0;
int POS_INICIAL_X_PRIMEIRO_PIPE = 640;


typedef struct {

    float POS_EIXO_X;
    int ALTURA_TUBO_CIMA;
    int ALTURA_TUBO_BAIXO;

} TUBOS;


typedef struct {

    bool VIVO; 

    double POS_INICIAL_X; 
    double POS_INICIAL_Y; //Input 2 - Representa a altura a que o Flappy encontra-se
    double VELOCIDADE_Y; //Input 1 - Representa a velocidade do Flappy no eixo dos Y

    double NEURÓNIO_HIDDEN_LAYER [NÚMERO_NEURÓNIOS_CAMADA_OCULTA];
    double OUTPUT_NEURÓNIO_HIDDEN_LAYER [NÚMERO_NEURÓNIOS_CAMADA_OCULTA];
    double OUTPUT;


    float CENTRO_COORDENADA_PIPE; //Input 4 - Representa o a coordenada do centro do próximo pipe, uma maneira diferente, em vez de dar o gap entre tubos     
    int X_TO_NEXTPIPE; //Input 3 - Representa a distância até ao próximo pipe, pipe a pipe

} REDE_NEURAL;


typedef struct {

    bool VIVO_UTI;

    double POS_INICIAL_X_UTI;
    double POS_INICIAL_Y_UTI;
    double VELOCIDADE_Y_UTI;

} UTILIZADOR;



double ACTIVATION_FUNCTION_TANH (double x);
double ACTIVATION_FUNCTION_SIGMOID (double x);

void INICIAR_VALORES (REDE_NEURAL *x, UTILIZADOR *z);

double REDE_NEURAL_AG (double INPUT1, double INPUT2, double INPUT3, double INPUT4, REDE_NEURAL *x);

void RUN_REDE_NEURAL (REDE_NEURAL *x, TUBOS y [], Texture2D Flappy);
void RUN_PLAYER1 (UTILIZADOR *z, TUBOS y [], Texture2D Flappy);



int main () {

    srand(time(NULL));

    InitWindow (LARGURA, ALTURA, "Neuro Flap");
    SetTargetFPS (FPS);
    Texture2D Flappy = LoadTexture("/home/eliezer/Neuro Flap/Imagens/flappybird2.png");    

    TUBOS colunas [NÚMERO_TUBOS];
    for (int i = 0; i < NÚMERO_TUBOS; i++) {
    
        int ALTURA_MAX_TUBO_CIMA = ALTURA - TUBO_GAP - 50;
        int ALTURA_TUBO_CIMA = rand() % (ALTURA_MAX_TUBO_CIMA - 50) + 50;
        int ALTURA_TUBO_BAIXO = ALTURA - ALTURA_TUBO_CIMA - TUBO_GAP;

        colunas[i].POS_EIXO_X = POS_INICIAL_X_PRIMEIRO_PIPE;
        colunas[i].ALTURA_TUBO_CIMA = ALTURA_TUBO_CIMA;
        colunas[i].ALTURA_TUBO_BAIXO = ALTURA_TUBO_BAIXO;

        POS_INICIAL_X_PRIMEIRO_PIPE += 280;
    }   


    REDE_NEURAL multilayer_perceptron_ag;
    UTILIZADOR player_1;

    INICIAR_VALORES (&multilayer_perceptron_ag, &player_1);


    while (!WindowShouldClose()) {

        if (GAME_MODE == true) {

            RUN_REDE_NEURAL (&multilayer_perceptron_ag, colunas, Flappy);
            RUN_PLAYER1 (&player_1, colunas, Flappy);

            for (int i = 0; i < NÚMERO_TUBOS; i++) {

                colunas[i].POS_EIXO_X -= 3.0;
            }

        }        
    

        BeginDrawing();

            ClearBackground(SKYBLUE);

            DrawTextureEx(Flappy, (Vector2){multilayer_perceptron_ag.POS_INICIAL_X, multilayer_perceptron_ag.POS_INICIAL_Y}, 0, 0.45, RAYWHITE);
            DrawTextureEx(Flappy, (Vector2){player_1.POS_INICIAL_X_UTI, player_1.POS_INICIAL_Y_UTI}, 0, 0.45, BLACK);
        
            for (int i = 0; i < NÚMERO_TUBOS; i++) {
                
                DrawRectangle (colunas[i].POS_EIXO_X, 0, 85, colunas[i].ALTURA_TUBO_CIMA, WHITE);
			    DrawRectangle (colunas[i].POS_EIXO_X + 2, (ALTURA - colunas[i].ALTURA_TUBO_BAIXO), 85, colunas[i].ALTURA_TUBO_BAIXO, WHITE);
            }
        
        EndDrawing();
    }

    UnloadTexture(Flappy);
    CloseWindow();

    return 0;

}



double ACTIVATION_FUNCTION_TANH (double x) {

    return tanh (x);

}


double ACTIVATION_FUNCTION_SIGMOID (double x) {

    return 1.0 / (1.0 + exp(-x));

}


void INICIAR_VALORES(REDE_NEURAL *x, UTILIZADOR *z) {
    
    x -> VIVO = true;
    x -> POS_INICIAL_X = 200;
    x -> POS_INICIAL_Y = 200;
    x -> VELOCIDADE_Y = 0;
    x -> CENTRO_COORDENADA_PIPE = 0;
    x -> X_TO_NEXTPIPE = 0;
  
    
    z -> VIVO_UTI = true;
    z -> POS_INICIAL_X_UTI = 200;
    z -> POS_INICIAL_Y_UTI = 150;
    z -> VELOCIDADE_Y_UTI = 0;

}



double REDE_NEURAL_AG (double INPUT1, double INPUT2, double INPUT3, double INPUT4, REDE_NEURAL *x) {

    int index = 0;

    for (int a = 0; a < NÚMERO_NEURÓNIOS_CAMADA_OCULTA; a++) {

        x -> NEURÓNIO_HIDDEN_LAYER [a] = INPUT1 * GENES [index++] +
                                         INPUT2 * GENES [index++] +
                                         INPUT3 * GENES [index++] +
                                         INPUT4 * GENES [index++];
        
        x -> NEURÓNIO_HIDDEN_LAYER [a] += GENES [index++];
    }


    for (int b = 0; b < NÚMERO_NEURÓNIOS_CAMADA_OCULTA; b++) {

        x -> OUTPUT_NEURÓNIO_HIDDEN_LAYER [b] = ACTIVATION_FUNCTION_TANH (x -> NEURÓNIO_HIDDEN_LAYER [b]);

    }
  
    x -> OUTPUT = 0;

    for (int c = 0; c < NÚMERO_NEURÓNIOS_CAMADA_OCULTA; c++) {

        x -> OUTPUT += x -> OUTPUT_NEURÓNIO_HIDDEN_LAYER [c] * GENES [index++];

    }
    
    x -> OUTPUT += GENES [index++];

    x -> OUTPUT = ACTIVATION_FUNCTION_SIGMOID (x -> OUTPUT);

    return x -> OUTPUT;

}


void RUN_REDE_NEURAL (REDE_NEURAL *x, TUBOS y [], Texture2D Flappy) { //Structs são passadas por valor (cópia), arrays são passados como ponteiros automaticamente.


    int NEXTPIPE = -1;
    
    x -> VELOCIDADE_Y += GRAVIDADE;
    x -> POS_INICIAL_Y += x -> VELOCIDADE_Y;

    Vector2 FLAPPYHITBOX = {
                            x -> POS_INICIAL_X + (Flappy.width * 0.45 / 2 + 10),
                            x -> POS_INICIAL_Y + (Flappy.height * 0.45 / 2)                                               
    };


    for (int i = 0; i < NÚMERO_TUBOS; i++) {


        Rectangle PIPECIMA = {y[i].POS_EIXO_X, 0, 85, y[i].ALTURA_TUBO_CIMA};
        Rectangle PIPEBAIXO = {y[i].POS_EIXO_X + 2, (ALTURA - y[i].ALTURA_TUBO_BAIXO), 85, y[i].ALTURA_TUBO_BAIXO};
        

        COLISÃO_CIMA_REDE_NEURAL = CheckCollisionCircleRec (FLAPPYHITBOX, 20, PIPECIMA);
        COLISÃO_BAIXO_REDE_NEURAL = CheckCollisionCircleRec (FLAPPYHITBOX, 20, PIPEBAIXO);

        
        if (y[i].POS_EIXO_X + 85 >= x -> POS_INICIAL_X && NEXTPIPE == -1) {
    
            NEXTPIPE = i;
        }


        if (COLISÃO_CIMA_REDE_NEURAL == true || COLISÃO_BAIXO_REDE_NEURAL == true) {

            GAME_MODE = false;                 
        }
    
        
        x -> CENTRO_COORDENADA_PIPE = y[i].ALTURA_TUBO_CIMA + (TUBO_GAP / 2.0); //À medida que os pipes avançam   
    }


    if (NEXTPIPE != -1) {

        x -> X_TO_NEXTPIPE = (y[NEXTPIPE].POS_EIXO_X + 85) - x -> POS_INICIAL_X;
        x -> CENTRO_COORDENADA_PIPE = y[NEXTPIPE].ALTURA_TUBO_CIMA + (TUBO_GAP / 2.0);
    }


    if (x -> POS_INICIAL_Y > (ALTURA - 45) || x -> POS_INICIAL_Y <= 0) {

        GAME_MODE = false;
    }

    if (NEXTPIPE == -1 && x -> VIVO == true) {
        
        WINNER = true;        
    }


    
    double DECISÃO = REDE_NEURAL_AG ((double) x -> POS_INICIAL_Y / (double) ALTURA, //Input 1 Normalizado
                       (double) x -> X_TO_NEXTPIPE / (double) LARGURA, // Input 2 Normalizado
                       (double) x -> VELOCIDADE_Y / (double) 10.0, // Input 3 Normalizado
                       ((double) x -> CENTRO_COORDENADA_PIPE - (double) x -> POS_INICIAL_Y) / (double) ALTURA, // Input 4 Normalizado 
                       x); //Ponteiro para a struct única

    if (DECISÃO > 0.5) {
        x -> VELOCIDADE_Y = -8.8f;    
    }
}



void RUN_PLAYER1 (UTILIZADOR *z, TUBOS y [], Texture2D Flappy) {

    
    int NEXTPIPE2 = -1;
  
    z -> VELOCIDADE_Y_UTI += GRAVIDADE;
    z -> POS_INICIAL_Y_UTI += z -> VELOCIDADE_Y_UTI;


    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	    
        z -> VELOCIDADE_Y_UTI = -8.8; 
	};
			

    Vector2 FLAPPYHITBOX_UTI = {
                            z -> POS_INICIAL_X_UTI + (Flappy.width * 0.45 / 2 + 10),
                            z -> POS_INICIAL_Y_UTI + (Flappy.height * 0.45 / 2)                                               
    };


    for (int i = 0; i < NÚMERO_TUBOS; i++) {

        Rectangle PIPECIMA = {y[i].POS_EIXO_X, 0, 85, y[i].ALTURA_TUBO_CIMA};
        Rectangle PIPEBAIXO = {y[i].POS_EIXO_X + 2, (ALTURA - y[i].ALTURA_TUBO_BAIXO), 85, y[i].ALTURA_TUBO_BAIXO};

        COLISÃO_CIMA_UTILIZADOR = CheckCollisionCircleRec (FLAPPYHITBOX_UTI, 20, PIPECIMA);
        COLISÃO_BAIXO_UTILIZADOR = CheckCollisionCircleRec (FLAPPYHITBOX_UTI, 20, PIPEBAIXO);

        
        if (y[i].POS_EIXO_X + 85 >= z -> POS_INICIAL_X_UTI && NEXTPIPE2 == -1) {
    
            NEXTPIPE2 = i;
            SCORE += 1;
        }


        if (COLISÃO_CIMA_UTILIZADOR == true || COLISÃO_BAIXO_UTILIZADOR == true) {

            GAME_MODE = false;                 
        }
    
    }


    if (z -> POS_INICIAL_Y_UTI > (ALTURA - 45) || z -> POS_INICIAL_Y_UTI <= 0) {

        GAME_MODE = false;
    }

    if (NEXTPIPE2 == -1 && z -> VIVO_UTI == true) {
        
        WINNER = true;        
    }
}



















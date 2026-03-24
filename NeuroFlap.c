#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//--------------------------------------------------------------------------------- VARIÁVEIS ---------------------------------------------------------------------------


#define LARGURA 1000
#define ALTURA 550
#define FPS 60 
#define GRAVIDADE 0.5 
#define POPULAÇÃO 250 
#define NUM_ELITES 25 
#define TAXA_DE_MUTAÇÃO 0.05 
#define NÚMERO_TUBOS 75
#define NÚMERO_GENES 31
#define NÚMERO_NEURÓNIOS_CAMADA_OCULTA 5

bool COLISÃO_CIMA = false;
bool COLISÃO_BAIXO = false;
bool NEXT_POPULATION = false;
bool GAME_OVER = false;


int TUBO_GAP = 180; //INPUT 1
int MORTES = 0;
int GERAÇÃO = 0;




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


    double NEURÓNIO_HIDDEN_LAYER [NÚMERO_NEURÓNIOS_CAMADA_OCULTA];
    double OUTPUT_NEURÓNIO_HIDDEN_LAYER [NÚMERO_NEURÓNIOS_CAMADA_OCULTA];
    double OUTPUT;

    float CENTRO_COORDENADA_PIPE;     
    int X_TO_NEXTPIPE;


} PESSOA;



//------------------------------------------------------------------------ FUNCTIONS -------------------------------------------------------------------------


int COMPARAÇÃO (const void *a, const void *b);


double FUNÇÃO_ATIVAÇÃO_SIGMOID (double x);
double FUNÇÃO_ATIVAÇÃO_ReLU (double x);

void RESET_JOGO (struct TUBOS colunas []);

void GERAÇÃO_0 (PESSOA x []);

double MULTILAYER_PERCEPTRON (double INPUT1, double INPUT2, double INPUT3, double INPUT4, PESSOA *x);

void NEXT_GERAÇÕES (PESSOA x [], int ELITES);
void FILHOS_NEXT_GERAÇÕES (PESSOA *PAI1, PESSOA *PAI2, PESSOA *FILHO, int NÚMERO_DE_GENES);

void MAIN_LOOP (PESSOA x [], struct TUBOS colunas[], Texture2D Flappy);



//------------------------------------------------------------------------ MAIN -----------------------------------------------------------------------------------------

int main () {

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

        POS_INICIAL_X_PRIMEIRO_PIPE += 280;

	}


    PESSOA x [POPULAÇÃO];
    
    GERAÇÃO_0 (x);


    FILE* LOGS;

    LOGS = fopen ("4INPUTSNORMALIZADOS_5NEURÓNIOS_SIGMOID_RELU.txt", "w");
        
    

    while (!WindowShouldClose()) {

        

        MAIN_LOOP (x, colunas, Flappy);

        for (int i = 0; i < NÚMERO_TUBOS; i++) {
           
             colunas[i].POS_EIXO_X -= 2.9;
		}	

 


        if (MORTES >= POPULAÇÃO) {

			NEXT_POPULATION = true;

            fprintf (LOGS, "\n GERAÇÃO %i \n -----------------------------------------------------", GERAÇÃO);
            
            for (int i = 0; i < POPULAÇÃO; i++) {
                
                fprintf(LOGS, "\n Indivíduo %i \n", i);
    
                for (int j = 0; j < NÚMERO_GENES; j++) {

                    fprintf(LOGS, "Genes %i -> %lf \n", j, x[i].GENES[j]);
                }
            }
            
            for (int i = 0; i < POPULAÇÃO; i++) {
            
               fprintf(LOGS, "Fitness Indivíduo %i = %lf \n", i, x[i].STORED_FITNESS);   
                
            }
        }


        if (GAME_OVER == true) {

            UnloadTexture(Flappy);
		    CloseWindow();
            fclose(LOGS);

        }


		if (NEXT_POPULATION == true) {
            
             
			NEXT_GERAÇÕES (x, NUM_ELITES);          
            RESET_JOGO (colunas);
			GERAÇÃO ++;
            MORTES = 0;
			NEXT_POPULATION = false;
            
		}


        


        for (int i = 0; i < POPULAÇÃO; i++) {

            if (x[i].VIVO == false) {
                   
                //x[i].POS_INICIAL_Y += 10.0f;
                x[i].POS_INICIAL_X -= 3.0f;
            }    
        }


        



		BeginDrawing();
		ClearBackground(DARKBLUE);



        for (int i = 0; i < POPULAÇÃO; i++) {
		    
            DrawTextureEx(Flappy, (Vector2){x[i].POS_INICIAL_X, x[i].POS_INICIAL_Y}, 0, 0.45, RAYWHITE);

            // Debug DrawCircle (x[i].POS_INICIAL_X + (Flappy.width * 0.45 / 2 + 10),
            //           x[i].POS_INICIAL_Y + (Flappy.height * 0.45 / 2), 20, BLACK);


        }
		

		for (int i = 0; i < NÚMERO_TUBOS; i++) {
			
			DrawRectangle (colunas[i].POS_EIXO_X, 0, 85, colunas[i].ALTURA_TUBO_CIMA, WHITE);
			DrawRectangle (colunas[i].POS_EIXO_X + 2, (ALTURA - colunas[i].ALTURA_TUBO_BAIXO), 85, colunas[i].ALTURA_TUBO_BAIXO, WHITE);

            
        }


        

		DrawText(TextFormat("População %i", GERAÇÃO), 30, 50, 25, BLACK);		
		DrawText(TextFormat("Indivíduos Restantes = %i", POPULAÇÃO - MORTES), 30, 80, 25, BLACK);
        

       
     


		EndDrawing();
	}

		UnloadTexture(Flappy);
		CloseWindow();
        fclose(LOGS);

}



int COMPARAÇÃO (const void *a, const void *b) {

    PESSOA *ind1 = (PESSOA *)a;
   	PESSOA *ind2 = (PESSOA *)b;

    
    if (ind1 -> STORED_FITNESS < ind2 -> STORED_FITNESS) return 1;
    if (ind1 -> STORED_FITNESS > ind2 -> STORED_FITNESS) return -1;
    

    return 0;

}




double FUNÇÃO_ATIVAÇÃO_SIGMOID (double x) {

    return 1.0 / (1.0 + exp(-x));
}



double FUNÇÃO_ATIVAÇÃO_ReLU (double x) {

    
    if (x < 0) {

        return 0;                
    }

    return x;

}


void RESET_JOGO (struct TUBOS colunas []) {


    float POS_INICIAL_X_PRIMEIRO_PIPE_2 = 680;

    for (int i = 0; i < NÚMERO_TUBOS; i++) {
	
        int ALTURA_MAX_TUBO_CIMA = ALTURA - TUBO_GAP - 50;
        int ALTURA_TUBO_CIMA = rand() % (ALTURA_MAX_TUBO_CIMA - 50) + 50;
        int ALTURA_TUBO_BAIXO = ALTURA - ALTURA_TUBO_CIMA - TUBO_GAP;

       
        colunas[i].POS_EIXO_X = POS_INICIAL_X_PRIMEIRO_PIPE_2;
        colunas[i].ALTURA_TUBO_CIMA = ALTURA_TUBO_CIMA;
        colunas[i].ALTURA_TUBO_BAIXO = ALTURA_TUBO_BAIXO;

        POS_INICIAL_X_PRIMEIRO_PIPE_2 += 280;

	}

}


void GERAÇÃO_0 (PESSOA x []) {


    for (int i = 0; i < POPULAÇÃO; i++) {
        for (int j = 0; j < NÚMERO_GENES; j++) {

            x[i].GENES[j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        }
            x[i].GENES[NÚMERO_GENES - 1] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    
            
            
            x[i].FITNESS = 0;
            x[i].STORED_FITNESS = 0;
            x[i].VIVO = true;

            x[i].POS_INICIAL_X = 150;
            x[i].POS_INICIAL_Y = 40 + ((double)rand() / RAND_MAX) * (ALTURA - 40);
            x[i].VELOCIDADE_Y = 0.5;


            
    }
}




double MULTILAYER_PERCEPTRON (double INPUT1, double INPUT2, double INPUT3, double INPUT4, PESSOA *x ) {

    int index = 0;
        
        for (int k = 0; k < 5; k++) {
           
            x -> NEURÓNIO_HIDDEN_LAYER[k] = INPUT1 * x -> GENES[index++] +
                                     INPUT2 * x -> GENES[index++] +
                                     INPUT3 * x -> GENES[index++] +
                                     INPUT4 * x -> GENES[index++];
                                                
                                     
            x -> NEURÓNIO_HIDDEN_LAYER[k] += x -> GENES[index++];
                        
            }

               
        for (int j = 0; j < 5; j++) {
            
            x -> OUTPUT_NEURÓNIO_HIDDEN_LAYER[j] = FUNÇÃO_ATIVAÇÃO_SIGMOID (x -> NEURÓNIO_HIDDEN_LAYER[j]);
        
            }
        

        x -> OUTPUT = 0;
        for (int z = 0; z < 5; z++) {

            x -> OUTPUT += x -> OUTPUT_NEURÓNIO_HIDDEN_LAYER[z] * x -> GENES[index++];
        }

        x -> OUTPUT += x -> GENES[NÚMERO_GENES - 1];

        x -> OUTPUT = FUNÇÃO_ATIVAÇÃO_ReLU(x -> OUTPUT);

        return x -> OUTPUT;
    
}




void NEXT_GERAÇÕES (PESSOA x [], int ELITES) {

    qsort (x, POPULAÇÃO, sizeof(PESSOA), COMPARAÇÃO);
  

    PESSOA NEW_GEN [POPULAÇÃO];
    
    for (int i = 0; i < NUM_ELITES; i++) {

        NEW_GEN [i] = x [i];
        
    }


    for (int i = NUM_ELITES; i < POPULAÇÃO; i++) {

		int PAI1 = rand() % (NUM_ELITES);
       
		int PAI2 = rand() % (NUM_ELITES);
   
		FILHOS_NEXT_GERAÇÕES (&NEW_GEN[PAI1], &NEW_GEN[PAI2], &NEW_GEN[i], NÚMERO_GENES);
	
	}
    

    for (int i = 0; i < POPULAÇÃO; i++) {

        x[i] = NEW_GEN[i]; //REPLACEMENT DA POPULAÇÃO
        
        x[i].FITNESS = 0;
        x[i].STORED_FITNESS = 0;
        x[i].VIVO = true;

        x[i].POS_INICIAL_X = 150;
        x[i].POS_INICIAL_Y = 40 + ((double)rand() / RAND_MAX) * (ALTURA - 40);
        x[i].VELOCIDADE_Y = 0.5;


       
    }
}





void FILHOS_NEXT_GERAÇÕES (PESSOA *PAI1, PESSOA *PAI2, PESSOA *FILHO, int NÚMERO_DE_GENES) {

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

		if ((rand() / (double)RAND_MAX) < TAXA_DE_MUTAÇÃO) {

			FILHO -> GENES[i] += ((double)rand() / RAND_MAX) * 0.2 - 0.1;	

		}
	}
}



void MAIN_LOOP (PESSOA x [], struct TUBOS colunas[], Texture2D Flappy) {


    for (int i = 0; i < POPULAÇÃO; i++) {

        if (x[i].VIVO == false) {
           
            continue;
        
        }
   
        int NEXTPIPE = -1;

        x[i].FITNESS ++;

        x[i].VELOCIDADE_Y += GRAVIDADE;
        x[i].POS_INICIAL_Y += x[i].VELOCIDADE_Y;



        Vector2 FLAPPYHITBOX = {
                                x[i].POS_INICIAL_X + (Flappy.width * 0.45 / 2 + 10),
                                x[i].POS_INICIAL_Y + (Flappy.height * 0.45 / 2)
                        };
    
       
        for (int j = 0; j < NÚMERO_TUBOS; j++) {


            Rectangle TUBOCIMA = {colunas[j].POS_EIXO_X, 0, 85, colunas[j].ALTURA_TUBO_CIMA};
            Rectangle TUBOBAIXO = {colunas[j].POS_EIXO_X + 2, (ALTURA - colunas[j].ALTURA_TUBO_BAIXO), 85, colunas[j].ALTURA_TUBO_BAIXO};



            COLISÃO_CIMA = CheckCollisionCircleRec (FLAPPYHITBOX, 20, TUBOCIMA);
            COLISÃO_BAIXO = CheckCollisionCircleRec (FLAPPYHITBOX, 20, TUBOBAIXO);


            if (colunas[j].POS_EIXO_X + 85 >= x[i].POS_INICIAL_X && NEXTPIPE == -1) { //Enquanto o Boneco tiver atrás do Pipe, o NEXTPIPE vai ser sempre o mesmo índice, só reseta quando for maior que a POS_INICIAL_X
                NEXTPIPE = j;
            }

                    
    
            if (COLISÃO_CIMA == true || COLISÃO_BAIXO == true) {

			    x[i].VIVO = false;
                
                MORTES += 1;
                x[i].STORED_FITNESS = x[i].FITNESS;
               
                //x[i].POS_INICIAL_X -= 200.0f;
                //x[i].POS_INICIAL_Y += 200.0f;  

            }



            x[i].CENTRO_COORDENADA_PIPE = colunas[j].ALTURA_TUBO_CIMA + (TUBO_GAP / 2.0);
        } 


       if (NEXTPIPE != -1) {

            x[i].X_TO_NEXTPIPE = (colunas[NEXTPIPE].POS_EIXO_X + 85) - x[i].POS_INICIAL_X;

            x[i].CENTRO_COORDENADA_PIPE = colunas[NEXTPIPE].ALTURA_TUBO_CIMA + (TUBO_GAP / 2.0);
        }


        if (x[i].POS_INICIAL_Y > (ALTURA - 40) || x[i].POS_INICIAL_Y <= 0) {

            x[i].VIVO = false;
           
            MORTES += 1;
            x[i].STORED_FITNESS = x[i].FITNESS;
            
            //x[i].POS_INICIAL_X -= 200.0f;
            //x[i].POS_INICIAL_Y += 200.0f;
		
        }


        if (NEXTPIPE == -1 && x[i].VIVO == true) {

                x[i].VIVO = false;
                x[i].STORED_FITNESS = x[i].FITNESS + 500000; // bónus de vitória
                MORTES += 1;
                GAME_OVER = true;

        }


      
        double output = MULTILAYER_PERCEPTRON ((double) x[i].POS_INICIAL_Y / (double) ALTURA,
                       (double) x[i].X_TO_NEXTPIPE / (double) LARGURA,
                       (double) x[i].VELOCIDADE_Y / (double) 10.0,
                       ((double) x[i].CENTRO_COORDENADA_PIPE - (double) x[i].POS_INICIAL_Y) / (double) ALTURA, 
                       &x[i]);

        
        if (output > 0.0) {
            x[i].VELOCIDADE_Y = -8.8f;
        }
        
        
    }
}
//-------------------------------------------------------------------------- fim ---------------------------------------------------------------------------------------












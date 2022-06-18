#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

const float FPS = 50;  

const int SCREEN_H = 960;
const int SCREEN_W = 441;

const int SCREEN_H_MENU = 675;
const int SCREEN_W_MENU = 1200;


//JOGADOR:
int DIST_FUNDO = 50;
int ALTURA_JOGADOR = 30;
int LARGURA_JOGADOR = 100;
float VEL_JOGADOR = 3;


typedef struct Jogador {
	float x, y, h, w, vel;
	int dir, esq, cima, baixo;
	ALLEGRO_COLOR cor;
	int id;
} Jogador;



void verifica_posicao(Jogador *p);
void desenhaJogador(Jogador p);
void atualiza_jogador(Jogador *p);
void desenha_jogador(Jogador p);
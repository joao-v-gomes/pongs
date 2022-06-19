#ifndef JOGADORES_H
#define JOGADORES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

// #include "pongs.h"

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

void verifica_posicoes_jogadores(Jogador *p1, Jogador *p2);
void verifica_posicao(Jogador *p);
void desenha_jogadores(Jogador p1, Jogador p2);
void desenha_jogador(Jogador p);
void init_jogador(Jogador *p);
void init_jogador1(Jogador *p1);
void init_jogador2(Jogador *p2);
void atualiza_jogadores(Jogador *p1, Jogador *p2);
void atualiza_jogador(Jogador *p);

#endif
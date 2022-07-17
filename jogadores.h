#ifndef JOGADORES_H
#define JOGADORES_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//
#include "pongs.h"

// JOGADORES:
// Jogador 1 -> Jogador padrao
// Jogador 2 -> Jogador pequeno e rapido
// Jogador 2 -> Jogador grande e lento
#define DIST_FUNDO 50
//
#define ALTURA_JOGADOR_1  30
#define LARGURA_JOGADOR_1 100
#define VEL_JOGADOR_1	  3
#define COR_JOGADOR_1	  al_map_rgb(0, 0, 155)
//
#define ALTURA_JOGADOR_2  25
#define LARGURA_JOGADOR_2 75
#define VEL_JOGADOR_2	  5
#define COR_JOGADOR_2	  al_map_rgb(155, 0, 0)
//
#define ALTURA_JOGADOR_3  35
#define LARGURA_JOGADOR_3 150
#define VEL_JOGADOR_3	  2
#define COR_JOGADOR_3	  al_map_rgb(155, 0, 155)

typedef struct Jogador {
	float x, y, h, w, vel;
	int dir, esq, cima, baixo;
	ALLEGRO_COLOR cor;
	int id;
} Jogador;

typedef enum {
	TIPO_JOGADOR1,
	TIPO_JOGADOR2,
	TIPO_JOGADOR3,

	JOGADOR_ESCOLHIDO,

	INIT_ESCOLHA_JOGADOR
} fsm_escolha_jogadores;

void verifica_posicoes_jogadores(Jogador *p1, Jogador *p2);
void verifica_fundo_baixo(Jogador *p);
void verifica_fundo_alto(Jogador *p);
void verifica_fundo_esquerdo(Jogador *p);
void verifica_fundo_direito(Jogador *p);
void verifica_meio_quadra(Jogador *p);
void verifica_posicao(Jogador *p);
void desenha_jogadores(Jogador p1, Jogador p2);
void desenha_jogador(Jogador p);
void init_jogador(Jogador *p, fsm_escolha_jogadores opcao_jogador);
void init_jogador1(Jogador *p1, fsm_escolha_jogadores opcao_jogador);
void init_jogador2(Jogador *p2, fsm_escolha_jogadores opcao_jogador);
void atualiza_jogadores(Jogador *p1, Jogador *p2);
void atualiza_jogador(Jogador *p);

#endif
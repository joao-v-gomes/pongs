#ifndef BOLAS_H
#define BOLAS_H

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
//
#include "jogadores.h"
//
#include "graficos.h"
//
#include "bolas.h"

#define MIN_DX_BOLA		  1
#define MAX_DX_BOLA		  12
#define MIN_DY_BOLA		  1
#define MAX_DY_BOLA		  20
#define DIAMETRO_BOLA_MIN 3
#define DIAMETRO_BOLA_MAX 8
#define MAX_BOLAS		  20
#define TEMPO_SOLTA_BOLA  5

typedef enum {
	CANTO_SUP_DIR,
	CANTO_INF_DIR,
	CANTO_INF_ESQ,
	CANTO_SUP_ESQ

} posicao_bola;

typedef struct Bola {
	float x, y;
	float dx, dy;
	uint8_t d;
	uint8_t id;
	uint8_t bola_valida;

} Bola;
void init_bolas(Bola bola[], int *contador_bolas);
void verifica_fundo_baixo_bola(Bola *b, int *contador_bolas, int *pontos2);
void verifica_fundo_alto_bola(Bola *b, int *contador_bolas, int *pontos1, int tipo_jogo);
void verifica_fundo_esquerdo_bola(Bola *b);
void verifica_fundo_direito_bola(Bola *b);
void verifica_contato_jogador(Bola *b, Jogador *j, bool pode_rebater);
void cria_bola(Bola bolas[], int *contador_bolas);
void atualiza_posicao_bola(Bola *bola);
void atualiza_bolas(Bola bolas[]);
void desenha_bola(Bola bolas[]);
void verifica_posicao_bola_quadra(Bola bola[], int *contador_bolas, int *pontos1, int *pontos2, int tipo_jogo);
void verifica_posicao_bola_jogador(Bola bola[], Jogador *j, bool pode_rebater);
void verifica_posicao_bola_jogadores(Bola bola[], Jogador *j1, Jogador *j2, bool pode_rebater_j1, bool pode_rebater_j2);

#endif
#ifndef PONGS_H
#define PONGS_H

#include "jogadores.h"

#define FPS			30
#define SCREEN_INIT 1
#define JOGO_H		440
#define JOGO_W		960

typedef enum {
	INIT_MENU,
	MENU,
	UM_JOGADOR,
	DOIS_JOGADORES,
	SAIR,

	ESCOLHE_UM_JOGADOR,
	ESCOLHE_DOIS_JOGADORES,

	CARREGA_UM_JOGADOR,
	CARREGA_DOIS_JOGADORES,

	JOGO_UM_JOGADOR,
	JOGO_DOIS_JOGADORES,
} fsm_menu;

typedef enum {
	TIPO_JOGADOR1,
	TIPO_JOGADOR2,
	TIPO_JOGADOR3,

	JOGADOR_ESCOLHIDO,

	INIT_ESCOLHA_JOGADOR
} fsm_escolha_jogadores;

void verifica_tecla_movimentacao(ALLEGRO_EVENT ev, Jogador *p1, Jogador *p2);
void verifica_esc(ALLEGRO_EVENT ev, int *playing);

#endif
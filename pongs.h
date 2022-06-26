#ifndef PONGS_H
#define PONGS_H

#include "jogadores.h"

#define FPS			50
#define SCREEN_INIT 1
#define SCREEN_H	960
#define SCREEN_W	441

typedef enum {
	INIT_MENU,
	MENU,
	UM_JOGADOR,
	DOIS_JOGADORES,
	SAIR,

	ESCOLHE_UM_JOGADOR,
	ESCOLHE_DOIS_JOGADORES,

	JOGO_UM_JOGADOR,
	JOGO_DOIS_JOGADORES,
} fsm_menu;

typedef enum {
	INIT_ESCOLHA_JOGADOR,

	POSICAO_JOGADOR1,
	POSICAO_JOGADOR2,
	POSICAO_JOGADOR3
} fsm_escolha_jogadores;

// void verifica_tecla_movimentacao(ALLEGRO_EVENT ev, Jogador *p1, Jogador *p2);
// void verifica_esc(int *playing, ALLEGRO_EVENT ev);

#endif
#ifndef PONGS_H
#define PONGS_H

#include "jogadores.h"

#define FPS			50
#define SCREEN_INIT 1
#define SCREEN_H	960
#define SCREEN_W	441

typedef enum {
	INIT,
	MENU,
	UM_JOGADOR,
	DOIS_JOGADORES,
	SAIR,

	ESCOLHE_UM_JOGADOR,
	ESCOLHE_DOIS_JOGADORES,

	JOGO_UM_JOGADOR,
	JOGO_DOIS_JOGADORES,
} fsm_menu;

// void desenha_quadra();
// void desenha_menu(ALLEGRO_FONT *size_32, ALLEGRO_BITMAP *bg_menu, ALLEGRO_BITMAP *seta_menu, uint8_t counter);
// void verifica_tecla_movimentacao(ALLEGRO_EVENT ev, Jogador *p1, Jogador *p2);
// void verifica_esc(int *playing, ALLEGRO_EVENT ev);

#endif
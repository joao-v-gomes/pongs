#ifndef PONGS_H
#define PONGS_H

#include "jogadores.h"

#define FPS			   30
#define SCREEN_INIT	   1
#define JOGO_H		   440
#define JOGO_W		   960
#define PONTOS_VITORIA 2
#define UM_JOG		   1
#define DOIS_JOG	   2

#define MAX_LINHAS_LIDAS   8
#define MIN_ESCRITA_LINHAS 350

typedef enum {
	INIT_MENU,
	MENU,
	UM_JOGADOR,
	DOIS_JOGADORES,
	AGUARDA_SAIR,
	SAIR,

	ESCOLHE_UM_JOGADOR,
	ESCOLHE_DOIS_JOGADORES,

	CARREGA_UM_JOGADOR,
	CARREGA_DOIS_JOGADORES,

	JOGO_UM_JOGADOR,
	JOGO_DOIS_JOGADORES,

	CARREGA_FINAL_JOGO,
	FINAL_JOGO,
} fsm_menu;

void init_pongs();
void verifica_selecao_menu(ALLEGRO_EVENT ev, int *counter, int *counter2, fsm_menu *state);
void verifica_movimentacao_menus(ALLEGRO_EVENT ev, int *counter, int *counter2);
void verifica_tecla_movimentacao(ALLEGRO_EVENT ev, Jogador *p1, Jogador *p2, fsm_menu state);
void verifica_esc(ALLEGRO_EVENT ev, int *playing);
void verifica_selecao_jogador(ALLEGRO_EVENT ev, int *counter, int *counter2, fsm_escolha_jogadores *opcao_jogador1, fsm_escolha_jogadores *opcao_jogador2, fsm_menu *state);

#endif
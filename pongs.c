#include "pongs.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_image.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//
#include "jogadores.h"

ALLEGRO_SAMPLE *move_menu = NULL;
ALLEGRO_SAMPLE *intro = NULL;

void init_pongs() {
	move_menu = al_load_sample("data/audio/menu-navigate-03.wav");
	intro = al_load_sample("data/audio/top-gear-3.wav");

	// al_play_sample(intro, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void verifica_esc(ALLEGRO_EVENT ev, int *playing) {
	if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
		*playing = 0;
	}
}

void verifica_selecao_menu(ALLEGRO_EVENT ev, int *counter, int *counter2, fsm_menu *state) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
			switch (*counter) {
				case 0:
					*state = ESCOLHE_UM_JOGADOR;
					*counter = 0;
					*counter2 = -1;
					printf("Foi escolhe um jogador!\r\n");
					break;
				case 1:
					*state = ESCOLHE_DOIS_JOGADORES;
					*counter = 0;
					*counter2 = 0;
					printf("Foi escolhe dois jogador!\r\n");
					break;
				case 2:
					*state = SAIR;
					break;

				default:
					break;
					// opcao_menu = counter;
			}
		}
	}
}

void verifica_selecao_jogador(ALLEGRO_EVENT ev, int *counter, int *counter2, fsm_escolha_jogadores *opcao_jogador1, fsm_escolha_jogadores *opcao_jogador2, fsm_menu *state) {
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
			switch (*counter) {
				case 0:
					*opcao_jogador1 = TIPO_JOGADOR1;
					break;
				case 1:
					*opcao_jogador1 = TIPO_JOGADOR2;
					break;
				case 2:
					*opcao_jogador1 = TIPO_JOGADOR3;
					break;

				default:
					*opcao_jogador1 = INIT_ESCOLHA_JOGADOR;
					break;
					// opcao_menu = counter;
			}
		}

		if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
			switch (*counter2) {
				case 0:
					*opcao_jogador2 = TIPO_JOGADOR1;
					break;
				case 1:
					*opcao_jogador2 = TIPO_JOGADOR2;
					break;
				case 2:
					*opcao_jogador2 = TIPO_JOGADOR3;
					break;

				default:
					*opcao_jogador2 = INIT_ESCOLHA_JOGADOR;
					break;
					// opcao_menu = counter;
			}
		}
	}

	if (*state == ESCOLHE_UM_JOGADOR) {
		if (*opcao_jogador1 != INIT_ESCOLHA_JOGADOR) {
			*state = CARREGA_UM_JOGADOR;
		}
	} else if (*state == ESCOLHE_DOIS_JOGADORES) {
		if (*opcao_jogador1 != INIT_ESCOLHA_JOGADOR && *opcao_jogador2 != INIT_ESCOLHA_JOGADOR) {
			*state = CARREGA_DOIS_JOGADORES;
		}
	}
}

void verifica_movimentacao_menus(ALLEGRO_EVENT ev, int *counter, int *counter2) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
			al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

			// *counter-- não funciona. Estranho...
			*counter = *counter - 1;

			if (*counter < 0) {
				*counter = 2;
			}
		} else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

			// *counter++ não funciona. Estranho...
			*counter = *counter + 1;

			if (*counter > 2) {
				*counter = 0;
			}
		}

		if (*counter2 != -1) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_W) {
				al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

				// *counter-- não funciona. Estranho...
				*counter2 = *counter2 - 1;

				if (*counter2 < 0) {
					*counter2 = 2;
				}
			} else if (ev.keyboard.keycode == ALLEGRO_KEY_S) {
				al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

				// *counter++ não funciona. Estranho...
				*counter2 = *counter2 + 1;

				if (*counter2 > 2) {
					*counter2 = 0;
				}
			}
		}
	}
}

void verifica_tecla_movimentacao(ALLEGRO_EVENT ev, Jogador *p1, Jogador *p2) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				p1->cima = 1;
				break;

			case ALLEGRO_KEY_S:
				p1->baixo = 1;
				break;

			case ALLEGRO_KEY_A:
				p1->esq = 1;
				break;

			case ALLEGRO_KEY_D:
				p1->dir = 1;
				break;

			case ALLEGRO_KEY_UP:
				p2->cima = 1;
				break;

			case ALLEGRO_KEY_DOWN:
				p2->baixo = 1;
				break;

			case ALLEGRO_KEY_LEFT:
				p2->esq = 1;
				break;

			case ALLEGRO_KEY_RIGHT:
				p2->dir = 1;
				break;
		}
	} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {

		switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				p1->cima = 0;
				break;

			case ALLEGRO_KEY_S:
				p1->baixo = 0;
				break;

			case ALLEGRO_KEY_A:
				p1->esq = 0;
				break;

			case ALLEGRO_KEY_D:
				p1->dir = 0;
				break;

			case ALLEGRO_KEY_UP:
				p2->cima = 0;
				break;

			case ALLEGRO_KEY_DOWN:
				p2->baixo = 0;
				break;

			case ALLEGRO_KEY_LEFT:
				p2->esq = 0;
				break;

			case ALLEGRO_KEY_RIGHT:
				p2->dir = 0;
				break;
		}
	}
}

void limpa_pongs() {
	al_destroy_sample(intro);
	al_destroy_sample(move_menu);
}
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

	al_play_sample(intro, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void verifica_esc(ALLEGRO_EVENT ev, int *playing) {
	if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
		*playing = 0;
	}
}

void verifica_selecao_menu(ALLEGRO_EVENT ev, int *counter, fsm_menu *opcao_menu) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
			switch (*counter) {
				case 0:
					*opcao_menu = UM_JOGADOR;
					break;
				case 1:
					*opcao_menu = DOIS_JOGADORES;
					break;
				case 2:
					*opcao_menu = SAIR;
					break;

				default:
					break;
					// opcao_menu = counter;
			}
		}
	}
}

void verifica_selecao_jogador() {
}

void verifica_som_menu(ALLEGRO_EVENT ev, int *counter) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
			al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

			// *counter-- não funciona. Estranho...
			*counter = *counter - 1;

			if (*counter < 0) {
				*counter = 2;
			}
		}

		if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

			// *counter++ não funciona. Estranho...
			*counter = *counter + 1;

			if (*counter > 2) {
				*counter = 0;
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
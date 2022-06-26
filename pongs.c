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

void init_pongs() {
	move_menu = al_load_sample("data/audio/menu-navigate-03.wav");
}

void verifica_esc(ALLEGRO_EVENT ev, int *playing) {
	if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
		*playing = 0;
	}
}

void verifica_selecao_menu(ALLEGRO_EVENT ev, int *counter, fsm_menu *state, fsm_menu *opcao) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
			if (*state == MENU) {
				switch (*counter) {
					case 0:
						*opcao = UM_JOGADOR;
						break;
					case 1:
						*opcao = DOIS_JOGADORES;
						break;
					case 2:
						*opcao = SAIR;
						break;

					default:
						break;
				}
				// opcao = counter;
			}
		}
	}
}

void verifica_som_menu(ALLEGRO_EVENT ev, int *counter) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
			al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

			// printf("Valor counter1: %d\r\n", *counter);
			*counter = *counter - 1;
			// printf("Valor counter2: %d\r\n", *counter);

			if (*counter < 0) {
				*counter = 2;
			}
		}

		if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			// printf("Valor counter3: %d\r\n", *counter);
			*counter = *counter + 1;
			// printf("Valor counter4: %d\r\n", *counter);

			if (*counter > 2) {
				*counter = 0;
			}
		}
	}
}

void verifica_tecla_movimentacao(ALLEGRO_EVENT ev, Jogador *p1, Jogador *p2) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev.keyboard.keycode) {
				// se a tecla for o W
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
				// se a tecla for o W
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
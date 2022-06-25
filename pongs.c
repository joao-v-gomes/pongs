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

// extern const int SCREEN_H;
// extern const int SCREEN_W;

void desenha_quadra() {
	uint8_t linha = 3;

	al_clear_to_color(al_map_rgb(0, 155, 0));
	// Linha meio principal
	al_draw_line(linha, SCREEN_H / 2, SCREEN_W - linha, SCREEN_H / 2, al_map_rgb(255, 255, 255), linha + linha);

	// Linha baixo principal
	al_draw_line(0, SCREEN_H - linha, SCREEN_W - linha, SCREEN_H - linha, al_map_rgb(255, 255, 255), linha);

	// Linha alto principal
	al_draw_line(0, linha, SCREEN_W - linha, linha, al_map_rgb(255, 255, 255), linha);

	// Linha esq principal
	al_draw_line(3, linha, 3, SCREEN_H - linha, al_map_rgb(255, 255, 255), linha);

	// Linha dir principal
	al_draw_line(SCREEN_W - linha, linha - 1, SCREEN_W - linha, SCREEN_H - linha + 2, al_map_rgb(255, 255, 255), linha);

	// Linha esq secundaria
	al_draw_line(55, linha, 55, SCREEN_H - linha, al_map_rgb(255, 255, 255), linha);

	// Linha dir secundaria
	al_draw_line(SCREEN_W - 55, linha, SCREEN_W - 55, SCREEN_H - linha, al_map_rgb(255, 255, 255), linha);

	// Linha meio secundaria baixo
	al_draw_line(55, SCREEN_H - 222, SCREEN_W - 55, SCREEN_H - 222, al_map_rgb(255, 255, 255), linha);

	// Linha meio secundaria alto
	al_draw_line(55, 222, SCREEN_W - 55, 222, al_map_rgb(255, 255, 255), linha);

	// Linha centro
	al_draw_line(SCREEN_W / 2 - 2, 222, SCREEN_W / 2 - 2, 222 + (258 + 258), al_map_rgb(255, 255, 255), linha);
}

void desenha_menu(ALLEGRO_FONT *size_32, ALLEGRO_BITMAP *bg_menu, ALLEGRO_BITMAP *seta_menu, uint8_t counter) {
	char text[30];

	al_draw_bitmap(bg_menu, 0, 0, 0);

	// al_clear_to_color(al_map_rgb(0, 0, 50));
	sprintf(text, "1 Jogador");
	al_draw_text(size_32, al_map_rgb(255, 255, 255), 150, 280, 0, text);

	sprintf(text, "2 Jogadores");
	al_draw_text(size_32, al_map_rgb(255, 255, 255), 130, 350, 0, text);

	sprintf(text, "Sair");
	al_draw_text(size_32, al_map_rgb(255, 255, 255), 210, 412, 0, text);
	// al_draw_line(0, SCREEN_H/2, SCREEN_W, SCREEN_H/2, al_map_rgb(255,255,255), 4);

	// Posicoes menu para bmp de 30x30
	// 1 j -> 110 , 280
	// 2 j -> 90 , 350
	// sair -> 170 , 412

	switch (counter) {
		case 0:
			al_draw_bitmap(seta_menu, 110, 280, 0);
			break;
		case 1:
			al_draw_bitmap(seta_menu, 90, 350, 0);
			break;
		case 2:
			al_draw_bitmap(seta_menu, 170, 412, 0);
			break;

		default:
			break;
	}
}

void verifica_esc(int *playing, ALLEGRO_EVENT ev) {
	if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
		*playing = 0;
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
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_image.h"
#include "pongs.h"
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

void desenha_menu(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *size_32, ALLEGRO_BITMAP *bg_menu, uint8_t counter) {

	ALLEGRO_BITMAP *seletor = al_load_bitmap("data/img/barra-menu.bmp");

	char um_jog[10] = "1 Jogador";
	char dois_jog[12] = "2 Jogadores";
	char sair[5] = "Sair";

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	int text_w = 0;

	int posicao_w_texto = 0;
	int posicao_h_texto = 280;

	al_draw_bitmap(bg_menu, 0, 0, 0);

	text_w = al_get_text_width(size_32, um_jog);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);

	al_draw_text(size_32, al_map_rgb(255, 255, 255), posicao_w_texto, posicao_h_texto, 0, um_jog);

	text_w = al_get_text_width(size_32, dois_jog);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);
	posicao_h_texto = posicao_h_texto + 70;

	al_draw_text(size_32, al_map_rgb(255, 255, 255), posicao_w_texto, posicao_h_texto, 0, dois_jog);

	text_w = al_get_text_width(size_32, sair);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);
	posicao_h_texto = posicao_h_texto + 70;

	al_draw_text(size_32, al_map_rgb(255, 255, 255), posicao_w_texto, posicao_h_texto, 0, sair);

	switch (counter) {
		case 0:
			text_w = al_get_text_width(size_32, um_jog);
			posicao_w_texto = (screen_w / 2) - (text_w / 2);
			posicao_w_texto = posicao_w_texto - 30;

			posicao_h_texto = posicao_h_texto - (2 * 70) - 7;

			al_draw_bitmap(seletor, posicao_w_texto, posicao_h_texto, 0);
			break;
		case 1:
			text_w = al_get_text_width(size_32, dois_jog);
			posicao_w_texto = (screen_w / 2) - (text_w / 2);
			posicao_w_texto = posicao_w_texto - 30;

			posicao_h_texto = posicao_h_texto - (1 * 70) - 7;

			al_draw_bitmap(seletor, posicao_w_texto, posicao_h_texto, 0);
			break;
		case 2:
			text_w = al_get_text_width(size_32, sair);
			posicao_w_texto = (screen_w / 2) - (text_w / 2);
			posicao_w_texto = posicao_w_texto - 30;

			posicao_h_texto = posicao_h_texto - 7;

			al_draw_bitmap(seletor, posicao_w_texto, posicao_h_texto, 0);
			break;

		default:
			break;
	}
}

void limpa_menu(ALLEGRO_BITMAP *bg_menu) {
	al_destroy_bitmap(bg_menu);
}
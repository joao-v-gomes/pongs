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

ALLEGRO_FONT *fonte_texto_pequeno = NULL;
ALLEGRO_FONT *fonte_texto_grande = NULL;
ALLEGRO_BITMAP *seletor = NULL;

void init_graficos() {
	fonte_texto_pequeno = al_load_font("data/font/UbuntuMono-RI.ttf", 20, 1);
	fonte_texto_grande = al_load_font("data/font/UbuntuMono-RI.ttf", 32, 1);
	seletor = al_load_bitmap("data/img/barra-menu.bmp");
}

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

void desenha_menu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bg_menu, int *counter) {

	// printf("Valor counter6: %d\r\n", *counter);

	char um_jog[] = "1 Jogador";
	char dois_jog[] = "2 Jogadores";
	char sair[] = "Sair";

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	int text_w = 0;

	int posicao_w_texto = 0;
	int posicao_h_texto = 280;

	al_draw_bitmap(bg_menu, 0, 0, 0);

	text_w = al_get_text_width(fonte_texto_grande, um_jog);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);

	al_draw_text(fonte_texto_grande, al_map_rgb(255, 255, 255), posicao_w_texto, posicao_h_texto, 0, um_jog);

	text_w = al_get_text_width(fonte_texto_grande, dois_jog);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);
	posicao_h_texto = posicao_h_texto + 70;

	al_draw_text(fonte_texto_grande, al_map_rgb(255, 255, 255), posicao_w_texto, posicao_h_texto, 0, dois_jog);

	text_w = al_get_text_width(fonte_texto_grande, sair);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);
	posicao_h_texto = posicao_h_texto + 70;

	al_draw_text(fonte_texto_grande, al_map_rgb(255, 255, 255), posicao_w_texto, posicao_h_texto, 0, sair);

	switch (*counter) {
		case 0:
			text_w = al_get_text_width(fonte_texto_grande, um_jog);
			posicao_w_texto = (screen_w / 2) - (text_w / 2);
			posicao_w_texto = posicao_w_texto - 30;

			posicao_h_texto = posicao_h_texto - (2 * 70) - 7;

			al_draw_bitmap(seletor, posicao_w_texto, posicao_h_texto, 0);
			break;
		case 1:
			text_w = al_get_text_width(fonte_texto_grande, dois_jog);
			posicao_w_texto = (screen_w / 2) - (text_w / 2);
			posicao_w_texto = posicao_w_texto - 30;

			posicao_h_texto = posicao_h_texto - (1 * 70) - 7;

			al_draw_bitmap(seletor, posicao_w_texto, posicao_h_texto, 0);
			break;
		case 2:
			text_w = al_get_text_width(fonte_texto_grande, sair);
			posicao_w_texto = (screen_w / 2) - (text_w / 2);
			posicao_w_texto = posicao_w_texto - 30;

			posicao_h_texto = posicao_h_texto - 7;

			al_draw_bitmap(seletor, posicao_w_texto, posicao_h_texto, 0);
			break;

		default:
			break;
	}
}

void desenha_escolha_jogador(ALLEGRO_DISPLAY *display, fsm_escolha_jogadores *opcao_jogador1, fsm_escolha_jogadores *opcao_jogador2, fsm_menu state) {
	int num_jogador = 0;

	if (state == ESCOLHE_UM_JOGADOR) {
		num_jogador = 1;
	} else if (state == ESCOLHE_DOIS_JOGADORES) {
		num_jogador = 2;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	int text_w = 0;
	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	int posicao_w_texto = 0;
	int posicao_h_texto = 50;

	char escolha[] = "Escolha o seu jogador!";

	text_w = al_get_text_width(fonte_texto_grande, escolha);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);

	al_draw_text(fonte_texto_grande, al_map_rgb(255, 255, 255), posicao_w_texto, posicao_h_texto, 0, escolha);

	desenha_tipo_jogador1(display);
	desenha_tipo_jogador2(display);
	desenha_tipo_jogador3(display);
}

void desenha_tipo_jogador1(ALLEGRO_DISPLAY *display) {
	// al_draw_filled_rectangle(p.x, p.y, p.x + p.w, p.y + p.h, COR_JOGADOR_1);

	// uint8_t tamanho_fonte = 20;

	// ALLEGRO_FONT *fonte_texto = al_load_font("data/font/UbuntuMono-RI.ttf", tamanho_fonte, 1);

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	int text_w = 0;
	int posicao_w = 0;
	int posicao_h = 0;

	int x1 = (screen_w / 4) - (LARGURA_JOGADOR_1 / 2);
	int x2 = x1 + LARGURA_JOGADOR_1;
	int y1 = (screen_h / 3);
	int y2 = y1 + ALTURA_JOGADOR_1;

	al_draw_filled_rectangle(x1, y1, x2, y2, COR_JOGADOR_1);

	char velocidade[] = "Velocidade";
	char tamanho[] = "Tamanho";

	// Escreve Velocidade
	text_w = al_get_text_width(fonte_texto_pequeno, velocidade);
	posicao_w = (screen_w / 2) - 30;

	posicao_h = y1 - 30;

	al_draw_text(fonte_texto_pequeno, al_map_rgb(255, 255, 255), posicao_w, posicao_h, 0, velocidade);

	// Escreve Tamanho
	text_w = al_get_text_width(fonte_texto_pequeno, tamanho);
	posicao_w = (screen_w / 2) + text_w + 70;

	al_draw_text(fonte_texto_pequeno, al_map_rgb(255, 255, 255), posicao_w, posicao_h, 0, tamanho);

	int posicao_h_bolinha = y2 - 15;
	int posicao_w_bolinha = 260;

	// Desenha as bolinhas velocidade
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(posicao_w_bolinha + 20, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));

	posicao_w_bolinha = 415;

	// Desenha as bolinhas tamanho
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(posicao_w_bolinha + 20, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));
}

void desenha_tipo_jogador2(ALLEGRO_DISPLAY *display) {
	// al_draw_filled_rectangle(p.x, p.y, p.x + p.w, p.y + p.h, COR_JOGADOR_1);

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	int text_w = 0;
	int posicao_w = 0;
	int posicao_h = 50;

	int x1 = (screen_w / 4) - (LARGURA_JOGADOR_2 / 2);
	int x2 = x1 + LARGURA_JOGADOR_2;
	int y1 = (screen_h / 2) + 50;
	int y2 = y1 + ALTURA_JOGADOR_2;

	al_draw_filled_rectangle(x1, y1, x2, y2, COR_JOGADOR_2);

	char velocidade[] = "Velocidade";
	char tamanho[] = "Tamanho";

	// Escreve Velocidade
	text_w = al_get_text_width(fonte_texto_pequeno, velocidade);
	posicao_w = (screen_w / 2) - 30;

	posicao_h = y1 - 30;

	al_draw_text(fonte_texto_pequeno, al_map_rgb(255, 255, 255), posicao_w, posicao_h, 0, velocidade);

	// Escreve Tamanho
	text_w = al_get_text_width(fonte_texto_pequeno, tamanho);
	posicao_w = (screen_w / 2) + text_w + 70;

	al_draw_text(fonte_texto_pequeno, al_map_rgb(255, 255, 255), posicao_w, posicao_h, 0, tamanho);

	int posicao_h_bolinha = y2 - 15;
	int posicao_w_bolinha = 250;

	// Desenha as bolinhas velocidade
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(posicao_w_bolinha + 20, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(posicao_w_bolinha + 40, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));

	posicao_w_bolinha = 425;

	// Desenha as bolinhas tamanho
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));
}

void desenha_tipo_jogador3(ALLEGRO_DISPLAY *display) {
	// al_draw_filled_rectangle(p.x, p.y, p.x + p.w, p.y + p.h, COR_JOGADOR_1);

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	int text_w = 0;
	int posicao_w = 0;
	int posicao_h = 50;

	int x1 = (screen_w / 4) - (LARGURA_JOGADOR_3 / 2);
	int x2 = x1 + LARGURA_JOGADOR_3;
	int y1 = (screen_h / 2) + 170;
	int y2 = y1 + ALTURA_JOGADOR_3;

	al_draw_filled_rectangle(x1, y1, x2, y2, COR_JOGADOR_3);

	char velocidade[] = "Velocidade";
	char tamanho[] = "Tamanho";

	// Escreve Velocidade
	text_w = al_get_text_width(fonte_texto_pequeno, velocidade);
	posicao_w = (screen_w / 2) - 30;

	posicao_h = y1 - 30;

	al_draw_text(fonte_texto_pequeno, al_map_rgb(255, 255, 255), posicao_w, posicao_h, 0, velocidade);

	// Escreve Tamanho
	text_w = al_get_text_width(fonte_texto_pequeno, tamanho);
	posicao_w = (screen_w / 2) + text_w + 70;

	al_draw_text(fonte_texto_pequeno, al_map_rgb(255, 255, 255), posicao_w, posicao_h, 0, tamanho);

	int posicao_h_bolinha = y2 - 15;
	int posicao_w_bolinha = 270;

	// Desenha as bolinhas velocidade
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));
	// al_draw_filled_circle(posicao_w_bolinha + 20, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));

	posicao_w_bolinha = 405;

	// Desenha as bolinhas tamanho
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(posicao_w_bolinha + 20, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(posicao_w_bolinha + 40, posicao_h_bolinha, 5, al_map_rgb(255, 255, 255));
}

void limpa_menu(ALLEGRO_BITMAP *bg_menu) {
	al_destroy_bitmap(bg_menu);
}
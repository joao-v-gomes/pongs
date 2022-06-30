#include "graficos.h"
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
#include "jogadores.h"

ALLEGRO_FONT *fonte_texto_pequeno = NULL;
ALLEGRO_FONT *fonte_texto_grande = NULL;
ALLEGRO_BITMAP *bg_menu;
ALLEGRO_BITMAP *seletor = NULL;

void init_graficos() {
	fonte_texto_pequeno = al_load_font("data/font/UbuntuMono-RI.ttf", 20, 1);
	fonte_texto_grande = al_load_font("data/font/UbuntuMono-RI.ttf", 32, 1);
	seletor = al_load_bitmap("data/img/barra-menu.bmp");
	bg_menu = al_load_bitmap("data/img/menu-grande.bmp");
}

void desenha_quadra() {

	al_clear_to_color(al_map_rgb(0, 155, 0));

	// Linha alto principal
	al_draw_line(0, 0, JOGO_W, 0, COR_BRANCA, ESPESSURA_LINHA_QUADRA + ESPESSURA_LINHA_QUADRA);

	// Linha esquerda principal
	al_draw_line(0, 0, 0, JOGO_H, COR_BRANCA, ESPESSURA_LINHA_QUADRA + ESPESSURA_LINHA_QUADRA);

	// Linha baixo principal
	al_draw_line(0, JOGO_H, JOGO_W, JOGO_H, COR_BRANCA, ESPESSURA_LINHA_QUADRA + ESPESSURA_LINHA_QUADRA);

	// Linha direita principal
	al_draw_line(JOGO_W, 0, JOGO_W, JOGO_H, COR_BRANCA, ESPESSURA_LINHA_QUADRA + ESPESSURA_LINHA_QUADRA);

	// Linha centro
	al_draw_line(JOGO_W / 2, 0, JOGO_W / 2, JOGO_H, COR_BRANCA, ESPESSURA_LINHA_QUADRA + ESPESSURA_LINHA_QUADRA);

	// Linha alto secundaria
	al_draw_line(0, 55, JOGO_W, 55, COR_BRANCA, ESPESSURA_LINHA_QUADRA);

	// Linha baixo secundaria
	al_draw_line(0, JOGO_H - 55, JOGO_W, JOGO_H - 55, COR_BRANCA, ESPESSURA_LINHA_QUADRA);

	// Linha meio secundaria esq
	al_draw_line(222, 55, 222, JOGO_H - 55, COR_BRANCA, ESPESSURA_LINHA_QUADRA);

	// Linha meio secundaria direita
	al_draw_line(JOGO_W - 222, 55, JOGO_W - 222, JOGO_H - 55, COR_BRANCA, ESPESSURA_LINHA_QUADRA);

	// Linha centro
	al_draw_line(222, (55 + 166), JOGO_W - 222, (55 + 166), COR_BRANCA, ESPESSURA_LINHA_QUADRA);
}

void desenha_menu(ALLEGRO_DISPLAY *display, int *counter) {

	char um_jog[] = "1 Jogador";
	char dois_jog[] = "2 Jogadores";
	char sair[] = "Sair";

	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	int text_w = 0;

	int posicao_w_texto = 0;
	int posicao_h_texto = 350;

	al_draw_bitmap(bg_menu, 0, 0, 0);

	text_w = al_get_text_width(fonte_texto_grande, um_jog);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);

	al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, um_jog);

	text_w = al_get_text_width(fonte_texto_grande, dois_jog);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);
	posicao_h_texto = posicao_h_texto + 70;

	al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, dois_jog);

	text_w = al_get_text_width(fonte_texto_grande, sair);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);
	posicao_h_texto = posicao_h_texto + 70;

	al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, sair);

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

void desenha_escolha_jogador(ALLEGRO_DISPLAY *display) {

	al_clear_to_color(al_map_rgb(0, 0, 0));

	int text_w = 0;
	int screen_w = al_get_display_width(display);
	// int screen_h = al_get_display_height(display);

	int posicao_w_texto = 0;
	int posicao_h_texto = 50;

	char escolha[] = "Escolha o seu jogador!";

	text_w = al_get_text_width(fonte_texto_grande, escolha);
	posicao_w_texto = (screen_w / 2) - (text_w / 2);

	al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, escolha);

	desenha_tipo_jogador1(display);
	desenha_tipo_jogador2(display);
	desenha_tipo_jogador3(display);

	// int inicio_largura_box = 50;
	// int final_largura_box = 480;
	// int altura_box = 130;
	// int espessura = 2;

	// al_draw_rectangle(inicio_largura_box, altura_box, final_largura_box, altura_box + 90, COR_BRANCA, espessura);
	// al_draw_rectangle(inicio_largura_box + 10, (2 * altura_box), final_largura_box, (2 * altura_box) + 90, COR_BRANCA, espessura);
	// al_draw_rectangle(inicio_largura_box - 20, (3 * altura_box) - 5, final_largura_box, (3 * altura_box) - 5 + 90, COR_BRANCA, espessura);
}

void desenha_escolha_jogador_um(ALLEGRO_DISPLAY *display, int *counter) {
	// desenha_escolha_jogador(display);

	int pos_w = 30;
	int pos_h_1 = 180;
	int pos_h_2 = 330;
	int pos_h_3 = 460;

	int text_w = 0;

	int posicao_w_texto = 0;
	int posicao_h_texto = 350;

	char jogador1[] = "J1";

	text_w = al_get_text_width(fonte_texto_grande, jogador1);

	switch (*counter) {
		case 0:
			al_draw_text(fonte_texto_grande, COR_BRANCA, (pos_w - 10), (pos_h_1 - 40), 0, jogador1);

			al_draw_filled_rectangle(pos_w, pos_h_1, (pos_w + SELETOR_W), (pos_h_1 + SELETOR_H), COR_BRANCA);

			// al_draw_filled_rectangle(pos_w, pos_h_2, (pos_w + SELETOR_W), (pos_h_2 + SELETOR_H), al_map_rgb(0, 0, 0));
			// al_draw_filled_rectangle(pos_w, pos_h_3, (pos_w + SELETOR_W), (pos_h_3 + SELETOR_H), al_map_rgb(0, 0, 0));
			break;
		case 1:
			al_draw_text(fonte_texto_grande, COR_BRANCA, (pos_w - 10), (pos_h_2 - 40), 0, jogador1);

			al_draw_filled_rectangle(pos_w, pos_h_2, (pos_w + SELETOR_W), (pos_h_2 + SELETOR_H), COR_BRANCA);

			// al_draw_filled_rectangle(pos_w, pos_h_1, (pos_w + SELETOR_W), (pos_h_1 + SELETOR_H), al_map_rgb(0, 0, 0));
			// al_draw_filled_rectangle(pos_w, pos_h_3, (pos_w + SELETOR_W), (pos_h_3 + SELETOR_H), al_map_rgb(0, 0, 0));
			break;
		case 2:
			al_draw_text(fonte_texto_grande, COR_BRANCA, (pos_w - 10), (pos_h_3 - 40), 0, jogador1);

			al_draw_filled_rectangle(pos_w, pos_h_3, (pos_w + SELETOR_W), (pos_h_3 + SELETOR_H), COR_BRANCA);

			// al_draw_filled_rectangle(pos_w, pos_h_1, (pos_w + SELETOR_W), (pos_h_1 + SELETOR_H), al_map_rgb(0, 0, 0));
			// al_draw_filled_rectangle(pos_w, pos_h_2, (pos_w + SELETOR_W), (pos_h_2 + SELETOR_H), al_map_rgb(0, 0, 0));
			break;

		default:
			break;
	}
}

void desenha_escolha_jogador_dois(ALLEGRO_DISPLAY *display, int *counter2) {
	// desenha_escolha_jogador(display);

	int pos_w = MENU_W - 50;
	int pos_h_1 = 180;
	int pos_h_2 = 330;
	int pos_h_3 = 460;

	int text_w = 0;

	int posicao_w_texto = 0;
	int posicao_h_texto = 350;

	char jogador1[] = "J2";

	text_w = al_get_text_width(fonte_texto_grande, jogador1);

	switch (*counter2) {
		case 0:
			al_draw_text(fonte_texto_grande, COR_BRANCA, (pos_w - 10), (pos_h_1 - 40), 0, jogador1);

			al_draw_filled_rectangle(pos_w, pos_h_1, (pos_w + SELETOR_W), (pos_h_1 + SELETOR_H), COR_BRANCA);

			// al_draw_filled_rectangle(pos_w, pos_h_2, (pos_w + SELETOR_W), (pos_h_2 + SELETOR_H), al_map_rgb(0, 0, 0));
			// al_draw_filled_rectangle(pos_w, pos_h_3, (pos_w + SELETOR_W), (pos_h_3 + SELETOR_H), al_map_rgb(0, 0, 0));
			break;
		case 1:
			al_draw_text(fonte_texto_grande, COR_BRANCA, (pos_w - 10), (pos_h_2 - 40), 0, jogador1);

			al_draw_filled_rectangle(pos_w, pos_h_2, (pos_w + SELETOR_W), (pos_h_2 + SELETOR_H), COR_BRANCA);

			// al_draw_filled_rectangle(pos_w, pos_h_1, (pos_w + SELETOR_W), (pos_h_1 + SELETOR_H), al_map_rgb(0, 0, 0));
			// al_draw_filled_rectangle(pos_w, pos_h_3, (pos_w + SELETOR_W), (pos_h_3 + SELETOR_H), al_map_rgb(0, 0, 0));
			break;
		case 2:
			al_draw_text(fonte_texto_grande, COR_BRANCA, (pos_w - 10), (pos_h_3 - 40), 0, jogador1);

			al_draw_filled_rectangle(pos_w, pos_h_3, (pos_w + SELETOR_W), (pos_h_3 + SELETOR_H), COR_BRANCA);

			// al_draw_filled_rectangle(pos_w, pos_h_1, (pos_w + SELETOR_W), (pos_h_1 + SELETOR_H), al_map_rgb(0, 0, 0));
			// al_draw_filled_rectangle(pos_w, pos_h_2, (pos_w + SELETOR_W), (pos_h_2 + SELETOR_H), al_map_rgb(0, 0, 0));
			break;

		default:
			break;
	}
}

void desenha_tipo_jogador1(ALLEGRO_DISPLAY *display) {

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

	al_draw_text(fonte_texto_pequeno, COR_BRANCA, posicao_w, posicao_h, 0, velocidade);

	// Escreve Tamanho
	text_w = al_get_text_width(fonte_texto_pequeno, tamanho);
	posicao_w = (screen_w / 2) + text_w + 70;

	al_draw_text(fonte_texto_pequeno, COR_BRANCA, posicao_w, posicao_h, 0, tamanho);

	int posicao_h_bolinha = y2 - 15;
	int posicao_w_bolinha = 310;

	// Desenha as bolinhas velocidade
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, COR_BRANCA);
	al_draw_filled_circle(posicao_w_bolinha + 20, posicao_h_bolinha, 5, COR_BRANCA);

	posicao_w_bolinha = 470;

	// Desenha as bolinhas tamanho
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, COR_BRANCA);
	al_draw_filled_circle(posicao_w_bolinha + 20, posicao_h_bolinha, 5, COR_BRANCA);
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

	al_draw_text(fonte_texto_pequeno, COR_BRANCA, posicao_w, posicao_h, 0, velocidade);

	// Escreve Tamanho
	text_w = al_get_text_width(fonte_texto_pequeno, tamanho);
	posicao_w = (screen_w / 2) + text_w + 70;

	al_draw_text(fonte_texto_pequeno, COR_BRANCA, posicao_w, posicao_h, 0, tamanho);

	int posicao_h_bolinha = y2 - 15;
	int posicao_w_bolinha = 300;

	// Desenha as bolinhas velocidade
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, COR_BRANCA);
	al_draw_filled_circle(posicao_w_bolinha + 20, posicao_h_bolinha, 5, COR_BRANCA);
	al_draw_filled_circle(posicao_w_bolinha + 40, posicao_h_bolinha, 5, COR_BRANCA);

	posicao_w_bolinha = 480;

	// Desenha as bolinhas tamanho
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, COR_BRANCA);
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

	al_draw_text(fonte_texto_pequeno, COR_BRANCA, posicao_w, posicao_h, 0, velocidade);

	// Escreve Tamanho
	text_w = al_get_text_width(fonte_texto_pequeno, tamanho);
	posicao_w = (screen_w / 2) + text_w + 70;

	al_draw_text(fonte_texto_pequeno, COR_BRANCA, posicao_w, posicao_h, 0, tamanho);

	int posicao_h_bolinha = y2 - 15;
	int posicao_w_bolinha = 320;

	// Desenha as bolinhas velocidade
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, COR_BRANCA);
	// al_draw_filled_circle(posicao_w_bolinha + 20, posicao_h_bolinha, 5, COR_BRANCA);

	posicao_w_bolinha = 460;

	// Desenha as bolinhas tamanho
	al_draw_filled_circle(posicao_w_bolinha, posicao_h_bolinha, 5, COR_BRANCA);
	al_draw_filled_circle(posicao_w_bolinha + 20, posicao_h_bolinha, 5, COR_BRANCA);
	al_draw_filled_circle(posicao_w_bolinha + 40, posicao_h_bolinha, 5, COR_BRANCA);
}

void limpa_menu() {
	al_destroy_bitmap(seletor);
	al_destroy_bitmap(bg_menu);
	al_destroy_font(fonte_texto_pequeno);
	al_destroy_font(fonte_texto_grande);
}
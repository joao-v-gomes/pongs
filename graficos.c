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
ALLEGRO_SAMPLE *vencedor = NULL;

int i = 0;
int altura = 300;

void init_graficos() {
	fonte_texto_pequeno = al_load_font("data/font/UbuntuMono-RI.ttf", 22, 1);
	fonte_texto_grande = al_load_font("data/font/UbuntuMono-RI.ttf", 32, 1);
	seletor = al_load_bitmap("data/img/barra-menu.bmp");
	bg_menu = al_load_bitmap("data/img/menu-grande.bmp");
	vencedor = al_load_sample("data/audio/top-gear-fim.wav");
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
	char ajuda[] = "Aperte 'H' para ajuda";

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

	al_draw_text(fonte_texto_pequeno, COR_BRANCA, 10, 560, 0, ajuda);

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

void desenha_ajuda() {
	ALLEGRO_BITMAP *imagem_ajuda = NULL;

	imagem_ajuda = al_load_bitmap("data/img/ajuda.bmp");

	al_draw_bitmap(imagem_ajuda, 0, 0, 0);
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

void desenha_placar(int pontos_p1, int pontos_p2, int tipo_jogo, int tempo_jogo) {

	if (tipo_jogo == UM_JOG) {
		char aux[100];
		char pontos2[1000];
		char tempo[1000];

		sprintf(aux, "%d", pontos_p2);

		strcpy(pontos2, aux);

		strcpy(aux, "");

		int posicao_w_texto = 400;
		int posicao_h_texto = 20;

		al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, pontos2);

		sprintf(aux, "%d", tempo_jogo);

		strcpy(tempo, aux);

		strcpy(aux, "");

		posicao_w_texto = 540;

		al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, tempo);

	} else if (tipo_jogo == DOIS_JOG) {

		char aux[100];
		char pontos1[1000];
		char pontos2[1000];

		sprintf(aux, "%d", pontos_p1);

		strcpy(pontos1, aux);

		strcpy(aux, "");

		sprintf(aux, "%d", pontos_p2);

		strcpy(pontos2, aux);

		int posicao_w_texto = 400;
		int posicao_h_texto = 20;

		al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, pontos1);

		posicao_w_texto = 540;

		al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, pontos2);
	}
}

void desenha_final_jogo(int tipo_jogo, int pontos_p1, int pontos_p2, int tempo_jogo) {
	al_draw_bitmap(bg_menu, 0, 0, 0);

	al_stop_samples();
	if (COM_SOM) {
		al_play_sample(vencedor, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
	}

	// char linha[] = "teeste";

	// al_draw_text(fonte_texto_pequeno, COR_BRANCA, 200, 200, 0, linha);
	if (tipo_jogo == UM_JOG) {

		FILE *ler_partidas;

		char linha[1000];
		char c;
		int i = 0;
		int counter = 0;

		strcpy(linha, "");

		int posicao_h_texto = 0;
		int posicao_w_texto = 0;

		ler_partidas = fopen("partidas-um-jogador.txt", "r");
		printf("Leu arq\r\n");

		if (ler_partidas == NULL) {
			printf("Deu ruim arq um jogador\r\n");
		}

		// while (fgets(linha, 1000, ler_partidas)) {
		// 	printf("Linha lida: %s\r\n");
		// }

		// Conta a qtde de linhas no arquivo
		int qtde_linhas_total = 0;
		int qtde_linhas_parcial = 0;

		while (c != EOF) {
			c = fgetc(ler_partidas);

			if (c == '\n') {
				qtde_linhas_total++;
			}
		}

		//"Recarrega" o arquivo
		rewind(ler_partidas);
		c = " ";

		printf("Qtde linhas total: %d\r\n", qtde_linhas_total);

		posicao_h_texto = 180;

		int text_w = 0;

		char texto_final[100];

		// Escreve fim partida

		strcpy(texto_final, "Fim de Partida!");

		text_w = al_get_text_width(fonte_texto_grande, texto_final);
		posicao_w_texto = (MENU_W / 2) - (text_w / 2);

		al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, texto_final);

		// Escreve voce sobreviveu
		posicao_h_texto = 240;

		strcpy(texto_final, "Voce sobreviveu por: ");

		text_w = al_get_text_width(fonte_texto_pequeno, texto_final);
		posicao_w_texto = (MENU_W / 2) - (text_w / 2);

		al_draw_text(fonte_texto_pequeno, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, texto_final);

		char tempo[1000];

		sprintf(tempo, "%d", tempo_jogo);

		strcpy(texto_final, tempo);

		strcat(texto_final, " segundos!");

		posicao_h_texto = 270;

		text_w = al_get_text_width(fonte_texto_grande, texto_final);
		posicao_w_texto = (MENU_W / 2) - (text_w / 2);

		al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, texto_final);

		// Escreve o historico

		posicao_w_texto = 25;

		if (qtde_linhas_total == 1) {
			posicao_h_texto = MIN_ESCRITA_LINHAS;
		} else if (qtde_linhas_total > 1 && qtde_linhas_total < 10) {
			posicao_h_texto = MIN_ESCRITA_LINHAS + (qtde_linhas_total * 30);
		} else if (qtde_linhas_total >= 10) {
			posicao_h_texto = 550;
		}

		// Escreve vai pra primeira linha do historico valido
		while ((c != EOF) && (counter < MAX_LINHAS_LIDAS)) {
			while (qtde_linhas_parcial < qtde_linhas_total - MAX_LINHAS_LIDAS) {
				c = fgetc(ler_partidas);

				if (c == '\n') {
					qtde_linhas_parcial++;
				}
			}

			// printf("Qtde linhas parcial: %d\r\n", qtde_linhas_parcial);
			// counter = 10;

			// printf("Esta na linha certa!\r\n");

			// Escreve as linhas de historico em ordem
			c = fgetc(ler_partidas);

			if (c != '\n') {
				linha[i] = c;
				i++;
			} else {
				linha[i] = ' ';
				printf("Leu newline\r\n");
				// fgetc(ler_partidas);
				printf("Linha %d lida: %s\r\n", counter, linha);

				al_draw_text(fonte_texto_pequeno, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, linha);

				posicao_h_texto = posicao_h_texto - 30;

				strcpy(linha, "");

				i = 0;
				counter++;
			}
		}

		fclose(ler_partidas);
	} else if (tipo_jogo = DOIS_JOG) {

		int jogos_j1 = 0;
		int jogos_j2 = 0;

		FILE *pega_historico;
		pega_historico = fopen("historico.txt", "r");
		printf("Leu arq partidas\r\n");

		if (pega_historico == NULL) {
			printf("Deu ruim arq historico\r\n");
		} else {
			char aux[10];
			char c1, c2;
			// int hist[2];
			int i = 0;

			for (i = 0; i < 10; i++) {
				c1 = fgetc(pega_historico);

				if (c1 != ' ') {
					aux[i] = c1;
					// i++;
				} else {
					i = 10;
				}
			}

			printf("Hist_j1 pego: %s\r\n", aux);

			jogos_j1 = strtol(aux, NULL, 10);

			strcpy(aux, "          ");

			for (i = 0; i < 10; i++) {
				c2 = fgetc(pega_historico);

				if (c2 != ' ') {
					aux[i] = c2;
					// i++;
				} else {
					i = 10;
				}
			}

			printf("Hist_j2 pego: %s\r\n", aux);

			jogos_j2 = strtol(aux, NULL, 10);

			fclose(pega_historico);
		}

		FILE *ler_partidas;

		char linha[1000];
		char aux[10];
		char c;
		int i = 0;
		int counter = 0;

		strcpy(linha, "");
		strcpy(aux, "");

		int posicao_h_texto = 0;
		int posicao_w_texto = 0;

		ler_partidas = fopen("partidas-dois-jogadores.txt", "r");
		printf("Leu arq\r\n");

		if (ler_partidas == NULL) {
			printf("Deu ruim arq dois jogadores\r\n");
		}

		// while (fgets(linha, 1000, ler_partidas)) {
		// 	printf("Linha lida: %s\r\n");
		// }
		int qtde_linhas_total = 0;
		int qtde_linhas_parcial = 0;

		while (c != EOF) {
			c = fgetc(ler_partidas);

			if (c == '\n') {
				qtde_linhas_total++;
			}
		}

		rewind(ler_partidas);
		c = " ";

		printf("Qtde linhas total: %d\r\n", qtde_linhas_total);

		posicao_h_texto = 180;

		int text_w = 0;

		char texto_final[100];

		if (pontos_p1 >= PONTOS_VITORIA) {
			strcpy(texto_final, "Jogador 1 venceu!");
		} else if (pontos_p2 >= PONTOS_VITORIA) {
			strcpy(texto_final, "Jogador 2 venceu!");
		}

		text_w = al_get_text_width(fonte_texto_grande, texto_final);
		posicao_w_texto = (MENU_W / 2) - (text_w / 2);

		al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, texto_final);

		posicao_h_texto = 240;

		strcpy(texto_final, "Vitorias do J1: ");

		strcpy(aux, "");

		sprintf(aux, "%d", jogos_j1);

		strcat(texto_final, aux);

		al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, texto_final);

		posicao_h_texto = 280;

		strcpy(texto_final, "Vitorias do J2: ");

		strcpy(aux, "");

		sprintf(aux, "%d", jogos_j2);

		strcat(texto_final, aux);

		al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, texto_final);

		/*
		posicao_h_texto = 240;

		strcpy(texto_final, "Jogador 1: ");

		sprintf(aux, "%d", pontos_p1);

		strcat(texto_final, aux);

		strcat(texto_final, " - ");

		strcat(texto_final, "Jogador 2: ");

		strcpy(aux, "");

		sprintf(aux, "%d", pontos_p2);

		strcat(texto_final, aux);

		text_w = al_get_text_width(fonte_texto_grande, texto_final);
		posicao_w_texto = (MENU_W / 2) - (text_w / 2);

		al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, texto_final);
		*/
		// char tempo[1000];

		// sprintf(tempo, "%d", tempo_jogo);

		// strcpy(texto_final, tempo);

		// strcat(texto_final, " segundos!");

		// posicao_h_texto = 270;

		// text_w = al_get_text_width(fonte_texto_grande, texto_final);
		// posicao_w_texto = (MENU_W / 2) - (text_w / 2);

		// al_draw_text(fonte_texto_grande, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, texto_final);

		posicao_w_texto = 10;

		if (qtde_linhas_total == 1) {
			posicao_h_texto = MIN_ESCRITA_LINHAS;
		} else if (qtde_linhas_total > 1 && qtde_linhas_total < 10) {
			posicao_h_texto = MIN_ESCRITA_LINHAS + (qtde_linhas_total * 30);
		} else if (qtde_linhas_total >= 10) {
			posicao_h_texto = 550;
		}

		while ((c != EOF) && (counter < MAX_LINHAS_LIDAS)) {
			while (qtde_linhas_parcial < qtde_linhas_total - MAX_LINHAS_LIDAS) {
				c = fgetc(ler_partidas);

				if (c == '\n') {
					qtde_linhas_parcial++;
				}
			}

			// printf("Qtde linhas parcial: %d\r\n", qtde_linhas_parcial);
			// counter = 10;

			// printf("Esta na linha certa!\r\n");

			c = fgetc(ler_partidas);

			if (c != '\n') {
				linha[i] = c;
				i++;
			} else {
				int j = i;
				for (j; j < i + 5; j++) {
					linha[j] = ' ';
				}
				printf("Leu newline\r\n");
				// fgetc(ler_partidas);
				printf("Linha %d lida: %s\r\n", counter, linha);

				al_draw_text(fonte_texto_pequeno, COR_BRANCA, posicao_w_texto, posicao_h_texto, 0, linha);

				posicao_h_texto = posicao_h_texto - 30;

				strcpy(linha, "");

				i = 0;
				counter++;
			}
		}

		fclose(ler_partidas);
	}
}

void limpa_menu() {
	al_destroy_bitmap(seletor);
	al_destroy_bitmap(bg_menu);
	al_destroy_font(fonte_texto_pequeno);
	al_destroy_font(fonte_texto_grande);
	al_destroy_sample(vencedor);
}
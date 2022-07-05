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
//
#include "graficos.h"
//
#include "bolas.h"

posicao_bola posicao_nova_bola = CANTO_SUP_DIR;

void init_bolas(Bola bola[], int *indice_bolas) {

	*indice_bolas = 0;

	int i;

	for (i = 0; i < MAX_BOLAS; i++) {
		bola[i].bola_valida = 0;
		// printf("bola[%d]: %d\r\n", i, bola[i].bola_criada);
	}
}

void verifica_fundo_baixo_bola(Bola *b) {
	if ((b->x) < DIST_FUNDO_LIMITE) {
		b->dx = -b->dx;
	}
}

void verifica_fundo_alto_bola(Bola *b) {
	if ((b->x) > JOGO_W - b->d - DIST_FUNDO_LIMITE) {
		b->dx = -b->dx;
	}
}

void verifica_fundo_esquerdo_bola(Bola *b) {
	if ((b->y) < DIST_FUNDO_LIMITE) {
		b->dy = -b->dy;
	}
}

void verifica_fundo_direito_bola(Bola *b) {
	if ((b->y) > JOGO_H - b->d - DIST_FUNDO_LIMITE) {
		b->dy = -b->dy;
	}
}

void verifica_contato_jogador(Bola *b, Jogador *j) {
	if (b.x ==)
}

void cria_bola(Bola bolas[], int *indice_bolas) {

	float x, y;
	float dx, dy;

	if (*indice_bolas < MAX_BOLAS) {
		switch (posicao_nova_bola) {
			case CANTO_SUP_DIR:
				x = JOGO_W - DIAMETRO_BOLA - ESPESSURA_LINHA_QUADRA;
				y = 0 + DIAMETRO_BOLA + ESPESSURA_LINHA_QUADRA;
				dx = 5;
				dy = 12;

				posicao_nova_bola = CANTO_INF_DIR;
				break;

			case CANTO_INF_DIR:
				x = JOGO_W - DIAMETRO_BOLA - ESPESSURA_LINHA_QUADRA;
				y = JOGO_H - DIAMETRO_BOLA - ESPESSURA_LINHA_QUADRA;
				dx = 2;
				dy = 16;

				posicao_nova_bola = CANTO_INF_ESQ;
				break;

			case CANTO_INF_ESQ:
				x = 0 + DIAMETRO_BOLA + ESPESSURA_LINHA_QUADRA;
				y = JOGO_H - DIAMETRO_BOLA - ESPESSURA_LINHA_QUADRA;
				dx = 8;
				dy = 19;

				posicao_nova_bola = CANTO_SUP_ESQ;
				break;

			case CANTO_SUP_ESQ:
				x = 0 + DIAMETRO_BOLA + ESPESSURA_LINHA_QUADRA;
				y = 0 + DIAMETRO_BOLA + ESPESSURA_LINHA_QUADRA;
				dx = 15;
				dy = 3;

				posicao_nova_bola = CANTO_SUP_DIR;
				break;

			default:
				printf("Caiu default cria bola!\r\n");
				break;
		}

		bolas[*indice_bolas].x = x;
		bolas[*indice_bolas].y = y;
		bolas[*indice_bolas].dx = dx;
		bolas[*indice_bolas].dy = dy;
		bolas[*indice_bolas].d = DIAMETRO_BOLA;
		bolas[*indice_bolas].id = *indice_bolas;
		bolas[*indice_bolas].bola_valida = 1;

		*indice_bolas = *indice_bolas + 1;
	} else {
		printf("Limite de bolas!\n\r");
	}
}

void atualiza_posicao_bola(Bola *bola) {
	bola->x = bola->x + bola->dx;
	bola->y = bola->y + bola->dy;
}

void atualiza_bolas(Bola bolas[], int indice_bolas) {
	int i = 0;

	for (i; i < indice_bolas; i++) {
		if (bolas[i].bola_valida) {
			atualiza_posicao_bola(&bolas[i]);
		}
	}
}

void desenha_bola(Bola bolas[], int indice_bolas) {
	int i = 0;
	for (i; i < indice_bolas; i++) {
		al_draw_filled_circle(bolas[i].x, bolas[i].y, bolas[i].d, COR_BRANCA);
	}
}

void verifica_posicao_bola(Bola bola[], int indice_bolas) {
	int i = 0;

	for (i; i < indice_bolas; i++) {
		verifica_fundo_esquerdo_bola(&bola[i]);
		verifica_fundo_direito_bola(&bola[i]);
		verifica_fundo_alto_bola(&bola[i]);
		verifica_fundo_baixo_bola(&bola[i]);
	}
}
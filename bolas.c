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

ALLEGRO_TIMER *timer_bola = NULL;
// Bola bolas[MAX_BOLAS];

int teste = 10;

void init_bolas(Bola bola[], int *indice_bolas) {

	timer_bola = al_create_timer(1);

	al_start_timer(timer_bola);

	*indice_bolas = 0;

	int i;

	for (i = 0; i < MAX_BOLAS; i++) {
		bola[i].bola_criada = 0;
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

void cria_bola(Bola bolas[], int *indice_bolas) {
	// int i = *indice_bolas;

	// for (i; i < MAX_BOLAS; i++) {
	// if (al_get_timer_count(timer_bola) == 2) {
	bolas[*indice_bolas].x = teste;
	bolas[*indice_bolas].y = teste + 10;
	bolas[*indice_bolas].dx = 10;
	bolas[*indice_bolas].dy = 15;
	bolas[*indice_bolas].d = 5;
	bolas[*indice_bolas].id = *indice_bolas;
	bolas[*indice_bolas].bola_criada = 1;

	*indice_bolas = *indice_bolas + 1;

	teste = teste + 10;

	// al_set_timer_count(timer_bola, 0);
	// }

	// printf("Indice: %d\r\n", *indice_bolas);
	// }
}

void atualiza_posicao_bola(Bola *bola) {
	bola->x = bola->x + bola->dx;
	bola->y = bola->y + bola->dy;
}

void atualiza_bolas(Bola bolas[], int indice_bolas) {
	int i = 0;

	for (i; i < indice_bolas; i++) {
		if (bolas[i].bola_criada) {
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
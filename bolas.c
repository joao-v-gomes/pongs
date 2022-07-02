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

uint8_t indice_bolas;

void init_bolas(Bola *bolas[]) {

	timer_bola = al_create_timer(1);

	al_start_timer(timer_bola);

	indice_bolas = 0;

	int i;

	for (i = 0; i < MAX_BOLAS; i++) {
		bolas[i]->bola_criada = false;
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

void cria_bola(Bola *bolas[]) {
	bolas[indice_bolas]->x = 700;
	bolas[indice_bolas]->y = 50;
	bolas[indice_bolas]->dx = 10;
	bolas[indice_bolas]->dy = 15;
	bolas[indice_bolas]->d = 5;
	bolas[indice_bolas]->id = 3;
	bolas[indice_bolas]->bola_criada = true;

	indice_bolas++;
}

void atualiza_posicao_bola(Bola *bola) {
	bola->x = bola->x + bola->dx;
	bola->y = bola->y + bola->dy;
}

void atualiza_bolas(Bola bolas[]) {
	int i = 0;

	for (i; i < MAX_BOLAS; i++) {
		if (bolas[i].bola_criada == true) {
			atualiza_posicao_bola(&bolas[i]);
		}
	}
}

void desenha_bola(Bola bola) {
	al_draw_filled_circle(bola.x, bola.y, bola.d, COR_BRANCA);
}

void verifica_posicao_bola(Bola *bola) {
	verifica_fundo_esquerdo_bola(bola);
	verifica_fundo_direito_bola(bola);
	verifica_fundo_alto_bola(bola);
	verifica_fundo_baixo_bola(bola);
}
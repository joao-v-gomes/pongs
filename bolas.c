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

void init_bola(Bola *bola) {
	bola->x = 700;
	bola->y = 50;
	bola->dx = 10;
	bola->dy = 15;
	bola->d = 5;
	bola->id = 3;
}

void atualiza_posicao_bola(Bola *bola) {
	bola->x = bola->x + bola->dx;
	bola->y = bola->y + bola->dy;
}

void atualiza_bolas() {
}

void desenha_bola(Bola bola_nova) {
	al_draw_filled_circle(bola_nova.x, bola_nova.y, bola_nova.d, COR_BRANCA);
}

void verifica_posicao_bola(Bola *bola) {
	verifica_fundo_esquerdo_bola(bola);
	verifica_fundo_direito_bola(bola);
	verifica_fundo_alto_bola(bola);
	verifica_fundo_baixo_bola(bola);
}
#ifndef BOLAS_H
#define BOLAS_H

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

#define DIAMETRO_BOLA	 5
#define MAX_BOLAS		 2
#define TEMPO_SOLTA_BOLA 2

typedef enum {
	CANTO_SUP_DIR,
	CANTO_INF_DIR,
	CANTO_INF_ESQ,
	CANTO_SUP_ESQ

} posicao_bola;

typedef struct Bola {
	float x, y;
	float dx, dy;
	uint8_t d;
	uint8_t id;
	uint8_t bola_valida;

} Bola;

#endif
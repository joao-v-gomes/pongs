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

#define MAX_BOLAS 20

typedef struct {
	float x, y;
	float dx, dy;
	uint8_t d;
	uint8_t id;
	bool bola_criada;

} Bola;

#endif
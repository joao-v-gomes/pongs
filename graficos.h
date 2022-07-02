#ifndef GRAFICOS_H
#define GRAFICOS_H
#include "graficos.h"
//
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_image.h"
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

#define MENU_W 600
#define MENU_H 600

#define SELETOR_W 15
#define SELETOR_H 50

#define COR_BRANCA			   al_map_rgb(255, 255, 255)
#define ESPESSURA_LINHA_QUADRA 3
#define DIST_FUNDO_LIMITE	   (ESPESSURA_LINHA_QUADRA * 2)

void init_graficos();
void desenha_menu(ALLEGRO_DISPLAY *display, int *counter);
void desenha_quadra();
void desenha_escolha_jogador(ALLEGRO_DISPLAY *display);
void desenha_escolha_jogador_um(ALLEGRO_DISPLAY *display, int *counter);
void desenha_escolha_jogador_dois(ALLEGRO_DISPLAY *display, int *counter2);
void desenha_tipo_jogador1(ALLEGRO_DISPLAY *display);
void desenha_tipo_jogador2(ALLEGRO_DISPLAY *display);
void desenha_tipo_jogador3(ALLEGRO_DISPLAY *display);

#endif
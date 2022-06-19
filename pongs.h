#ifndef PONGS_H
#define PONGS_H

#include "jogadores.h"

const float FPS = 50;  

const int SCREEN_H = 960;
const int SCREEN_W = 441;

const int SCREEN_H_MENU = 675;
const int SCREEN_W_MENU = 1200;


void desenha_quadra();
void desenha_menu(ALLEGRO_FONT *size_32);
void verifica_tecla_movimentacao(ALLEGRO_EVENT ev, Jogador *p1, Jogador *p2);
void verifica_esc(int *playing, ALLEGRO_EVENT ev);

#endif
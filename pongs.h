#ifndef PONGS_H
#define PONGS_H

#include "jogadores.h"

void desenha_quadra();
void desenha_menu(ALLEGRO_FONT *size_32);
void verifica_tecla_movimentacao(ALLEGRO_EVENT ev, Jogador *p1, Jogador *p2);
void verifica_esc(int *playing, ALLEGRO_EVENT ev);

#endif
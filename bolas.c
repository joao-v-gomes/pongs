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

void init_bolas(Bola bola[], int *contador_bolas) {

	*contador_bolas = 0;

	posicao_nova_bola = CANTO_SUP_DIR;

	int i = 0;

	for (i; i < MAX_BOLAS; i++) {
		bola[i].bola_valida = 0;
		// printf("bola[%d]: %d\r\n", i, bola[i].bola_criada);
	}
}

void verifica_fundo_baixo_bola(Bola *b, int *contador_bolas, int *pontos2) {
	if ((b->x) < DIST_FUNDO_LIMITE) {
		// b->dx = -b->dx;

		b->bola_valida = 0;

		*pontos2 = *pontos2 + 1;

		*contador_bolas = *contador_bolas - 1;

		printf("Bola %d invalida\r\n", b->id);
	}
}

void verifica_fundo_alto_bola(Bola *b, int *contador_bolas, int *pontos1, int tipo_jogo) {
	if ((b->x) > JOGO_W - b->d - DIST_FUNDO_LIMITE) {
		if (tipo_jogo == UM_JOG) {
			b->dx = -b->dx;
		} else if (tipo_jogo == DOIS_JOG) {

			// b->dx = -b->dx;

			b->bola_valida = 0;

			*pontos1 = *pontos1 + 1;

			*contador_bolas = *contador_bolas - 1;

			printf("Bola %d invalida\r\n", b->id);
		}
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

void verifica_contato_jogador(Bola *b, Jogador *j, bool pode_rebater) {

	if (pode_rebater == true) {
		if (j->id == 1) {
			if (((b->x + b->d) >= j->x - b->d) && ((b->x + b->d) <= (j->x + j->w + b->d)) && ((b->y + b->d) >= j->y - b->d) && ((b->y + b->d) <= (j->y + j->h + b->d))) {
				if ((b->x + b->d - b->dx) >= j->x + j->w) {
					b->x = j->x + j->w + b->d;
					b->dx = -b->dx;
				}
				if ((b->y + b->d - b->dy) <= j->y) {
					b->y = j->y + b->d;
					b->dy = -b->dy;
				}
				if ((b->y + b->d - b->dy) >= j->y + j->h) {
					b->y = j->y + j->h + b->d;
					b->dy = -b->dy;
				}
			}
		} else if (j->id == 2) {
			if (((b->x + b->d) >= j->x - b->d) && ((b->x + b->d) <= (j->x + j->w + b->d)) && ((b->y + b->d) >= j->y - b->d) && ((b->y + b->d) <= (j->y + j->h + b->d))) {
				if (((b->x + b->d - b->dx) <= j->x - b->d)) {
					b->x = j->x - b->d;
					b->dx = -b->dx;
				}
				if ((b->y + b->d - b->dy) <= j->y) {
					b->y = j->y + b->d;
					b->dy = -b->dy;
				}
				if ((b->y + b->d - b->dy) >= j->y + j->h) {
					b->y = j->y + j->h + b->d;
					b->dy = -b->dy;
				}
			}
		}
	}
}

void cria_bola(Bola bolas[], int *contador_bolas) {

	float x, y;
	float dx, dy;

	int indice_bolas = 0;

	int i = 0;

	int valor_dx = MIN_DX_BOLA + rand() % MAX_DX_BOLA;
	int valor_dy = MIN_DY_BOLA + rand() % MAX_DY_BOLA;

	for (i; i < MAX_BOLAS; i++) {
		if (bolas[i].bola_valida == 0) {
			indice_bolas = i;
			i = MAX_BOLAS;
		}
	}

	if (*contador_bolas < MAX_BOLAS) {

		int diametro_bola = 0;

		bolas[indice_bolas].d = DIAMETRO_BOLA_MIN + rand() % DIAMETRO_BOLA_MAX;
		bolas[indice_bolas].id = indice_bolas;
		bolas[indice_bolas].bola_valida = 1;

		diametro_bola = bolas[indice_bolas].d;

		switch (posicao_nova_bola) {
			case CANTO_SUP_DIR:
				x = JOGO_W - diametro_bola - DIST_FUNDO_LIMITE;
				y = 0 + diametro_bola + DIST_FUNDO_LIMITE;
				dx = -valor_dx;
				dy = valor_dy;

				posicao_nova_bola = CANTO_INF_DIR;
				break;

			case CANTO_INF_DIR:
				x = JOGO_W - diametro_bola - DIST_FUNDO_LIMITE;
				y = JOGO_H - diametro_bola - DIST_FUNDO_LIMITE;
				dx = -valor_dx;
				dy = -valor_dy;

				posicao_nova_bola = CANTO_INF_ESQ;
				break;

			case CANTO_INF_ESQ:
				x = 0 + diametro_bola + DIST_FUNDO_LIMITE;
				y = JOGO_H - diametro_bola - DIST_FUNDO_LIMITE;
				dx = valor_dx;
				dy = -valor_dy;

				posicao_nova_bola = CANTO_SUP_ESQ;
				break;

			case CANTO_SUP_ESQ:
				x = 0 + diametro_bola + DIST_FUNDO_LIMITE;
				y = 0 + diametro_bola + DIST_FUNDO_LIMITE;
				dx = valor_dx;
				dy = valor_dy;

				posicao_nova_bola = CANTO_SUP_DIR;
				break;

			default:
				printf("Caiu default cria bola!\r\n");
				break;
		}

		bolas[indice_bolas].x = x;
		bolas[indice_bolas].y = y;
		bolas[indice_bolas].dx = dx;
		bolas[indice_bolas].dy = dy;

		*contador_bolas = *contador_bolas + 1;

		printf("Bola %d criada\r\n", indice_bolas);

	} else {
		printf("Limite de bolas!\n\r");
	}
}

void atualiza_posicao_bola(Bola *bola) {
	bola->x = bola->x + bola->dx;
	bola->y = bola->y + bola->dy;
}

void atualiza_bolas(Bola bolas[]) {
	int i = 0;

	for (i; i < MAX_BOLAS; i++) {
		if (bolas[i].bola_valida) {
			atualiza_posicao_bola(&bolas[i]);
		}
	}
}

void desenha_bola(Bola bolas[]) {
	int i = 0;
	for (i; i < MAX_BOLAS; i++) {
		if (bolas[i].bola_valida) {
			al_draw_filled_circle(bolas[i].x, bolas[i].y, bolas[i].d, COR_BRANCA);
		}
	}
}

void verifica_posicao_bola_quadra(Bola bola[], int *contador_bolas, int *pontos1, int *pontos2, int tipo_jogo) {
	int i = 0;
	// printf("Foi verificar2!\r\n");
	for (i; i < MAX_BOLAS; i++) {
		if (bola[i].bola_valida) {
			verifica_fundo_esquerdo_bola(&bola[i]);
			verifica_fundo_direito_bola(&bola[i]);
			verifica_fundo_alto_bola(&bola[i], contador_bolas, pontos1, tipo_jogo);
			verifica_fundo_baixo_bola(&bola[i], contador_bolas, pontos2);
			// verifica_contato_jogador(&bola[i], j);
		}
	}
}

void verifica_posicao_bola_jogador(Bola bola[], Jogador *j, bool pode_rebater) {
	int i = 0;
	// printf("Foi verificar2!\r\n");
	for (i; i < MAX_BOLAS; i++) {
		if (bola[i].bola_valida) {
			verifica_contato_jogador(&bola[i], j, pode_rebater);
		}
	}
}

void verifica_posicao_bola_jogadores(Bola bola[], Jogador *j1, Jogador *j2, bool pode_rebater_j1, bool pode_rebater_j2) {
	verifica_posicao_bola_jogador(bola, j1, pode_rebater_j1);
	verifica_posicao_bola_jogador(bola, j2, pode_rebater_j2);
}
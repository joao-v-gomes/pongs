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

void verifica_posicoes_jogadores(Jogador *p1, Jogador *p2) {
	verifica_posicao(p1);
	verifica_posicao(p2);
}

void verifica_posicao(Jogador *p) {

	if (p->id == 1) {
		// Verifica meio
		if ((p->y) > JOGO_H / 2 + 4) {
			// tudo certo
			//  p->cima = 0;
		} else {
			// printf("deu merda\r\n");
			p->cima = 0;
		}

		// Verifica fundo
		if ((p->y) < JOGO_H - ALTURA_JOGADOR_1 - 7) {

		} else {
			p->baixo = 0;
		}

		// Verifica esq
		if ((p->x) > 0 + 6) {

		} else {
			p->esq = 0;
		}

		// Verifica dir
		if ((p->x) < JOGO_W - LARGURA_JOGADOR_1 - 7) {

		} else {
			p->dir = 0;
		}
	} else {
		// Verifica meio
		if ((p->y) <= JOGO_H / 2 - ALTURA_JOGADOR_1 - 5) {
			// tudo certo
			//  p->cima = 0;
		} else {
			// printf("deu merda\r\n");
			p->baixo = 0;
		}

		// Verifica topo
		if ((p->y) > 0 + 5) {

		} else {
			p->cima = 0;
		}

		// Verifica esq
		if ((p->x) > 0 + 6) {

		} else {
			p->esq = 0;
		}

		// Verifica dir
		if ((p->x) < JOGO_W - LARGURA_JOGADOR_1 - 7) {

		} else {
			p->dir = 0;
		}
	}
}

void desenha_jogadores(Jogador p1, Jogador p2) {
	desenha_jogador(p1);
	desenha_jogador(p2);
}

void desenha_jogador(Jogador p) {

	al_draw_filled_rectangle(p.x, p.y, p.x + p.w, p.y + p.h, p.cor);

	// if (p.id == 2) {
	// 	printf("pos x: %.1f \n pos y: %.1f", p.x, p.y);
	// }
}

void init_jogador(Jogador *p, fsm_escolha_jogadores opcao_jogador) {

	switch (opcao_jogador) {
		case 0:
			p->w = ALTURA_JOGADOR_1;
			p->h = LARGURA_JOGADOR_1;
			p->vel = VEL_JOGADOR_1;
			p->cor = COR_JOGADOR_1;
			break;

		case 1:
			p->w = ALTURA_JOGADOR_2;
			p->h = LARGURA_JOGADOR_2;
			p->vel = VEL_JOGADOR_2;
			p->cor = COR_JOGADOR_2;
			break;

		case 2:
			p->w = ALTURA_JOGADOR_3;
			p->h = LARGURA_JOGADOR_3;
			p->vel = VEL_JOGADOR_3;
			p->cor = COR_JOGADOR_3;
			break;

		default:
			printf("Entrou default initjogador!");
			break;
	}

	p->y = JOGO_H / 2 - p->h / 2;
	p->dir = 0;
	p->esq = 0;
	p->cima = 0;
	p->baixo = 0;
}

void init_jogador1(Jogador *p1, fsm_escolha_jogadores opcao_jogador) {
	init_jogador(p1, opcao_jogador);
	p1->x = 0 + DIST_FUNDO - p1->w;
	p1->id = 1;
}

void init_jogador2(Jogador *p2, fsm_escolha_jogadores opcao_jogador) {
	init_jogador(p2, opcao_jogador);
	p2->x = JOGO_W - DIST_FUNDO;
	p2->id = 2;
}

void atualiza_jogadores(Jogador *p1, Jogador *p2) {
	atualiza_jogador(p1);
	atualiza_jogador(p2);
}

void atualiza_jogador(Jogador *p) {

	p->x = p->x + p->dir * p->vel - p->esq * p->vel;
	p->y = p->y + p->baixo * p->vel - p->cima * p->vel;
}

void printa_info_jogador(Jogador p) {
	printf(" Jogador: %d\r\n", p.id);
	printf(" Altura: %.2f\r\n", p.w);
	printf(" Largura: %.2f\r\n", p.h);
}
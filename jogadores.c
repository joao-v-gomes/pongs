#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "pongs.h"
#include "jogadores.h"

extern const int SCREEN_H;
extern const int SCREEN_W;

//JOGADOR:
int DIST_FUNDO = 50;
int ALTURA_JOGADOR = 30;
int LARGURA_JOGADOR = 100;
float VEL_JOGADOR = 3;


void verifica_posicoes_jogadores(Jogador *p1, Jogador *p2){
	verifica_posicao(p1);
	verifica_posicao(p2);
}

void verifica_posicao(Jogador *p){

	if(p->id == 1){
		//Verifica meio
		if((p->y) > SCREEN_H/2 + 4){
			//tudo certo
			// p->cima = 0;
		}
		else{
			// printf("deu merda\r\n");
			p->cima = 0;
		}

		//Verifica fundo
		if((p->y) < SCREEN_H-ALTURA_JOGADOR-7){

		}
		else{
			p->baixo = 0;
		}

		//Verifica esq
		if((p->x) > 0+6){

		}
		else{
			p->esq = 0;
		}

		//Verifica dir
		if((p->x) < SCREEN_W-LARGURA_JOGADOR-7){

		}
		else{
			p->dir = 0;
		}
	}
	else{
		//Verifica meio
		if((p->y) <= SCREEN_H/2 - ALTURA_JOGADOR - 5){
			//tudo certo
			// p->cima = 0;
		}
		else{
			// printf("deu merda\r\n");
			p->baixo = 0;
		}

		//Verifica topo
		if((p->y) > 0+5){

		}
		else{
			p->cima = 0;
		}

		//Verifica esq
		if((p->x) > 0+6){

		}
		else{
			p->esq = 0;
		}

		//Verifica dir
		if((p->x) < SCREEN_W-LARGURA_JOGADOR-7){

		}
		else{
			p->dir = 0;
		}
	}
}

void desenha_jogadores(Jogador p1, Jogador p2){
	desenha_jogador(p1);
	desenha_jogador(p2);
}

void desenha_jogador(Jogador p){

	al_draw_filled_rectangle(p.x, p.y, p.x + p.w, p.y + p.h, p.cor );

	if(p.id == 2){
		printf("pos x: %.1f \n pos y: %.1f",p.x,p.y);
	}

}

void init_jogador(Jogador *p) {
	p->h = ALTURA_JOGADOR;
	p->w = LARGURA_JOGADOR;
	p->x = SCREEN_W/2 - p->w/2;
	p->dir = 0;
	p->esq = 0;
	p->cima = 0;
	p->baixo = 0;
	p->vel = VEL_JOGADOR;

}

void init_jogador1(Jogador *p1) {
	init_jogador(p1);
	p1->y = SCREEN_H - DIST_FUNDO - p1->h;
	p1->cor = al_map_rgb(155, 0, 0);
	p1->id = 1;

}

void init_jogador2(Jogador *p2) {
	init_jogador(p2);
	p2->y = 0 + DIST_FUNDO;
	p2->cor = al_map_rgb(0, 0, 155);
	p2->id = 2;

}

void atualiza_jogadores(Jogador *p1, Jogador *p2){
	atualiza_jogador(p1);
	atualiza_jogador(p2);
}

void atualiza_jogador(Jogador *p) {

	p->x = p->x + p->dir*p->vel - p->esq*p->vel;
	p->y = p->y + p->baixo*p->vel - p->cima*p->vel;

}
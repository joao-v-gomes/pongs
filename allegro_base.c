#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "pongs.h"



void verifica_posicao(Jogador *p){
	if((p->y) <= SCREEN_H/2 + 2){
		//tudo certo
	}
	else{
		printf("deu merda\r\n");
	}
}

void desenhaQuadra() {
	
	al_clear_to_color(al_map_rgb(0, 155, 0));
	al_draw_line(0, SCREEN_H/2, SCREEN_W, SCREEN_H/2, al_map_rgb(255,255,255), 4);
	
}

void desenhaJogador(Jogador p) {

	al_draw_filled_rectangle(p.x, p.y, p.x + p.w, p.y + p.h, p.cor );

}


void initJogador(Jogador *p) {
	p->h = ALTURA_JOGADOR;
	p->w = LARGURA_JOGADOR;
	p->x = SCREEN_W/2 - p->w/2;
	p->dir = 0;
	p->esq = 0;
	p->cima = 0;
	p->baixo = 0;
	p->vel = VEL_JOGADOR;

}

void initJogador1(Jogador *p1) {
	initJogador(p1);
	p1->y = SCREEN_H - DIST_FUNDO - p1->h;
	p1->cor = al_map_rgb(155, 0, 0);
	p1->id = 1;

}


void atualizaJogador(Jogador *p) {

	p->x = p->x + p->dir*p->vel - p->esq*p->vel;
	p->y = p->y + p->baixo*p->vel - p->cima*p->vel;

}



int main(int argc, char **argv){
	
	int i, j;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
   
	//----------------------- rotinas de inicializacao ---------------------------------------
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}
   
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
	//instala o mouse
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize mouse!\n");
		return -1;
	}

	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    ALLEGRO_FONT *size_32 = al_load_font("arial.ttf", 32, 1);   
	if(size_32 == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
   


	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	// //registra na fila os eventos de mouse (ex: clicar em um botao do mouse)
	// al_register_event_source(event_queue, al_get_mouse_event_source());  	


	//inicia o temporizador
	al_start_timer(timer);
	

	Jogador p1;
	initJogador1(&p1);


	// FONT_32 = al_load_font("arial.ttf", 32, 1);

	int playing = 1;
	while(playing) {
		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {


			desenhaQuadra();
			atualizaJogador(&p1);
			desenhaJogador(p1);

			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
			
			if(al_get_timer_count(timer)%(int)FPS == 0)
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		//se o tipo de evento for um clique de mouse
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("\nmouse clicado em: %d, %d", ev.mouse.x, ev.mouse.y);
		}
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			//imprime qual tecla foi
			// printf("\ncodigo tecla: %d", ev.keyboard.keycode);

			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				playing = 0;
			}

			switch(ev.keyboard.keycode) {
			//se a tecla for o W
				case ALLEGRO_KEY_W:
					p1.cima = 1;
				break;
		
				case ALLEGRO_KEY_S:
					p1.baixo = 1;
				break;
		
				case ALLEGRO_KEY_A:
					p1.esq = 1;
				break;
		
				case ALLEGRO_KEY_D:
					p1.dir = 1;
				break;
			
			}


			//imprime qual tecla foi
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {

			switch(ev.keyboard.keycode) {
			//se a tecla for o W
				case ALLEGRO_KEY_W:
					p1.cima = 0;
				break;
		
				case ALLEGRO_KEY_S:
					p1.baixo = 0;
				break;
		
				case ALLEGRO_KEY_A:
					p1.esq = 0;
				break;
		
				case ALLEGRO_KEY_D:
					p1.dir = 0;
				break;


			}
		}		
			

	} //fim do while
    
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

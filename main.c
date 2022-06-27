#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_image.h"
#include "pongs.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//
#include "graficos.h"
//
#include "pongs.h"
//
#include "jogadores.h"

int main(int argc, char **argv) {

	int i, j;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	//----------------------- rotinas de inicializacao ---------------------------------------

	// inicializa o Allegro
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	// inicializa o módulo de primitivas do Allegro
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize primitives!\n");
		return -1;
	}

	// inicializa o modulo que permite carregar imagens no jogo
	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}

	// cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	// cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_INIT, SCREEN_INIT);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	// instala o teclado
	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	// instala o mouse
	if (!al_install_mouse()) {
		fprintf(stderr, "failed to initialize mouse!\n");
		return -1;
	}

	// inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	// inicializa o modulo allegro que entende arquivos tff de fontes
	if (!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}

	// carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
	// ALLEGRO_FONT *fonte_texto = al_load_font("data/font/UbuntuMono-RI.ttf", 32, 1);
	// if (fonte_texto == NULL) {
	// 	fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	// }

	// cria a fila de eventos
	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(2);

	// registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	// registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	// registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	// //registra na fila os eventos de mouse (ex: clicar em um botao do mouse)
	al_register_event_source(event_queue, al_get_mouse_event_source());

	// inicia o temporizador
	al_start_timer(timer);

	Jogador p1, p2;
	init_jogador1(&p1);
	init_jogador2(&p2);

	// Icone da janela
	ALLEGRO_BITMAP *icone_pong = al_load_bitmap("data/img/pong2.bmp");
	al_set_window_title(display, "PongS");
	al_set_display_icon(display, icone_pong);

	// Audios
	// ALLEGRO_SAMPLE *intro = NULL;
	// ALLEGRO_SAMPLE *move_menu = NULL;

	// intro = al_load_sample("data/audio/words_of_a_madman.wav");
	// intro = al_load_sample("data/audio/top-gear-3.wav");

	// al_play_sample(intro, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

	// bool foi_menu = false;
	// bool abre_jogo = false;

	// Prepara o desenho do menu
	// ALLEGRO_BITMAP *bg_menu = al_load_bitmap("data/img/menu-alt-2.bmp");

	// int imageH = MENU_H;
	// int imageW = MENU_W;

	// imageH = al_get_bitmap_height(bg_menu);
	// imageW = al_get_bitmap_width(bg_menu);

	al_resize_display(display, MENU_W, MENU_H);

	volatile int counter = 0;

	fsm_menu state = INIT_MENU;
	fsm_menu opcao_menu = INIT_MENU;
	fsm_escolha_jogadores opcao_jogador1 = INIT_ESCOLHA_JOGADOR;
	fsm_escolha_jogadores opcao_jogador2 = INIT_ESCOLHA_JOGADOR;

	int playing = 1;

	// state = ESCOLHE_UM_JOGADOR;

	init_pongs();
	init_graficos();

	while (playing) {
		ALLEGRO_EVENT ev;
		// espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		// se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			switch (state) {
				case INIT_MENU:
					state = MENU;
					printf("Foi menu\r\n");
					break;
				case MENU:
					desenha_menu(display, &counter);

					switch (opcao_menu) {
						case UM_JOGADOR:
							state = ESCOLHE_UM_JOGADOR;
							counter = 0;
							printf("Foi um jogador\r\n");
							break;
						case DOIS_JOGADORES:
							state = ESCOLHE_DOIS_JOGADORES;
							printf("Foi dois jogadores\r\n");
							break;
						case SAIR:
							state = SAIR;
							break;

						default:
							break;
					}
					break;
				case ESCOLHE_UM_JOGADOR:
					escolha_um_jogador(display, &opcao_jogador1, &counter);
					break;
				case ESCOLHE_DOIS_JOGADORES:
					break;
				case JOGO_UM_JOGADOR:
					break;
				case JOGO_DOIS_JOGADORES:
					break;
				case SAIR:
					printf("Foi sair\r\n");
					// limpa_menu(bg_menu);
					playing = 0;
					break;

				default:
					break;
			}

			// if (foi_menu == false) {
			// 	// desenha_menu(fonte_texto);

			// 	abre_jogo = true;
			// } else {
			// 	if (abre_jogo == true) {
			// 		al_resize_display(display, SCREEN_W, SCREEN_H);
			// 	}

			// 	desenha_quadra();
			// 	verifica_posicoes_jogadores(&p1, &p2);
			// 	atualiza_jogadores(&p1, &p2);
			// 	desenha_jogadores(p1, p2);
			// }

			// atualiza a tela (quando houver algo para mostrar)
			al_flip_display();

			if (al_get_timer_count(timer) % (int)FPS == 0)
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer) / FPS));
		}
		// se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		// se o tipo de evento for um clique de mouse
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("\nmouse clicado em: %d, %d", ev.mouse.x, ev.mouse.y);
		} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP) {

			verifica_tecla_movimentacao(ev, &p1, &p2);

			if (state == MENU) {
				verifica_selecao_menu(ev, &counter, &state, &opcao_menu);
				verifica_som_menu(ev, &counter);
			} else if (state == ESCOLHE_UM_JOGADOR || state == ESCOLHE_DOIS_JOGADORES) {
				verifica_selecao_jogador(ev, &counter);
				verifica_som_menu(ev, &counter);
			}

			verifica_esc(ev, &playing);

			// if (ev.type == ALLEGRO_EVENT_KEY_UP) {

			// } else {
			// }
			// imprime qual tecla foi
			//  printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		}

	} // fim do while

	// procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)

	// al_destroy_bitmap(bg_menu);
	al_destroy_bitmap(icone_pong);
	// al_destroy_font(fonte_texto);
	// al_destroy_sample(intro);
	// al_destroy_sample(move_menu);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

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
	ALLEGRO_FONT *fonte_texto = al_load_font("data/font/UbuntuMono-RI.ttf", 32, 1);
	if (fonte_texto == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}

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
	ALLEGRO_SAMPLE *intro = NULL;
	ALLEGRO_SAMPLE *move_menu = NULL;

	// sample = al_load_sample("words_of_a_madman.wav");
	intro = al_load_sample("data/audio/top-gear-3.wav");
	move_menu = al_load_sample("data/audio/menu-navigate-03.wav");

	al_play_sample(intro, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

	bool foi_menu = false;
	bool abre_jogo = false;

	// Prepara o desenho do menu
	ALLEGRO_BITMAP *bg_menu = al_load_bitmap("data/img/menu-alt-2.bmp");

	int imageH = 0;
	int imageW = 0;

	imageH = al_get_bitmap_height(bg_menu);
	imageW = al_get_bitmap_width(bg_menu);

	al_resize_display(display, imageW, imageH);

	int8_t counter = 0;

	fsm_menu state = INIT;
	fsm_menu opcao = INIT;

	int playing = 1;
	while (playing) {
		ALLEGRO_EVENT ev;
		// espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		// se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			switch (state) {
				case INIT:
					state = MENU;
					printf("Foi menu\r\n");
					break;
				case MENU:
					desenha_menu(display, fonte_texto, bg_menu, counter);

					switch (opcao) {
						case UM_JOGADOR:
							state = ESCOLHE_UM_JOGADOR;
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
					break;
				case ESCOLHE_DOIS_JOGADORES:
					break;
				case JOGO_UM_JOGADOR:
					break;
				case JOGO_DOIS_JOGADORES:
					break;
				case SAIR:
					printf("Foi sair\r\n");
					limpa_menu(bg_menu);
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

			verifica_esc(&playing, ev);

			verifica_tecla_movimentacao(ev, &p1, &p2);

			// if (ev.keyboard.keycode == ALLEGRO_KEY_H) {
			// 	al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			// 	foi_menu = true;
			// }
			if (ev.type == ALLEGRO_EVENT_KEY_UP) {

			} else {
				if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
					al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					counter--;

					if (counter < 0) {
						counter = 2;
					}
				}

				if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
					al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					counter++;

					if (counter > 2) {
						counter = 0;
					}
				}

				if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
					if (state == MENU) {
						switch (counter) {
							case 0:
								opcao = UM_JOGADOR;
								break;
							case 1:
								opcao = DOIS_JOGADORES;
								break;
							case 2:
								opcao = SAIR;
								break;

							default:
								break;
						}
						// opcao = counter;
					}
				}
			}
			// imprime qual tecla foi
			//  printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		}

	} // fim do while

	// procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)

	// al_destroy_bitmap(bg_menu);
	al_destroy_bitmap(icone_pong);
	al_destroy_font(fonte_texto);
	al_destroy_sample(intro);
	al_destroy_sample(move_menu);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

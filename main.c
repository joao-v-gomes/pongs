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
#include <time.h>
//
#include "graficos.h"
//
#include "jogadores.h"
//
#include "pongs.h"
//
#include "bolas.h"

int main(int argc, char **argv) {

	srand(time(NULL));

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

	// cria uma tela com dimensoes de JOGO_W, JOGO_H pixels
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

	// cria a fila de eventos
	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(4);

	// registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	// registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	// registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	// //registra na fila os eventos de mouse (ex: clicar em um botao do mouse)
	// al_register_event_source(event_queue, al_get_mouse_event_source());

	// inicia o temporizador
	al_start_timer(timer);

	int playing = 1;

	// Icone da janela
	ALLEGRO_BITMAP *icone_pong = al_load_bitmap("data/img/pong2.bmp");
	al_set_window_title(display, "PongS");
	al_set_display_icon(display, icone_pong);

	al_resize_display(display, MENU_W, MENU_H);

	ALLEGRO_TIMER *timer_bola = NULL;
	ALLEGRO_TIMER *timer_jogo_um_jog = NULL;

	// Sobre os jogadores
	Jogador p1, p2;
	fsm_escolha_jogadores opcao_jogador1;
	fsm_escolha_jogadores opcao_jogador2;

	int pontos_p1;
	int pontos_p2;

	bool pode_rebater_j1 = false;
	bool pode_rebater_j2 = false;

	// Sobre as bolas
	Bola bolas[MAX_BOLAS];

	int contador_bolas;

	// Sobre o menu e jogo
	fsm_menu state = INIT_MENU;

	int counter;
	int counter2;

	int tempo_jogo = 0;
	int tipo_jogo = 0;

	while (playing) {
		ALLEGRO_EVENT ev;
		// espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		// se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			switch (state) {
				case INIT_MENU:

					timer_bola = al_create_timer(1);
					timer_jogo_um_jog = al_create_timer(1);

					al_start_timer(timer_bola);
					al_start_timer(timer_jogo_um_jog);

					// init_bolas(&bolas, &contador_bolas);

					init_pongs();
					init_graficos();

					state = INIT_VAR_PONGS;
					printf("Foi init var\r\n");
					break;
				case INIT_VAR_PONGS:
					init_var_pongs(&contador_bolas, &pontos_p1, &pontos_p2, &counter, &counter2, &opcao_jogador1, &opcao_jogador2, &tempo_jogo, &tipo_jogo);
					init_bolas(&bolas, &contador_bolas);
					state = MENU;
					printf("Foi menu\r\n");
					break;
				case MENU:
					// Printa e atualiza a movimentacao no menu inicial
					// printf("Foi menu\r\n");
					desenha_menu(display, &counter);
					break;
				case AJUDA:
					// printf("Foi ajuda\r\n");
					desenha_ajuda();
					break;
				case ESCOLHE_UM_JOGADOR:
					// Printa e atualiza a movimentacao no menu de jogadores para um jogador
					desenha_escolha_jogador(display);
					desenha_escolha_jogador_um(display, &counter);
					break;
				case ESCOLHE_DOIS_JOGADORES:
					// Printa e atualiza a movimentacao no menu de jogadores para dois jogadores
					desenha_escolha_jogador(display);
					desenha_escolha_jogador_um(display, &counter);
					desenha_escolha_jogador_dois(display, &counter2);
					break;
				case CARREGA_UM_JOGADOR:
					// Faz o init do jogador1 utilizando o tipo de jogador escolhido
					printf("Foi carrega 1 jogador1\r\n");
					// carrega_jogador_1(&opcao_jogador1);

					tipo_jogo = UM_JOG;

					init_jogador1(&p1, opcao_jogador1);

					// printa_info_jogador(p1);
					al_resize_display(display, JOGO_W, JOGO_H);

					al_set_timer_count(timer_jogo_um_jog, 0);
					al_set_timer_count(timer_bola, 0);
					// desenha_jogador(p1);

					toca_musica_jogo();

					state = JOGO_UM_JOGADOR;
					printf("Foi jogo um jogador\r\n");
					break;
				case CARREGA_DOIS_JOGADORES:
					// Faz o init do jogador1 e jogador2 utilizando o tipo de jogador escolhido
					printf("Foi carrega 2 jogadores\r\n");

					tipo_jogo = DOIS_JOG;

					init_jogador1(&p1, opcao_jogador1);
					init_jogador2(&p2, opcao_jogador2);

					al_resize_display(display, JOGO_W, JOGO_H);

					al_set_timer_count(timer_bola, 0);

					toca_musica_jogo();

					state = JOGO_DOIS_JOGADORES;
					printf("Foi jogo dois jogadores\r\n");
					break;
				case JOGO_UM_JOGADOR:
					// printf("Foi jogo 1 jogador\r\n");
					tempo_jogo = al_get_timer_count(timer_jogo_um_jog);

					desenha_quadra();
					desenha_placar(pontos_p1, pontos_p2, UM_JOG, tempo_jogo);

					if (al_get_timer_count(timer_bola) == TEMPO_SOLTA_BOLA) {
						// printf("e\r\n");
						cria_bola(&bolas, &contador_bolas);
						al_set_timer_count(timer_bola, 0);
					}
					// printf("Vai verificar\r\n");
					verifica_posicao_bola_quadra(&bolas, &contador_bolas, &pontos_p1, &pontos_p2, tipo_jogo);
					verifica_posicao_bola_jogador(&bolas, &p1, pode_rebater_j1);
					desenha_bola(bolas);
					atualiza_bolas(&bolas);

					verifica_posicao(&p1);
					desenha_jogador(p1);
					atualiza_jogador(&p1);

					if (pontos_p2 >= PONTOS_VITORIA) {
						state = CARREGA_FINAL_JOGO;
						printf("Foi carrega final um jogador\r\n");
					}

					// Abre o jogo para 1 jogador
					break;
				case JOGO_DOIS_JOGADORES:
					// // Abre o jogo para 2 jogadores
					// printf("Foi jogo 2 jogador\r\n");
					desenha_quadra();
					desenha_placar(pontos_p1, pontos_p2, DOIS_JOG, tempo_jogo);

					if (al_get_timer_count(timer_bola) == TEMPO_SOLTA_BOLA) {
						// printf("e\r\n");
						cria_bola(&bolas, &contador_bolas);
						al_set_timer_count(timer_bola, 0);
					}

					verifica_posicao_bola_quadra(&bolas, &contador_bolas, &pontos_p1, &pontos_p2, tipo_jogo);
					verifica_posicao_bola_jogadores(&bolas, &p1, &p2, pode_rebater_j1, pode_rebater_j2);
					desenha_bola(bolas);
					atualiza_bolas(&bolas);

					verifica_posicoes_jogadores(&p1, &p2);
					desenha_jogadores(p1, p2);
					atualiza_jogadores(&p1, &p2);

					if ((pontos_p1 >= PONTOS_VITORIA) || (pontos_p2 >= PONTOS_VITORIA)) {
						state = CARREGA_FINAL_JOGO;
						printf("Foi carrega final dois jogadors\r\n");
					}

					break;
				case CARREGA_FINAL_JOGO:
					printf("Pega os pontos, escreve no arquivo");

					prepara_final_jogo(pontos_p1, pontos_p2, tipo_jogo, tempo_jogo);
					al_resize_display(display, MENU_W, MENU_H);

					state = FINAL_JOGO;
					printf("Foi carrega final jogo\r\n");
					break;

				case FINAL_JOGO:
					printf("\nFINAL DO JOGO!\r\n");
					// al_resize_display(display, MENU_W, MENU_H);

					desenha_final_jogo(tipo_jogo, pontos_p1, pontos_p2, tempo_jogo);

					state = AGUARDA_SAIR;
					printf("Foi aguarda sair\r\n");

					break;

				case AGUARDA_SAIR:
					// printf("\nAGUARDA SAIR DO JOGO!\r\n");
					break;
				case SAIR:
					// limpa_menu(bg_menu);
					limpa_menu();
					limpa_pongs();
					playing = 0;
					printf("Foi sair\r\n");
					break;

				default:
					break;
			}

			// atualiza a tela (quando houver algo para mostrar)
			al_flip_display();

			// if (al_get_timer_count(timer) % (int)FPS == 0)
			// 	printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer) / FPS));
		}
		// se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		// se o tipo de evento for um clique de mouse
		// else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		// 	printf("\nmouse clicado em: %d, %d", ev.mouse.x, ev.mouse.y);
		// }
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP) {

			if (state == MENU) {
				verifica_selecao_menu(ev, &counter, &counter2, &state);
				verifica_movimentacao_menus(ev, &counter, &counter2);
			} else if (state == ESCOLHE_UM_JOGADOR || state == ESCOLHE_DOIS_JOGADORES) {
				verifica_selecao_jogador(ev, &counter, &counter2, &opcao_jogador1, &opcao_jogador2, &state);
				verifica_movimentacao_menus(ev, &counter, &counter2);
			} else if (state == JOGO_UM_JOGADOR || state == JOGO_DOIS_JOGADORES) {
				verifica_tecla_movimentacao(ev, &p1, &p2, state);
				verifica_tecla_rebatida(ev, state, &pode_rebater_j1, &pode_rebater_j2);
			}

			if (state == MENU || state == AJUDA) {
				verifica_tecla_ajuda(ev, &state);
			}

			if (state == AGUARDA_SAIR) {
				verifica_teclas_final_jogo(ev, &state);
			}

			verifica_esc(ev, &state, &playing);
		}

	} // fim do while

	// procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	al_destroy_bitmap(icone_pong);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
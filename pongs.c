#include "pongs.h"
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
#include <string.h>
#include <time.h>
//
#include "jogadores.h"

ALLEGRO_SAMPLE *move_menu = NULL;
ALLEGRO_SAMPLE *intro = NULL;
ALLEGRO_SAMPLE *jogo = NULL;

void init_pongs() {
	move_menu = al_load_sample("data/audio/menu-navigate-03.wav");
	intro = al_load_sample("data/audio/top-gear-intro.wav");
	jogo = al_load_sample("data/audio/top-gear-3.wav");
}

void init_var_pongs(int *contador_bolas, int *pontos_p1, int *pontos_p2, int *counter, int *counter2, fsm_escolha_jogadores *opcao_jogador1, fsm_escolha_jogadores *opcao_jogador2, int *tipo_jogo, int *tempo_jogo) {

	*contador_bolas = 0;

	*pontos_p1 = 0;
	*pontos_p2 = 0;

	*counter = 0;
	*counter2 = -1;

	*opcao_jogador1 = INIT_ESCOLHA_JOGADOR;
	*opcao_jogador2 = INIT_ESCOLHA_JOGADOR;

	*tipo_jogo = 0;
	*tempo_jogo = 0;

	if (COM_SOM) {
		al_stop_samples();
		al_play_sample(intro, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
	}
}

void toca_musica_jogo() {

	if (COM_SOM) {
		// al_stop_sample(intro);
		al_stop_samples();
		al_play_sample(jogo, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
	}
}

void verifica_esc(ALLEGRO_EVENT ev, fsm_menu *state, int *playing) {
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			switch (*state) {
				case AJUDA:
				case ESCOLHE_UM_JOGADOR:
				case ESCOLHE_DOIS_JOGADORES:
					*state = INIT_VAR_PONGS;
					break;

				default:
					*playing = 0;
					break;
			}
		}
	}
}

void verifica_selecao_menu(ALLEGRO_EVENT ev, int *counter, int *counter2, fsm_menu *state) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
			switch (*counter) {
				case 0:
					*state = ESCOLHE_UM_JOGADOR;
					*counter = 0;
					*counter2 = -1;
					printf("Foi escolhe um jogador!\r\n");
					break;
				case 1:
					*state = ESCOLHE_DOIS_JOGADORES;
					*counter = 0;
					*counter2 = 0;
					printf("Foi escolhe dois jogador!\r\n");
					break;
				case 2:
					*state = SAIR;
					break;

				default:
					break;
					// opcao_menu = counter;
			}
		}
	}
}

void verifica_selecao_jogador(ALLEGRO_EVENT ev, int *counter, int *counter2, fsm_escolha_jogadores *opcao_jogador1, fsm_escolha_jogadores *opcao_jogador2, fsm_menu *state) {
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
			switch (*counter) {
				case 0:
					*opcao_jogador1 = TIPO_JOGADOR1;
					break;
				case 1:
					*opcao_jogador1 = TIPO_JOGADOR2;
					break;
				case 2:
					*opcao_jogador1 = TIPO_JOGADOR3;
					break;

				default:
					*opcao_jogador1 = INIT_ESCOLHA_JOGADOR;
					break;
					// opcao_menu = counter;
			}
		}

		if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
			switch (*counter2) {
				case 0:
					*opcao_jogador2 = TIPO_JOGADOR1;
					break;
				case 1:
					*opcao_jogador2 = TIPO_JOGADOR2;
					break;
				case 2:
					*opcao_jogador2 = TIPO_JOGADOR3;
					break;

				default:
					*opcao_jogador2 = INIT_ESCOLHA_JOGADOR;
					break;
					// opcao_menu = counter;
			}
		}
	}

	// printf("Opcao j1: %d\r\n", *counter);
	// printf("Opcao j2: %d\r\n", *counter2);

	if (*state == ESCOLHE_UM_JOGADOR) {
		if (*opcao_jogador1 != INIT_ESCOLHA_JOGADOR) {
			*state = CARREGA_UM_JOGADOR;
		}
	} else if (*state == ESCOLHE_DOIS_JOGADORES) {
		if (*opcao_jogador1 != INIT_ESCOLHA_JOGADOR && *opcao_jogador2 != INIT_ESCOLHA_JOGADOR) {
			*state = CARREGA_DOIS_JOGADORES;
		}
	}
}

void verifica_movimentacao_menus(ALLEGRO_EVENT ev, int *counter, int *counter2) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_UP) {
			al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

			// *counter-- não funciona. Estranho...
			*counter = *counter - 1;

			if (*counter < 0) {
				*counter = 2;
			}
		} else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

			// *counter++ não funciona. Estranho...
			*counter = *counter + 1;

			if (*counter > 2) {
				*counter = 0;
			}
		}

		if (*counter2 != -1) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_W) {
				al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

				// *counter-- não funciona. Estranho...
				*counter2 = *counter2 - 1;

				if (*counter2 < 0) {
					*counter2 = 2;
				}
			} else if (ev.keyboard.keycode == ALLEGRO_KEY_S) {
				al_play_sample(move_menu, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

				// *counter++ não funciona. Estranho...
				*counter2 = *counter2 + 1;

				if (*counter2 > 2) {
					*counter2 = 0;
				}
			}
		}
	}
}

void verifica_tecla_movimentacao(ALLEGRO_EVENT ev, Jogador *p1, Jogador *p2, fsm_menu state) {

	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				p1->cima = 1;
				break;

			case ALLEGRO_KEY_DOWN:
				p1->baixo = 1;
				break;

			case ALLEGRO_KEY_LEFT:
				p1->esq = 1;
				break;

			case ALLEGRO_KEY_RIGHT:
				p1->dir = 1;
				break;

			case ALLEGRO_KEY_W:
				p2->cima = 1;
				break;

			case ALLEGRO_KEY_S:
				p2->baixo = 1;
				break;

			case ALLEGRO_KEY_A:
				p2->esq = 1;
				break;

			case ALLEGRO_KEY_D:
				p2->dir = 1;
				break;
		}
	} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {

		switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				p1->cima = 0;
				break;

			case ALLEGRO_KEY_DOWN:
				p1->baixo = 0;
				break;

			case ALLEGRO_KEY_LEFT:
				p1->esq = 0;
				break;

			case ALLEGRO_KEY_RIGHT:
				p1->dir = 0;
				break;

			case ALLEGRO_KEY_W:
				p2->cima = 0;
				break;

			case ALLEGRO_KEY_S:
				p2->baixo = 0;
				break;

			case ALLEGRO_KEY_A:
				p2->esq = 0;
				break;

			case ALLEGRO_KEY_D:
				p2->dir = 0;
				break;
		}
	}

	if (state == JOGO_UM_JOGADOR) {
		p2->cima = 0;
		p2->baixo = 0;
		p2->esq = 0;
		p2->dir = 0;
	}
}

void verifica_tecla_rebatida(ALLEGRO_EVENT ev, fsm_menu state, bool *pode_rebater_j1, bool *pode_rebater_j2) {
	if (state == JOGO_UM_JOGADOR || state == JOGO_DOIS_JOGADORES) {
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				*pode_rebater_j1 = true;
				printf("Pode rebater 1\r\n");
			}

			if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
				*pode_rebater_j2 = true;
				printf("Pode rebater 2\r\n");
			}
		} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				*pode_rebater_j1 = false;
				printf("Nao rebater 1\r\n");
			}

			if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
				*pode_rebater_j2 = false;
				printf("Nao rebater 2\r\n");
			}
		}
	}
}

void prepara_final_jogo(int pontos_p1, int pontos_p2, int tipo_jogo, int tempo_jogo) {

	if (tipo_jogo == UM_JOG) {
		printf("FIM 1 JOGADOR\r\n");

		FILE *partidas;

		partidas = fopen("partidas-um-jogador.txt", "a");

		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		// printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

		char linha_salva[200];
		// char pontos[3];
		char tempo[1000];
		char data[50];

		strcpy(data, "");

		strcpy(linha_salva, "");

		// Pega j1
		char j1[] = "Jogador 1";

		strcat(linha_salva, j1);

		strcat(linha_salva, ": ");

		sprintf(tempo, "%d", tempo_jogo);

		strcat(linha_salva, tempo);
		// strcat(linha_salva, " ");

		strcat(linha_salva, " segundos");

		strcat(linha_salva, " - ");

		// Pega data
		sprintf(data, "%02d", tm.tm_mday);
		strcat(linha_salva, data);
		strcat(linha_salva, "/");

		strcpy(data, "");

		sprintf(data, "%02d", tm.tm_mon + 1);
		strcat(linha_salva, data);
		strcat(linha_salva, "/");

		strcpy(data, "");

		sprintf(data, "%d", tm.tm_year + 1900);
		strcat(linha_salva, data);
		strcat(linha_salva, " - ");

		strcpy(data, "");

		sprintf(data, "%02d", tm.tm_hour);
		strcat(linha_salva, data);
		strcat(linha_salva, ":");

		strcpy(data, "");

		sprintf(data, "%02d", tm.tm_min);
		strcat(linha_salva, data);
		strcat(linha_salva, ":");

		strcpy(data, "");

		sprintf(data, "%02d", tm.tm_sec);
		strcat(linha_salva, data);

		strcat(linha_salva, "\n");

		printf("Linha: %s", linha_salva);

		fprintf(partidas, "%s", linha_salva);
		// fprintf(partidas, "%s", "\n");

		//
		strcpy(linha_salva, "");
		fclose(partidas);

	} else if (tipo_jogo == DOIS_JOG) {

		printf("FIM 2 JOGADOR\r\n");
		FILE *partidas;

		partidas = fopen("partidas-dois-jogadores.txt", "a");

		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		// printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

		char linha_salva[200];
		char pontos[3];
		char data[50];

		strcpy(data, "");

		strcpy(linha_salva, "");

		// Pega j1
		char j1[] = "Jogador 1";

		strcat(linha_salva, j1);

		strcat(linha_salva, ": ");

		sprintf(pontos, "%d", pontos_p1);

		strcat(linha_salva, pontos);

		strcat(linha_salva, " - ");

		// Pega j2
		char j2[] = "Jogador 2";

		strcat(linha_salva, j2);

		strcat(linha_salva, ": ");

		strcpy(pontos, "");

		sprintf(pontos, "%d", pontos_p2);

		strcat(linha_salva, pontos);

		strcat(linha_salva, " - ");

		// Pega data
		sprintf(data, "%02d", tm.tm_mday);
		strcat(linha_salva, data);
		strcat(linha_salva, "/");

		strcpy(data, "");

		sprintf(data, "%02d", tm.tm_mon + 1);
		strcat(linha_salva, data);
		strcat(linha_salva, "/");

		strcpy(data, "");

		sprintf(data, "%d", tm.tm_year + 1900);
		strcat(linha_salva, data);
		strcat(linha_salva, " - ");

		strcpy(data, "");

		sprintf(data, "%02d", tm.tm_hour);
		strcat(linha_salva, data);
		strcat(linha_salva, ":");

		strcpy(data, "");

		sprintf(data, "%02d", tm.tm_min);
		strcat(linha_salva, data);
		strcat(linha_salva, ":");

		strcpy(data, "");

		sprintf(data, "%02d", tm.tm_sec);
		strcat(linha_salva, data);

		strcat(linha_salva, "\n");

		printf("Linha: %s", linha_salva);

		fprintf(partidas, "%s", linha_salva);
		// fprintf(partidas, "%s", "\n");

		//
		strcpy(linha_salva, "");
		fclose(partidas);

		int ganhou = 0;

		if (pontos_p1 >= PONTOS_VITORIA) {
			ganhou = 1;
		} else if (pontos_p2 >= PONTOS_VITORIA) {
			ganhou = 2;
		}

		FILE *pega_historico;
		pega_historico = fopen("historico.txt", "r");
		// printf("Leu arq historico\r\n");

		if (pega_historico == NULL) {
			// printf("Deu ruim arq historico\r\n");

			pega_historico = fopen("historico.txt", "w");

			if (pega_historico == NULL) {
				// printf("Agora deu ruim de vez arq historico\r\n");
			} else {

				if (ganhou == 1) {
					fprintf(pega_historico, "%c", '1');
					fprintf(pega_historico, "%c", ' ');
					fprintf(pega_historico, "%c", '0');
					fprintf(pega_historico, "%c", ' ');
				} else if (ganhou == 2) {
					fprintf(pega_historico, "%c", '0');
					fprintf(pega_historico, "%c", ' ');
					fprintf(pega_historico, "%c", '1');
					fprintf(pega_historico, "%c", ' ');
				}

				fclose(pega_historico);
			}
		} else {
			// printf("Abriu arq hist para leitura\r\n");

			char aux[10];
			char c1, c2;
			// int hist[2];
			int i = 0;

			int jogos_j1 = 0;
			int jogos_j2 = 0;

			for (i = 0; i < 10; i++) {
				c1 = fgetc(pega_historico);

				if (c1 != ' ') {
					aux[i] = c1;
					// i++;
				} else {
					i = 10;
				}
			}

			// printf("Hist_j1 pego: %s\r\n", aux);

			jogos_j1 = strtol(aux, NULL, 10);

			strcpy(aux, "         ");

			for (i = 0; i < 10; i++) {
				c2 = fgetc(pega_historico);

				if (c2 != ' ') {
					aux[i] = c2;
					// i++;
				} else {
					i = 10;
				}
			}

			// printf("Hist_j2 pego: %s\r\n", aux);

			jogos_j2 = strtol(aux, NULL, 10);

			// printf("Jogos j1 antes: %d\r\n", jogos_j1);
			// printf("Jogos j2 antes: %d\r\n", jogos_j2);

			if (ganhou == 1) {
				jogos_j1++;
			} else if (ganhou = 2) {
				jogos_j2++;
			}

			// printf("Jogos j1 depois: %d\r\n", jogos_j1);
			// printf("Jogos j2 depois: %d\r\n", jogos_j2);

			fclose(pega_historico);

			pega_historico = fopen("historico.txt", "w");

			fprintf(pega_historico, "%d", jogos_j1);
			fprintf(pega_historico, "%c", ' ');
			fprintf(pega_historico, "%d", jogos_j2);
			fprintf(pega_historico, "%c", ' ');

			fclose(pega_historico);
		}
	}
}

void verifica_tecla_ajuda(ALLEGRO_EVENT ev, fsm_menu *state) {
	if (*state == MENU) {
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_H) {
				// printf("Apertou H\r\n");
				*state = AJUDA;
			}
		}
	}
}

void verifica_teclas_final_jogo(ALLEGRO_EVENT ev, fsm_menu *state) {
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER || ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
			*state = INIT_VAR_PONGS;
		}
	}
}

void limpa_pongs() {
	al_destroy_sample(intro);
	al_destroy_sample(move_menu);
	al_destroy_sample(jogo);
}
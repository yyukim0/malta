#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include "header.h"
#include <string.h>

char str[3];
void manipular_entrada(ALLEGRO_EVENT evento);
void exibir_texto_centralizado(GameAssets* assets);

// Função principal
int main(void) {
    GameAssets assets;
    GameState state;
    Character character = { 640, 360, 0, 128, 0 };
    state.chat_pergunta_estante = false;
    state.chat_resposta_correta_estante = false;
    state.chat_resposta_errada_estante = false;
    state.chat = false;
    state.chat_aviso_mesa = false;
    state.chave = false;
    state.chat_aviso_tv = false;
    state.chat_pergunta_tv = false;
    state.chat_para_tv = false;
    state.chat_pergunta_tv = false;
    state.chat_resposta_correta_tv = false;
    state.chat_resposta_errada_tv = false;
    state.mapa2 = false;

    strcpy_s(str, sizeof(str), "");

    init_allegro(&assets);
    init_game_state(&state);

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(assets.event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
            manipular_entrada(event); // Processa qualquer entrada de caractere
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (state.menu) {
                handle_menu_interactions(&state, &assets, event.keyboard.keycode);
            }
            else {
                // Atualiza as flags de acordo com a tecla pressionada
                if (event.keyboard.keycode == ALLEGRO_KEY_UP) state.key_up = true;
                if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) state.key_down = true;
                if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) state.key_left = true;
                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) state.key_right = true;
            
                if(state.mapa1) {
                //interação da mesa quando a gaveta está fechada
                    if (player_interacao(&character, &state, &assets, 550, 150, 120)) {
                        printf("dentro da interação - MESA\n");
                        if (event.keyboard.keycode == ALLEGRO_KEY_Z && !state.chat_aviso_mesa) {
                            state.chat_aviso_mesa = true;
                            state.chat = true;
                            printf("entrou"); //eu juro que fiquei 1 hora resolvendo um bug, eu botei esse printf e deu certo
                        }
                        else if (event.keyboard.keycode == ALLEGRO_KEY_Z && state.chat_aviso_mesa) {
                            state.chat = false;
                            state.chat_aviso_mesa = false;
                        }
                    }
                    //interação da tv
                    if (player_interacao(&character, &state, &assets, 337, 200, 120)) {
                        printf("dentro da interação - TELEVISÃO\n");


                        if (event.keyboard.keycode == ALLEGRO_KEY_Z && !state.chat_aviso_tv) {
                            state.chat_aviso_tv = true;
                            state.chat_para_tv = true;
                        }
                        else if (event.keyboard.keycode == ALLEGRO_KEY_Z && state.chat_aviso_tv && !state.chat_pergunta_tv) {
                            state.chat_pergunta_tv = true;
                            state.chat_aviso_tv = false;
                            state.chat_para_tv = true;
                        }
                        if ((event.keyboard.keycode == ALLEGRO_KEY_2 && state.chat_pergunta_tv) ||
                            (event.keyboard.keycode == ALLEGRO_KEY_3 && state.chat_pergunta_tv) ||
                            (event.keyboard.keycode == ALLEGRO_KEY_1 && state.chat_pergunta_tv)) {
                            state.chat_resposta_errada_tv = true;
                            state.chat_resposta_correta_tv = false;
                            state.chat_pergunta_tv = false;
                            state.chat_para_tv = true;
                        }
                        else if (event.keyboard.keycode == ALLEGRO_KEY_4 && state.chat_pergunta_tv) {
                            printf("Você apertou 4\n");
                            state.chat_resposta_correta_tv = true;
                            state.chat_resposta_errada_tv = false;
                            state.chat_pergunta_tv = false;
                            state.chat_para_tv = true;
                        }
                        else if (event.keyboard.keycode == ALLEGRO_KEY_Z && (state.chat_resposta_correta_tv || state.chat_resposta_errada_tv)) {
                            state.chat_para_tv = false;
                            state.chat_resposta_correta_tv = false;
                            state.chat_resposta_errada_tv = false;
                            state.chat_aviso_tv = false;
                        }
                    }
                    //interação da estante
                    if (player_interacao(&character, &state, &assets, 660, 125, 120)) {
                        printf("dentro da interação - ESTANTE\n");

                        if (event.keyboard.keycode == ALLEGRO_KEY_Z && !state.chat_resposta_correta_estante && !state.chat_resposta_errada_estante) {

                            state.chat_pergunta_estante = true;
                            state.chat = true;
                        }
                        if (!(strcmp(str, "12") == 0) && state.chat_pergunta_estante && event.keyboard.keycode == ALLEGRO_KEY_Z) {
                            state.chat_resposta_errada_estante = true;
                            state.chat_pergunta_estante = false;
                        }
                        if (strcmp(str, "12") == 0 && state.chat_pergunta_estante && event.keyboard.keycode == ALLEGRO_KEY_Z) {
                            printf("Você apertou 2\n");
                            state.chat_resposta_correta_estante = true;
                            state.chat_pergunta_estante = false;
                            state.chat_resposta_errada_estante = false;
                            state.chave = true;
                        }
                        if (event.keyboard.keycode == ALLEGRO_KEY_Z && (state.chat_resposta_correta_estante || state.chat_resposta_errada_estante)) {
                            state.chat = false;
                            state.chat_resposta_correta_estante = false;
                            state.chat_resposta_errada_estante = false;
                        }
                    }
                    //interação final
                    if (state.chave) {
                        if (player_interacao(&character, &state, &assets, 460, 127, 120) && event.keyboard.keycode == ALLEGRO_KEY_Z) {
                            printf("dentro da interação - PORTA\n");
                            state.mapa1 = false;
                            state.mapa2 = true;

                        }
                    }
                }
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            // Atualiza as flags de acordo com a tecla solta
            if (event.keyboard.keycode == ALLEGRO_KEY_UP) state.key_up = false;
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) state.key_down = false;
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) state.key_left = false;
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) state.key_right = false;
        }

        if (!state.menu) {
            update_position(&character, &state, &assets);
        }


        draw_game(&assets, &state, &character);
        exibir_texto_centralizado(&assets); // Garante que o texto sempre seja desenhado
        al_flip_display();
}

    destroy_assets(&assets);
    return 0;
}

void manipular_entrada(ALLEGRO_EVENT evento)
{
    if (evento.type == ALLEGRO_EVENT_KEY_CHAR) // Verifica se o input é um caractere
    {
        if (strlen(str) < 2) // Limita o tamanho da string a 4 caracteres
        {
            char temp[] = { evento.keyboard.unichar, '\0' }; // Buffer temporário com o caractere
            if (evento.keyboard.unichar >= '0' && evento.keyboard.unichar <= '9') // Aceita caracteres de 0 a 9
            {
                strcat_s(str, sizeof(str), temp); // Concatena com segurança
            }
        }

        if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0) // Trata o backspace
        {
            str[strlen(str) - 1] = '\0'; // Remove o último caractere
        }
    }
}

void exibir_texto_centralizado(GameAssets* assets)
{
    if (strlen(str) > 0) // Verifica se a string não está vazia
    {
        al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 500, 580, 0, str); // Desenha no centro da tela
    }
}
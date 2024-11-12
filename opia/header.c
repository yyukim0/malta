#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include "header.h"

// Fun��o para inicializar Allegro e os componentes
void init_allegro(GameAssets* assets) {
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    assets->display = al_create_display(1280, 720);
    al_set_window_position(assets->display, 200, 200);
    al_set_window_title(assets->display, "opia");

    assets->fonte_grande = al_load_font("./YumeNikkiTitleScreen.ttf", 50, 0);
    assets->fonte_pequena = al_load_font("./YumeNikkiTitleScreen.ttf", 40, 0);
    assets->timer = al_create_timer(1.0 / 30.0);

    // Carregando imagens
    assets->cama = al_load_bitmap("./cama.png");
    assets->tv = al_load_bitmap("./televisao.png");
    assets->mainCharacter = al_load_bitmap("./mc - precisamos decidir um nome.png");
    assets->bg = al_load_bitmap("./quarto inteiro.png");
    assets->parede_baixa = al_load_bitmap("./parede - baixo.png");
    assets->parede_esquerda = al_load_bitmap("./parede - lado.png");
    assets->parede_direita = al_load_bitmap("./parede - lado.png");
    assets->parede_direita_baixo = al_load_bitmap("./parede - canto - direita.png");
    assets->parede_esquerda_baixo = al_load_bitmap("./parede - canto - esquerda.png");
    assets->parede_cima = al_load_bitmap("./parede - cima.png");
    assets->menu_start = al_load_bitmap("./menu - start.png");
    assets->menu_controls = al_load_bitmap("./menu - controls.png");
    assets->chat_box = al_load_bitmap("./chat-box.jpeg");
    assets->page_controls = al_load_bitmap("./controls.png");
    assets->estante = al_load_bitmap("./estante.png");
    assets->mesa = al_load_bitmap("./mesa.png");
    assets->porta = al_load_bitmap("./porta.png");

    //segundo mapa
    assets->bg_sala2 = al_load_bitmap("./bg_sala_2.png");
    assets->parede_sala2 = al_load_bitmap("./parede_2.png");
    assets->parede_baixa_sala2 = al_load_bitmap("./parede_baixo_2.png");
    assets->parede_canto_direita_sala2 = al_load_bitmap("./parede_canto_direito_2.png");
    assets->parede_canto_esquerda_sala2 = al_load_bitmap("./parede_canto_esquerdo_2.png");
    assets->parede_cima_sala2 = al_load_bitmap("./parede_cima_2.png");
    assets->parede_curta_sala2 = al_load_bitmap("./parede_curta_2.png");
    assets->parede_lados_sala2 = al_load_bitmap("./parede_lados_2.png");
    assets->porta_sala2 = al_load_bitmap("./porta_2.png");
    assets->abajur = al_load_bitmap("./abajur.png");
    assets->balcao = al_load_bitmap("./balcao.png");
    assets->banheira = al_load_bitmap("./banheira.png");
    assets->cabide = al_load_bitmap("./cabide.png");
    assets->cadeiradireita = al_load_bitmap("./cadeiradireita.png");
    assets->cadeiraesquerda = al_load_bitmap("./cadeiraesquerda.png");
    assets->estante2 = al_load_bitmap("./estante2.png");
    assets->mesa2 = al_load_bitmap("./mesa2.png");
    assets->portaretrato = al_load_bitmap("./portaretrato.png");
    assets->poca = al_load_bitmap("./poca.png");
    assets->relogio = al_load_bitmap("./relogio.png");
    assets->fotos = al_load_bitmap("./fotos.png");
    assets->tapete2 = al_load_bitmap("./tapete2.png");
    assets->panela = al_load_bitmap("./panela.png");


    assets->event_queue = al_create_event_queue();
    al_register_event_source(assets->event_queue, al_get_display_event_source(assets->display));
    al_register_event_source(assets->event_queue, al_get_timer_event_source(assets->timer));
    al_register_event_source(assets->event_queue, al_get_keyboard_event_source());
    al_start_timer(assets->timer);

}

// Fun��o para limpar os recursos
void destroy_assets(GameAssets* assets) {
    al_destroy_bitmap(assets->menu_start);
    al_destroy_bitmap(assets->chat_box);
    al_destroy_bitmap(assets->parede_cima);
    al_destroy_bitmap(assets->parede_esquerda_baixo);
    al_destroy_bitmap(assets->parede_direita_baixo);
    al_destroy_bitmap(assets->parede_direita);
    al_destroy_bitmap(assets->parede_esquerda);
    al_destroy_bitmap(assets->mainCharacter);
    al_destroy_bitmap(assets->parede_baixa);
    al_destroy_bitmap(assets->bg);
    al_destroy_font(assets->fonte_grande);
    al_destroy_font(assets->fonte_pequena);
    al_destroy_display(assets->display);
    al_destroy_event_queue(assets->event_queue);
    al_destroy_bitmap(assets->tv);
    al_destroy_bitmap(assets->cama);
    al_destroy_bitmap(assets->estante);
    al_destroy_bitmap(assets->mesa);
    al_destroy_bitmap(assets->porta);

    //mapa2
    al_destroy_bitmap(assets->bg_sala2);
    al_destroy_bitmap(assets->parede_sala2);
    al_destroy_bitmap(assets->parede_baixa_sala2);
    al_destroy_bitmap(assets->parede_canto_direita_sala2);
    al_destroy_bitmap(assets->parede_canto_esquerda_sala2);
    al_destroy_bitmap(assets->parede_cima_sala2);
    al_destroy_bitmap(assets->parede_curta_sala2);
    al_destroy_bitmap(assets->parede_lados_sala2);
    al_destroy_bitmap(assets->cabide);
    al_destroy_bitmap(assets->abajur);
    al_destroy_bitmap(assets->balcao);
    al_destroy_bitmap(assets->banheira);
    al_destroy_bitmap(assets->cabide);
    al_destroy_bitmap(assets->cadeiradireita);
    al_destroy_bitmap(assets->cadeiraesquerda);
    al_destroy_bitmap(assets->estante2);
    al_destroy_bitmap(assets->fotos);
    al_destroy_bitmap(assets->mesa2);
    al_destroy_bitmap(assets->panela);
    al_destroy_bitmap(assets->poca);
    al_destroy_bitmap(assets->porta_sala2);
    al_destroy_bitmap(assets->portaretrato);
    al_destroy_bitmap(assets->tapete2);
    al_destroy_bitmap(assets->relogio);
}

// Fun��o para inicializar o estado do jogo
void init_game_state(GameState* state) {
    state->menu = true; // Come�a com o menu ativo
    state->start = true; // O cursor do menu come�a na op��o 'Start'
    state->pos_x = 640;
    state->pos_y = 360;

    // Posi��es das paredes para impedir que o personagem as atravesse
    state->parede_cima_y = 180;  // Ajuste da colis�o na parte superior
    state->parede_baixa_y = 630;
    state->parede_esquerda_x = 343;
    state->parede_direita_x = 970;

    // Inicializa as flags das teclas como falsas
    state->key_up = false;
    state->key_down = false;
    state->key_left = false;
    state->key_right = false;
}

// Fun��o para atualizar a posi��o do personagem
void update_position(Character* character, GameState* state, GameAssets* assets) {
    bool moving = false; // Verifica se o personagem est� se movendo
    if (state->mapa1 || state->mapa2) {
        // Dimens�es e posi��o da televis�o (somente em mapa1)
        int tv_x = 337;
        int tv_y = 200;
        int tv_width = 95;
        int tv_height = 50;

        // Dimens�es do canto superior direito (ajustadas, somente em mapa1)
        int canto_superior_direito_x_min = 900;
        int canto_superior_direito_x_max = 1100;
        int canto_superior_direito_y_min = 180;
        int canto_superior_direito_y_max = 240;

        printf("Posi��o do personagem: X=%d, Y=%d\n", state->pos_x, state->pos_y);

        // Dimens�es da cama (somente em mapa1)
        int cama_x = 860;
        int cama_y = 150;
        int cama_width = al_get_bitmap_width(assets->cama) * 5;
        int cama_height = al_get_bitmap_height(assets->cama) * 5;

        // Dimens�es da estante (somente em mapa1)
        int estante_x = 680;
        int estante_y = 30;
        int estante_width = al_get_bitmap_width(assets->estante) * 5;
        int estante_height = al_get_bitmap_height(assets->estante) * 5;

        // Dimens�es da mesa (somente em mapa1)
        int mesa_x = 550;
        int mesa_y = 20;
        int mesa_width = al_get_bitmap_width(assets->mesa) * 5;
        int mesa_height = al_get_bitmap_height(assets->mesa) * 5;

        // Verifica colis�o somente na dire��o que o personagem est� se movendo
        if (state->key_right && state->pos_x + 90 < state->parede_direita_x) {
            if (!(
                (state->mapa1 && state->pos_x + 90 >= tv_x && state->pos_x + 90 <= tv_x + tv_width &&
                    state->pos_y + 128 > tv_y && state->pos_y < tv_y + tv_height) ||
                (state->mapa1 && state->pos_x + 90 >= cama_x && state->pos_x + 90 <= cama_x + cama_width &&
                    state->pos_y + 128 > cama_y && state->pos_y < cama_y + cama_height) ||
                (state->mapa1 && state->pos_x + 90 >= mesa_x && state->pos_x + 90 <= mesa_x + mesa_width &&
                    state->pos_y + 128 > mesa_y && state->pos_y < mesa_y + mesa_height) ||
                (state->mapa1 && state->pos_x + 90 >= estante_x && state->pos_x + 90 <= estante_x + estante_width &&
                    state->pos_y + 128 > estante_y && state->pos_y < estante_y + estante_height) ||
                (state->mapa1 && state->pos_x + 90 >= canto_superior_direito_x_min && state->pos_x + 90 <= canto_superior_direito_x_max &&
                    state->pos_y + 128 > canto_superior_direito_y_min && state->pos_y < canto_superior_direito_y_max)
                )) {
                character->frame_y = 128;  // Dire��o direita
                state->pos_x += 5;
                moving = true;
            }
        }
        if (state->key_left && state->pos_x > state->parede_esquerda_x) {
            if (!(
                (state->mapa1 && state->pos_x <= tv_x + tv_width && state->pos_x >= tv_x &&
                    state->pos_y + 128 > tv_y && state->pos_y < tv_y + tv_height) ||
                (state->mapa1 && state->pos_x <= cama_x + cama_width && state->pos_x >= cama_x &&
                    state->pos_y + 128 > cama_y && state->pos_y < cama_y + cama_height) ||
                (state->mapa1 && state->pos_x <= mesa_x + mesa_width && state->pos_x >= mesa_x &&
                    state->pos_y + 128 > mesa_y && state->pos_y < mesa_y + mesa_height) ||
                (state->mapa1 && state->pos_x <= estante_x + estante_width && state->pos_x >= estante_x &&
                    state->pos_y + 128 > estante_y && state->pos_y < estante_y + estante_height)
                )) {
                character->frame_y = 128 * 3;  // Dire��o esquerda
                state->pos_x -= 5;
                moving = true;
            }
        }
        if (state->key_down && state->pos_y + 128 < state->parede_baixa_y) {
            if (!(
                (state->mapa1 && state->pos_x + 90 > tv_x && state->pos_x < tv_x + tv_width &&
                    state->pos_y + 128 >= tv_y && state->pos_y + 128 <= tv_y + tv_height) ||
                (state->mapa1 && state->pos_x + 90 > cama_x && state->pos_x < cama_x + cama_width &&
                    state->pos_y + 128 >= cama_y && state->pos_y + 128 <= cama_y + cama_height) ||
                (state->mapa1 && state->pos_x >= canto_superior_direito_x_min && state->pos_x <= canto_superior_direito_x_max &&
                    state->pos_y + 128 >= canto_superior_direito_y_min && state->pos_y + 128 <= canto_superior_direito_y_max)
                )) {
                character->frame_y = 128 * 2;  // Dire��o para baixo
                state->pos_y += 5;
                moving = true;
            }
        }
        if (state->key_up && state->pos_y > state->parede_cima_y) {
            if (!(
                (state->mapa1 && state->pos_x + 90 > tv_x && state->pos_x < tv_x + tv_width &&
                    state->pos_y <= tv_y + tv_height && state->pos_y >= tv_y) ||
                (state->mapa1 && state->pos_x + 90 > cama_x && state->pos_x < cama_x + cama_width &&
                    state->pos_y <= cama_y + cama_height && state->pos_y >= cama_y) ||
                (state->mapa1 && state->pos_x + 90 > mesa_x && state->pos_x < mesa_x + mesa_width &&
                    state->pos_y <= mesa_y + mesa_height && state->pos_y >= mesa_y) ||
                (state->mapa1 && state->pos_x + 90 > estante_x && state->pos_x < estante_x + estante_width &&
                    state->pos_y <= estante_y + estante_height && state->pos_y >= estante_y) ||
                (state->mapa1 && state->pos_x + 90 >= canto_superior_direito_x_min && state->pos_x + 90 <= canto_superior_direito_x_max &&
                    state->pos_y <= canto_superior_direito_y_max && state->pos_y >= canto_superior_direito_y_min)
                )) {
                character->frame_y = 0;  // Dire��o para cima
                state->pos_y -= 5;
                moving = true;
            }
        }
    }

    // Atualiza a anima��o do personagem apenas se ele estiver se movendo
    if (moving) {
        character->frame += 0.2f;
        if (character->frame > 3) {
            character->frame -= 3;
        }
    }
    else {
        character->frame = 0;
    }
}

// Fun��o para lidar com as intera��es no menu
void handle_menu_interactions(GameState* state, GameAssets* assets, int keycode) {
    if (keycode == ALLEGRO_KEY_DOWN) {
        state->start = false; // Alterna para 'Controls'
    }
    else if (keycode == ALLEGRO_KEY_UP) {
        state->start = true; // Alterna para 'Start'
    }
    else if (keycode == ALLEGRO_KEY_Z) {
        if (state->start) {
            state->menu = false; // Se 'Start' estiver selecionado, sai do menu
        }
        else {
            // Mostra a p�gina de controles
            al_draw_bitmap(assets->page_controls, 0, 0, 0);
            al_flip_display();
            al_rest(5.0); // Exibe por 5 segundos
        }
    }
}

// Fun��o para desenhar o cen�rio, personagem e menu
void draw_game(GameAssets* assets, GameState* state, Character* character) {
    if (state->menu) {
        // Desenha o menu
        al_clear_to_color(al_map_rgb(0, 0, 0));
        if (state->start) {
            al_draw_bitmap_region(assets->menu_start, 0, 0, 1280, 720, 0, 0, 0);
        }
        else {
            al_draw_bitmap_region(assets->menu_controls, 0, 0, 1280, 720, 0, 0, 0);
        }
    }
    else if (state->mapa1) {
        // Desenha o jogo
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap_region(assets->bg, -30, 0, 1280, 720, 0, 50, 0);
        al_draw_bitmap_region(assets->parede_cima, 0, 0, 503, 145, 405, 108, 0);
        al_draw_bitmap_region(assets->parede_direita_baixo, 0, 0, 69, 210, 905, 108, 0);
        al_draw_bitmap_region(assets->parede_esquerda_baixo, 0, 0, 69, 210, 340, 108, 0);
        al_draw_bitmap_region(assets->parede_esquerda, 0, 0, 18, 465, 325, 170, 0);
        al_draw_bitmap_region(assets->parede_direita, 0, 0, 18, 465, 970, 170, 0);
        al_draw_bitmap_region(assets->parede_baixa, 0, 0, 672, 17, 320, 630, 0);
        al_draw_bitmap_region(assets->tv, 0, 0, 124, 155, 337, 200, 0);
        al_draw_scaled_bitmap(assets->cama, 0, 0, al_get_bitmap_width(assets->cama), al_get_bitmap_height(assets->cama),
            850, 250, al_get_bitmap_width(assets->cama) * 5 - 20, al_get_bitmap_height(assets->cama) * 5 - 20, 0);
        al_draw_scaled_bitmap(assets->estante, 0, 0, al_get_bitmap_width(assets->estante), al_get_bitmap_height(assets->estante),
            660, 125, al_get_bitmap_width(assets->estante) * 5 - 20, al_get_bitmap_height(assets->estante) * 5 - 20, 0);
        al_draw_scaled_bitmap(assets->mesa, 0, 0, al_get_bitmap_width(assets->mesa), al_get_bitmap_height(assets->mesa),
            550, 150, al_get_bitmap_width(assets->mesa) * 5 - 50, al_get_bitmap_height(assets->mesa) * 5 - 50, 0);
        al_draw_bitmap_region(assets->porta, 0, 0, al_get_bitmap_width(assets->porta) * 5,
            al_get_bitmap_height(assets->porta) * 5, 460, 127, 0);
        al_draw_bitmap_region(assets->mainCharacter, 100 * (int)character->frame, character->frame_y, 90, 128, state->pos_x, state->pos_y, 0);

        ALLEGRO_EVENT event;

        // Desenha a chat box 
        if (state->chat) {
            al_draw_scaled_bitmap(assets->chat_box, 0, 0, al_get_bitmap_width(assets->chat_box), al_get_bitmap_height(assets->chat_box),
                225, 500, al_get_bitmap_width(assets->chat_box) * 1.25, al_get_bitmap_height(assets->chat_box) * 1.25, 0);
        }
        if (state->chat_para_tv) {
            al_draw_scaled_bitmap(assets->chat_box, 0, 0, al_get_bitmap_width(assets->chat_box), al_get_bitmap_height(assets->chat_box),
                225, 500, al_get_bitmap_width(assets->chat_box) * 1.25, al_get_bitmap_height(assets->chat_box) * 1.25, 0);
        }

        //intera��o com a estante
        if (state->chat_pergunta_estante) {

            al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 400, 520, 0, "qual livro eu deveria pegar?");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 500, 580, 0, "4");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 900, 580, 0, "2");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 500, 620, 0, "3");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 900, 620, 0, "5");

        }  if (state->chat_resposta_correta_estante) {
            al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 450, 520, 0, "caiu uma chave!");
        }  if (state->chat_resposta_errada_estante) {
            al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 450, 520, 0, "parece ter nada");
        }

        //intera��o com a mesa
        if (state->chat_aviso_mesa) {
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 420, 520, 0, "parece que tem um papel aqui. diz:");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 420, 560, 0, "\"conto historias e mostro imagens,");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 410, 600, 0, " sem que voce precise sair do lugar\"");
        }

        //intera��o com a tv
        if (state->chat_aviso_tv) {
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 420, 520, 0, "parece que tem um papel com uma");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 420, 560, 0, "conta na gaveta da tv");
        }

        if (state->chat_resposta_correta_tv) {
            al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 430, 520, 0, "parece estar certo!");
        } if (state->chat_resposta_errada_tv) {
            al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 430, 520, 0, "isso parece um pouco errado!");
        }

        if (state->chat_pergunta_tv) {

            al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 440, 525, 0, "log de 9 na base 3");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 500, 580, 0, "3");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 900, 580, 0, "4");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 500, 620, 0, "5");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 900, 620, 0, "2");
        }
    }
    else if (state->mapa2) {
        al_clear_to_color(al_map_rgb(167, 167, 167));
        al_draw_bitmap_region(assets->bg_sala2, -30, 0, 1280, 720, 0, 50, 0);
        al_draw_bitmap_region(assets->parede_cima_sala2, 0, 0, 503, 145, 415, 146, 0);
        al_draw_bitmap_region(assets->parede_canto_direita_sala2, 0, 0, 69, 210, 883, 162, 0);
        al_draw_bitmap_region(assets->parede_lados_sala2, 0, 0, 482, 465, 930, 172, 0);
        al_draw_bitmap_region(assets->parede_baixa_sala2, 0, 0, 622, 51, 345, 622, 0);
        al_draw_bitmap_region(assets->parede_lados_sala2, 0, 0, 482, 465, 335, 172, 0);
        al_draw_bitmap_region(assets->parede_canto_esquerda_sala2, 0, 12, 100, 210, 355, 160, 0);
        al_draw_scaled_bitmap(assets->banheira, 0, 0, al_get_bitmap_width(assets->banheira), al_get_bitmap_height(assets->banheira),
            765, 460, al_get_bitmap_width(assets->banheira) * 0.37, al_get_bitmap_height(assets->banheira) * 0.37, 0);
        al_draw_scaled_bitmap(assets->tapete2, 0, 0, al_get_bitmap_width(assets->tapete2), al_get_bitmap_height(assets->tapete2),
            460, 290, al_get_bitmap_width(assets->tapete2) * 0.12, al_get_bitmap_height(assets->tapete2) * 0.12, 0);
        al_draw_scaled_bitmap(assets->cadeiraesquerda, 0, 0, al_get_bitmap_width(assets->cadeiraesquerda), al_get_bitmap_height(assets->cadeiraesquerda),
            380, 490, al_get_bitmap_width(assets->cadeiraesquerda) * 0.3, al_get_bitmap_height(assets->cadeiraesquerda) * 0.3, 0);
        al_draw_scaled_bitmap(assets->cadeiradireita, 0, 0, al_get_bitmap_width(assets->cadeiradireita), al_get_bitmap_height(assets->cadeiradireita),
            520, 490, al_get_bitmap_width(assets->cadeiradireita) * 0.3, al_get_bitmap_height(assets->cadeiradireita) * 0.3, 0);
        al_draw_scaled_bitmap(assets->mesa2, 0, 0, al_get_bitmap_width(assets->mesa2), al_get_bitmap_height(assets->mesa2),
            435, 490, al_get_bitmap_width(assets->mesa2) * 0.3, al_get_bitmap_height(assets->mesa2) * 0.3, 0);
        al_draw_scaled_bitmap(assets->estante2, 0, 0, al_get_bitmap_width(assets->estante2), al_get_bitmap_height(assets->estante2),
            600, 170, al_get_bitmap_width(assets->estante2) * 0.37, al_get_bitmap_height(assets->estante2) * 0.37, 0);
        al_draw_scaled_bitmap(assets->relogio, 0, 0, al_get_bitmap_width(assets->relogio), al_get_bitmap_height(assets->relogio),
            375, 240, al_get_bitmap_width(assets->relogio) * 0.13, al_get_bitmap_height(assets->relogio) * 0.13, 0);
        al_draw_scaled_bitmap(assets->cabide, 0, 0, al_get_bitmap_width(assets->cabide), al_get_bitmap_height(assets->cabide),
            890, 290, al_get_bitmap_width(assets->cabide) * 0.3, al_get_bitmap_height(assets->cabide) * 0.3, 0);
        al_draw_scaled_bitmap(assets->balcao, 0, 0, al_get_bitmap_width(assets->balcao), al_get_bitmap_height(assets->balcao),
            700, 215, al_get_bitmap_width(assets->balcao) * 0.3, al_get_bitmap_height(assets->balcao) * 0.3, 0);
        al_draw_scaled_bitmap(assets->poca, 0, 0, al_get_bitmap_width(assets->poca), al_get_bitmap_height(assets->poca),
            715, 385, al_get_bitmap_width(assets->poca) * 0.34, al_get_bitmap_height(assets->poca) * 0.34, 0);
        al_draw_scaled_bitmap(assets->fotos, 0, 0, al_get_bitmap_width(assets->fotos), al_get_bitmap_height(assets->fotos),
            785, 175, al_get_bitmap_width(assets->fotos) * 0.2, al_get_bitmap_height(assets->fotos) * 0.2, 0);
        al_draw_scaled_bitmap(assets->abajur, 0, 0, al_get_bitmap_width(assets->abajur), al_get_bitmap_height(assets->abajur),
            800, 205, al_get_bitmap_width(assets->abajur) * 0.2, al_get_bitmap_height(assets->abajur) * 0.2, 0);
        al_draw_scaled_bitmap(assets->panela, 0, 0, al_get_bitmap_width(assets->panela), al_get_bitmap_height(assets->panela),
            700, 175, al_get_bitmap_width(assets->panela) * 0.15, al_get_bitmap_height(assets->panela) * 0.15, 0);
        al_draw_scaled_bitmap(assets->porta_sala2, 0, 0, al_get_bitmap_width(assets->porta_sala2), al_get_bitmap_height(assets->porta_sala2),
            450, 180, al_get_bitmap_width(assets->porta_sala2) * 0.34, al_get_bitmap_height(assets->porta_sala2) * 0.34, 0);
        al_draw_scaled_bitmap(assets->poca, 0, 0, al_get_bitmap_width(assets->poca), al_get_bitmap_height(assets->poca),
            350, 360, al_get_bitmap_width(assets->poca) * 0.2, al_get_bitmap_height(assets->poca) * 0.2, 180);
        al_draw_scaled_bitmap(assets->portaretrato, 0, 0, al_get_bitmap_width(assets->portaretrato), al_get_bitmap_height(assets->portaretrato),
            540, 205, al_get_bitmap_width(assets->portaretrato) * 0.18, al_get_bitmap_height(assets->portaretrato) * 0.18, 180);
        al_draw_bitmap_region(assets->mainCharacter, 100 * (int)character->frame, character->frame_y, 90, 128, state->pos_x, state->pos_y, 0);
    }
}

//calcula a dist�ncia entre o jogador e o objeto
int player_interacao(Character* character, GameState* state, GameAssets* assets, int obj_x, int obj_y, int range_interacao) {
    int dx_estante = state->pos_x - obj_x;
    int dy_estante = state->pos_y - obj_y;
    return (dx_estante * dx_estante + dy_estante * dy_estante) <= (range_interacao * range_interacao);
}
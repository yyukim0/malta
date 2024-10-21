#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

// Struct do Personagem Principal
typedef struct {
    int x, y;
    int frame_x, frame_y;
    float frame;
} Character;

// Struct do Mapa, Fonte
typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_FONT* fonte_grande, * fonte_pequena;
    ALLEGRO_TIMER* timer;
    ALLEGRO_BITMAP* mainCharacter;
    ALLEGRO_BITMAP* bg, * parede_baixa, * parede_esquerda, * parede_direita, * parede_direita_baixo, * parede_esquerda_baixo, * parede_cima, * tv, * cama, * mesa, * estante, * porta, * tela_final_beta;
    ALLEGRO_BITMAP* menu_start, * menu_controls, * page_controls, * chat_box;
    ALLEGRO_EVENT_QUEUE* event_queue;
} GameAssets;

// Struct do Menu, posição
typedef struct {
    bool menu;
    bool start;
    int pos_x, pos_y;
    int parede_cima_y, parede_baixa_y, parede_esquerda_x, parede_direita_x;
    bool key_up, key_down, key_left, key_right; // Flags para controle das teclas de movimento
    bool chat;
    bool chat_pergunta_estante, chat_resposta_correta_estante, chat_resposta_errada_estante;
    bool chat_aviso_mesa, mesa_aberta;
    bool chat_aviso_tv, chat_pergunta_tv, chat_para_tv, chat_resposta_errada_tv, chat_resposta_correta_tv;
    bool chave, tela_final;
} GameState;

// Função para inicializar Allegro e os componentes
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
    assets->tela_final_beta = al_load_bitmap("./telaFinal(beta).png");



    assets->event_queue = al_create_event_queue();
    al_register_event_source(assets->event_queue, al_get_display_event_source(assets->display));
    al_register_event_source(assets->event_queue, al_get_timer_event_source(assets->timer));
    al_register_event_source(assets->event_queue, al_get_keyboard_event_source());
    al_start_timer(assets->timer);

}

// Função para limpar os recursos
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
    al_destroy_bitmap(assets->tela_final_beta);
}

// Função para inicializar o estado do jogo
void init_game_state(GameState* state) {
    state->menu = true; // Começa com o menu ativo
    state->start = true; // O cursor do menu começa na opção 'Start'
    state->pos_x = 640;
    state->pos_y = 360;

    // Posições das paredes para impedir que o personagem as atravesse
    state->parede_cima_y = 180;  // Ajuste da colisão na parte superior
    state->parede_baixa_y = 630;
    state->parede_esquerda_x = 343;
    state->parede_direita_x = 970;

    // Inicializa as flags das teclas como falsas
    state->key_up = false;
    state->key_down = false;
    state->key_left = false;
    state->key_right = false;
}

// Função para atualizar a posição do personagem
void update_position(Character* character, GameState* state, GameAssets* assets) {
    bool moving = false; // Verifica se o personagem está se movendo

    // Dimensões e posição da televisão
    int tv_x = 337;
    int tv_y = 200;
    int tv_width = 95;
    int tv_height = 50;

    // Dimensões do canto superior direito (ajustadas)
    int canto_superior_direito_x_min = 900;
    int canto_superior_direito_x_max = 1100;
    int canto_superior_direito_y_min = 180;
    int canto_superior_direito_y_max = 240;

    // Dimensões da cama
    int cama_x = 860; //830
    int cama_y = 150; //250
    int cama_width = al_get_bitmap_width(assets->cama) * 5;
    int cama_height = al_get_bitmap_height(assets->cama) * 5;

    printf("Posição do personagem: X=%d, Y=%d\n", state->pos_x, state->pos_y);

    //só reza, se der bug vai para a igreja se benzer

    //dimensões da esntante

    int estante_x = 680;
    int estante_y = 30;
    int estante_width = al_get_bitmap_width(assets->estante) * 5;
    int estante_height = al_get_bitmap_height(assets->estante) * 5;

    //dimensões mesa

    int mesa_x = 550;
    int mesa_y = 20;
    int mesa_width = al_get_bitmap_width(assets->mesa) * 5;
    int mesa_height = al_get_bitmap_height(assets->mesa) * 5;

    // Verifica colisão somente na direção que o personagem está se movendo
    if (state->key_right && state->pos_x + 90 < state->parede_direita_x) {
        // Colisão ao mover para a direita (TV + cama + canto superior direito + estante + mesa)
        if (!(state->pos_x + 90 >= tv_x && state->pos_x + 90 <= tv_x + tv_width &&
            state->pos_y + 128 > tv_y && state->pos_y < tv_y + tv_height) &&
            !(state->pos_x + 90 >= cama_x && state->pos_x + 90 <= cama_x + cama_width &&
                state->pos_y + 128 > cama_y && state->pos_y < cama_y + cama_height) &&
            !(state->pos_x + 90 >= mesa_x && state->pos_x + 90 <= mesa_x + mesa_width &&
                state->pos_y + 128 > mesa_y && state->pos_y < mesa_y + mesa_height) &&
            !(state->pos_x + 90 >= estante_x && state->pos_x + 90 <= estante_x + estante_width &&
                state->pos_y + 128 > estante_y && state->pos_y < estante_y + estante_height) &&
            !(state->pos_x + 90 >= canto_superior_direito_x_min && state->pos_x + 90 <= canto_superior_direito_x_max &&
                state->pos_y + 128 > canto_superior_direito_y_min && state->pos_y < canto_superior_direito_y_max)) {
            character->frame_y = 128;  // Direção direita
            state->pos_x += 5;
            moving = true;
        }
    }
    if (state->key_left && state->pos_x > state->parede_esquerda_x) {
        // Colisão ao mover para a esquerda (TV + cama + estante + mesa)
        if (!(state->pos_x <= tv_x + tv_width && state->pos_x >= tv_x &&
            state->pos_y + 128 > tv_y && state->pos_y < tv_y + tv_height) &&
            !(state->pos_x <= cama_x + cama_width && state->pos_x >= cama_x &&
                state->pos_y + 128 > cama_y && state->pos_y < cama_y + cama_height) &&
            !(state->pos_x <= mesa_x + mesa_width && state->pos_x >= mesa_x &&
                state->pos_y + 128 > mesa_y && state->pos_y < mesa_y + mesa_height) &&
            !(state->pos_x <= estante_x + estante_width && state->pos_x >= estante_x &&
                state->pos_y + 128 > estante_y && state->pos_y < estante_y + estante_height)) {
            character->frame_y = 128 * 3;  // Direção esquerda
            state->pos_x -= 5;
            moving = true;
        }
    }
    if (state->key_down && state->pos_y + 128 < state->parede_baixa_y) {
        // Colisão ao mover para baixo (TV + cama + canto superior direito + estamte)
        if (!(state->pos_x + 90 > tv_x && state->pos_x < tv_x + tv_width &&
            state->pos_y + 128 >= tv_y && state->pos_y + 128 <= tv_y + tv_height) &&
            !(state->pos_x + 90 > cama_x && state->pos_x < cama_x + cama_width &&
                state->pos_y + 128 >= cama_y && state->pos_y + 128 <= cama_y + cama_height) &&
            !(state->pos_x >= canto_superior_direito_x_min && state->pos_x <= canto_superior_direito_x_max &&
                state->pos_y + 128 >= canto_superior_direito_y_min && state->pos_y + 128 <= canto_superior_direito_y_max)) {
            character->frame_y = 128 * 2;  // Direção para baixo
            state->pos_y += 5;
            moving = true;
        }
    }
    if (state->key_up && state->pos_y > state->parede_cima_y) {
        // Colisão ao mover para cima (TV + cama + canto superior direito + estante + mesa)
        if (!(state->pos_x + 90 > tv_x && state->pos_x < tv_x + tv_width &&
            state->pos_y <= tv_y + tv_height && state->pos_y >= tv_y) &&
            !(state->pos_x + 90 > cama_x && state->pos_x < cama_x + cama_width &&
                state->pos_y <= cama_y + cama_height && state->pos_y >= cama_y) &&
            !(state->pos_x + 90 > mesa_x && state->pos_x < mesa_x + mesa_width &&
                state->pos_y <= mesa_y + mesa_height && state->pos_y >= mesa_y) &&
            !(state->pos_x + 90 > estante_x && state->pos_x < estante_x + estante_width &&
                state->pos_y <= estante_y + estante_height && state->pos_y >= estante_y) &&
            !(state->pos_x + 90 >= canto_superior_direito_x_min && state->pos_x + 90 <= canto_superior_direito_x_max &&
                state->pos_y <= canto_superior_direito_y_max && state->pos_y >= canto_superior_direito_y_min)) {
            character->frame_y = 0;  // Direção para cima
            state->pos_y -= 5;
            moving = true;
        }
    }


    // Atualiza a animação do personagem apenas se ele estiver se movendo
    if (moving) {
        character->frame += 0.2f;
        if (character->frame > 3) {
            character->frame -= 3;
        }
    }
    else {
        // Se não estiver se movendo, o personagem mantém o quadro 0 (parado)
        character->frame = 0;
    }
}

// Função para lidar com as interações no menu
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
            // Mostra a página de controles
            al_draw_bitmap(assets->page_controls, 0, 0, 0);
            al_flip_display();
            al_rest(5.0); // Exibe por 5 segundos
        }
    }
}

// Função para desenhar o cenário, personagem e menu
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
    else {
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

        //interação com a estante
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

        //interação com a mesa
        if (state->chat_aviso_mesa) {
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 420, 520, 0, "parece que tem um papel aqui. diz:");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 420, 560, 0, "\"conto historias e mostro imagens,");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 410, 600, 0, " sem que voce precise sair do lugar\"");
        }

        //interação com a tv
        if (state->chat_aviso_tv) {
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 420, 520, 0, "parece que tem um papel com uma");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 420, 560, 0, "conta na gaveta da tv");
        }

        if (state->chat_resposta_correta_tv) {
            al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 430, 520, 0, "parece estar certo!");
        } if (state->chat_resposta_errada_tv){
            al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 430, 520, 0, "isso parece um pouco errado!");
        }

        if (state->chat_pergunta_tv) {

            al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 400, 520, 0, "x ao quadrado menos dois,");
            al_draw_text(assets->fonte_grande, al_map_rgb(255, 255, 255), 400, 550, 0, "tudo isso elevado a dois");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 500, 600, 0, "3");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 900, 600, 0, "4");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 500, 640, 0, "5");
            al_draw_text(assets->fonte_pequena, al_map_rgb(255, 255, 255), 900, 640, 0, "2");
        } 

        //interação do final aaaaaaa
        if (state->tela_final) {
            al_draw_bitmap_region(assets->tela_final_beta, 0, 0, 1280, 720, 0, 0, 0);
        }
    }
}


//calcula a distância entre o jogador e a estante
int player_interacao_estante(Character* character, GameState* state, GameAssets* assets) {
    int range_interacao = 120;

    int estante_x = 660;
    int estante_y = 125;

    int dx_estante = state->pos_x - estante_x;
    int dy_estante = state->pos_y - estante_y;
    return (dx_estante * dx_estante + dy_estante * dy_estante) <= (range_interacao * range_interacao);
}

//calcula a distância entre o jogador e a mesa
int player_interacao_mesa(Character* character, GameState* state, GameAssets* assets) {
    int range_interacao = 120;

    int mesa_x = 550;
    int mesa_y = 150;

    int dx_mesa = state->pos_x - mesa_x;
    int dy_mesa = state->pos_y - mesa_y;
    return (dx_mesa * dx_mesa + dy_mesa * dy_mesa) <= (range_interacao * range_interacao);
}

//calcula a distância entre o jogador e a tv
int player_interacao_tv(Character* character, GameState* state, GameAssets* assets) {
    int range_interacao = 120;

    int tv_x = 337;
    int tv_y = 200;

    int dx_tv = state->pos_x - tv_x;
    int dy_tv = state->pos_y - tv_y;
    return (dx_tv * dx_tv + dy_tv * dy_tv) <= (range_interacao * range_interacao);
}

//calcula a distância entre o jogador e a chave
int player_interacao_porta(Character* character, GameState* state, GameAssets* assets) {
    int range_interacao = 120;

    int porta_x = 460;
    int porta_y = 127;

    int dx_porta = state->pos_x - porta_x;
    int dy_porta = state->pos_y - porta_y;
    return (dx_porta * dx_porta + dy_porta * dy_porta) <= (range_interacao * range_interacao);
}

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
    state.tela_final = false;

    init_allegro(&assets);
    init_game_state(&state);

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(assets.event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
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

                //interação da mesa quando a gaveta está fechada
                if (player_interacao_mesa(&character, &state, &assets)) {
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
                if (player_interacao_tv(&character, &state, &assets)) {
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
                if (player_interacao_estante(&character, &state, &assets)) {
                    printf("dentro da interação - ESTANTE\n");
                
                    if (event.keyboard.keycode == ALLEGRO_KEY_Z && !state.chat_resposta_correta_estante && !state.chat_resposta_errada_estante) {
                    
                        state.chat_pergunta_estante = true;
                        state.chat = true;
                    }
                    if (event.keyboard.keycode == ALLEGRO_KEY_1 || event.keyboard.keycode == ALLEGRO_KEY_3
                        || event.keyboard.keycode == ALLEGRO_KEY_4 && state.chat_pergunta_estante) {
                        state.chat_resposta_errada_estante = true;
                        state.chat_pergunta_estante = false;
                    }
                    if (event.keyboard.keycode == ALLEGRO_KEY_2 && state.chat_pergunta_estante) {
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
            }
            //interação final

            if (state.chave) {
                if (player_interacao_porta(&character, &state, &assets) && event.keyboard.keycode == ALLEGRO_KEY_Z) {
                    printf("dentro da interação - PORTA\n");
                    state.tela_final = true;
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
        al_flip_display();
    }

    destroy_assets(&assets);
    return 0;
}
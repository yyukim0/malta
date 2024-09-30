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
    ALLEGRO_FONT* font;
    ALLEGRO_TIMER* timer;
    ALLEGRO_BITMAP* mainCharacter;
    ALLEGRO_BITMAP* bg, * bottom_wall, * left_wall, * right_wall, * bottom_right_wall, * bottom_left_wall, * top_wall;
    ALLEGRO_BITMAP* menu_start, * menu_controls, * page_controls;
    ALLEGRO_EVENT_QUEUE* event_queue;
} GameAssets;

// Struct do Menu, posição
typedef struct {
    bool menu;
    bool start;
    int pos_x, pos_y;
    int top_wall_y, bottom_wall_y, left_wall_x, right_wall_x;
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
    al_set_window_title(assets->display, "Opia");

    assets->font = al_load_font("./YumeNikkiTitleScreen.ttf", 25, 0);
    assets->timer = al_create_timer(1.0 / 60.0);

    // Carregando imagens
    assets->mainCharacter = al_load_bitmap("./mc - precisamos decidir um nome.png");
    assets->bg = al_load_bitmap("./quarto inteiro.png");
    assets->bottom_wall = al_load_bitmap("./parede - baixo.png");
    assets->left_wall = al_load_bitmap("./parede - lado.png");
    assets->right_wall = al_load_bitmap("./parede - lado.png");
    assets->bottom_right_wall = al_load_bitmap("./parede - canto - direita.png");
    assets->bottom_left_wall = al_load_bitmap("./parede - canto - esquerda.png");
    assets->top_wall = al_load_bitmap("./parede - cima.png");
    assets->menu_start = al_load_bitmap("./menu - start.png");
    assets->menu_controls = al_load_bitmap("./menu - controls.png");
    assets->page_controls = al_load_bitmap("./controls.png");

    assets->event_queue = al_create_event_queue();
    al_register_event_source(assets->event_queue, al_get_display_event_source(assets->display));
    al_register_event_source(assets->event_queue, al_get_display_event_source(assets->timer));
    al_register_event_source(assets->event_queue, al_get_keyboard_event_source());
    al_start_timer(assets->timer);
}

// Função para limpar os recursos
void destroy_assets(GameAssets* assets) {
    al_destroy_bitmap(assets->menu_start);
    al_destroy_bitmap(assets->top_wall);
    al_destroy_bitmap(assets->bottom_left_wall);
    al_destroy_bitmap(assets->bottom_right_wall);
    al_destroy_bitmap(assets->right_wall);
    al_destroy_bitmap(assets->left_wall);
    al_destroy_bitmap(assets->mainCharacter);
    al_destroy_bitmap(assets->bottom_wall);
    al_destroy_bitmap(assets->bg);
    al_destroy_font(assets->font);
    al_destroy_display(assets->display);
    al_destroy_event_queue(assets->event_queue);
}

// Função para inicializar o estado do jogo
void init_game_state(GameState* state) {
    state->menu = true;  // Começa com o menu ativo
    state->start = true; // O cursor do menu começa na opção 'Start'
    state->pos_x = 640;
    state->pos_y = 360;
    
    // Posições das paredes para impedir que o personagem as atravesse
    state->top_wall_y = 200;
    state->bottom_wall_y = 630;
    state->left_wall_x = 343;
    state->right_wall_x = 970;
}

// Função para atualizar a posição do personagem
void update_position(Character* character, GameState* state, int keycode) {
    if (keycode == ALLEGRO_KEY_RIGHT) {
        character->frame_y = 128; 
        if (state->pos_x + 90 < state->right_wall_x) {
            state->pos_x += 10;
        }
    }
    else if (keycode == ALLEGRO_KEY_LEFT) {
        character->frame_y = 128 * 3;
        if (state->pos_x > state->left_wall_x) {
            state->pos_x -= 10;
        }
    }
    else if (keycode == ALLEGRO_KEY_DOWN) {
        character->frame_y = 128 * 2;
        if (state->pos_y + 128 < state->bottom_wall_y) {
            state->pos_y += 10;
        }
    }
    else if (keycode == ALLEGRO_KEY_UP) {
        character->frame_y = 0;
        if (state->pos_y > state->top_wall_y) {
            state->pos_y -= 10;
        }
    }

    character->frame += 0.4f;
    if (character->frame > 3) {
        character->frame -= 3;
    }
}

// Função para lidar com as interações no menu
void handle_menu_interactions(GameState* state, GameAssets* assets, int keycode) {
    if (keycode == ALLEGRO_KEY_DOWN) {
        state->start = false; // Alterna para 'Controls'
    }
    else if (keycode == ALLEGRO_KEY_UP) {
        state->start = true;  // Alterna para 'Start'
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
        al_draw_bitmap_region(assets->top_wall, 0, 0, 503, 145, 405, 108, 0);
        al_draw_bitmap_region(assets->bottom_right_wall, 0, 0, 69, 210, 905, 108, 0);
        al_draw_bitmap_region(assets->bottom_left_wall, 0, 0, 69, 210, 340, 108, 0);
        al_draw_bitmap_region(assets->left_wall, 0, 0, 18, 465, 325, 170, 0);
        al_draw_bitmap_region(assets->right_wall, 0, 0, 18, 465, 970, 170, 0);
        al_draw_bitmap_region(assets->bottom_wall, 0, 0, 672, 17, 320, 630, 0);
        al_draw_bitmap_region(assets->mainCharacter, 100 * (int)character->frame, character->frame_y, 90, 128, state->pos_x, state->pos_y, 0);
    }
}

// Função principal
int main(void) {
    GameAssets assets;
    GameState state;
    Character character = { 640, 360, 0, 128, 0 };

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
                update_position(&character, &state, event.keyboard.keycode);
            }
        }

        draw_game(&assets, &state, &character);
        al_flip_display();
    }

    destroy_assets(&assets);
    return 0;
}

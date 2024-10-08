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
ALLEGRO_BITMAP* bg, * parede_baixa, * parede_esquerda, * parede_direita, * parede_direita_baixo, * parede_esquerda_baixo, * parede_cima, * tv, * cama;
ALLEGRO_BITMAP* menu_start, * menu_controls, * page_controls;
ALLEGRO_EVENT_QUEUE* event_queue;
} GameAssets;

// Struct do Menu, posição
typedef struct {
bool menu;
bool start;
int pos_x, pos_y;
int parede_cima_y, parede_baixa_y, parede_esquerda_x, parede_direita_x;
bool key_up, key_down, key_left, key_right; // Flags para controle das teclas de movimento
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

assets->font = al_load_font("./YumeNikkiTitleScreen.ttf", 25, 0);
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
assets->page_controls = al_load_bitmap("./controls.png");

assets->event_queue = al_create_event_queue();
al_register_event_source(assets->event_queue, al_get_display_event_source(assets->display));
al_register_event_source(assets->event_queue, al_get_timer_event_source(assets->timer));
al_register_event_source(assets->event_queue, al_get_keyboard_event_source());
al_start_timer(assets->timer);
}

// Função para limpar os recursos
void destroy_assets(GameAssets* assets) {
al_destroy_bitmap(assets->menu_start);
al_destroy_bitmap(assets->parede_cima);
al_destroy_bitmap(assets->parede_esquerda_baixo);
al_destroy_bitmap(assets->parede_direita_baixo);
al_destroy_bitmap(assets->parede_direita);
al_destroy_bitmap(assets->parede_esquerda);
al_destroy_bitmap(assets->mainCharacter);
al_destroy_bitmap(assets->parede_baixa);
al_destroy_bitmap(assets->bg);
al_destroy_font(assets->font);
al_destroy_display(assets->display);
al_destroy_event_queue(assets->event_queue);
al_destroy_bitmap(assets->tv);
al_destroy_bitmap(assets->cama);
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
int canto_superior_direito_x_min = 900; // Ajuste conforme necessário
int canto_superior_direito_x_max = 1100; // Ajuste conforme necessário
int canto_superior_direito_y_min = 180; // Ajuste conforme necessário
int canto_superior_direito_y_max = 240; // Ajuste conforme necessário

// Dimensões da cama
int cama_x = 750;
int cama_y = 100;
int cama_width = al_get_bitmap_width(assets->cama) * 5;
int cama_height = al_get_bitmap_height(assets->cama) * 5;

printf("Posição do personagem: X=%d, Y=%d\n", state->pos_x, state->pos_y);

// Verifica colisão somente na direção que o personagem está se movendo
if (state->key_right && state->pos_x + 90 < state->parede_direita_x) {
    // Colisão ao mover para a direita (TV + cama + canto superior direito)
    if (!(state->pos_x + 90 >= tv_x && state->pos_x + 90 <= tv_x + tv_width &&
        state->pos_y + 128 > tv_y && state->pos_y < tv_y + tv_height) &&
        !(state->pos_x + 90 >= cama_x && state->pos_x + 90 <= cama_x + cama_width &&
            state->pos_y + 128 > cama_y && state->pos_y < cama_y + cama_height) &&
        !(state->pos_x + 90 >= canto_superior_direito_x_min && state->pos_x + 90 <= canto_superior_direito_x_max &&
            state->pos_y + 128 > canto_superior_direito_y_min && state->pos_y < canto_superior_direito_y_max)) {
        character->frame_y = 128;  // Direção direita
        state->pos_x += 5;
        moving = true;
    }
}
if (state->key_left && state->pos_x > state->parede_esquerda_x) {
    // Colisão ao mover para a esquerda (TV + cama)
    if (!(state->pos_x <= tv_x + tv_width && state->pos_x >= tv_x &&
        state->pos_y + 128 > tv_y && state->pos_y < tv_y + tv_height) &&
        !(state->pos_x <= cama_x + cama_width && state->pos_x >= cama_x &&
            state->pos_y + 128 > cama_y && state->pos_y < cama_y + cama_height)) {
        character->frame_y = 128 * 3;  // Direção esquerda
        state->pos_x -= 5;
        moving = true;
    }
}
if (state->key_down && state->pos_y + 128 < state->parede_baixa_y) {
    // Colisão ao mover para baixo (TV + cama + canto superior direito)
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
    // Colisão ao mover para cima (TV + cama + canto superior direito)
    if (!(state->pos_x + 90 > tv_x && state->pos_x < tv_x + tv_width &&
        state->pos_y <= tv_y + tv_height && state->pos_y >= tv_y) &&
        !(state->pos_x + 90 > cama_x && state->pos_x < cama_x + cama_width &&
            state->pos_y <= cama_y + cama_height && state->pos_y >= cama_y) &&
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
750, 195, al_get_bitmap_width(assets->cama) * 5, al_get_bitmap_height(assets->cama) * 5, 0);
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
            // Atualiza as flags de acordo com a tecla pressionada
            if (event.keyboard.keycode == ALLEGRO_KEY_UP) state.key_up = true;
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) state.key_down = true;
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) state.key_left = true;
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) state.key_right = true;
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

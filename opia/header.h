#ifndef HEADER_H
#define HEADER_H

// Struct do Mapa, Fonte
typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_FONT* fonte_grande, * fonte_pequena;
    ALLEGRO_TIMER* timer;
    ALLEGRO_BITMAP* mainCharacter;
    ALLEGRO_BITMAP* bg, * parede_baixa, * parede_esquerda, * parede_direita, * parede_direita_baixo, * parede_esquerda_baixo, * parede_cima, * tv, * cama, * mesa, * estante, * porta, * tela_final_beta;
    ALLEGRO_BITMAP* bg_sala2, * parede_sala2, * parede_baixa_sala2, * parede_canto_direita_sala2, * parede_canto_esquerda_sala2, * parede_cima_sala2, * parede_curta_sala2, * parede_lados_sala2, * porta_sala2, * abajur, * balcao, * banheira, * mesa2, * cadeiradireita, * cadeiraesquerda, * panela, * poca, * portaretrato, * tapete2, * estante2, * cabide, * fotos, * relogio;
    ALLEGRO_BITMAP* menu_start, * menu_controls, * page_controls, * chat_box;
    ALLEGRO_EVENT_QUEUE* event_queue;
} GameAssets;

// Struct do Personagem Principal
typedef struct {
    int x, y;
    int frame_x, frame_y;
    float frame;
} Character;

// Struct do Menu, posição
typedef struct {
    bool menu;
    bool start;
    int pos_x, pos_y;
    int parede_cima_y, parede_baixa_y, parede_esquerda_x, parede_direita_x;
    int parede2_cima_y, parede2_baixa_y, parede2_esquerda_x, parede2_direita_x;
    bool key_up, key_down, key_left, key_right;
    bool chat;
    bool chat_pergunta_estante, chat_resposta_correta_estante, chat_resposta_errada_estante;
    bool chat_aviso_mesa;
    bool chat_aviso_tv, chat_pergunta_tv, chat_para_tv, chat_resposta_errada_tv, chat_resposta_correta_tv;
    bool chave, chave_banheira;
    bool chat2;
    bool chat_aviso_estante2, chat_aviso_abajur, segundo_chat_aviso_abajur, chat_aviso_relogio, chat_aviso_retrato, segundo_chat_aviso_retrato, chat_aviso_banheira;
    bool chat_aviso_porta_sem_chave, chat_aviso_banheira_com_chave, chat_resposta_errada_porta, chat_pergunta_porta, endgame;
    bool mapa1, mapa2;
} GameState;

void init_allegro(GameAssets* assets);
void destroy_assets(GameAssets* assets);
void init_game_state(GameState* state);
void update_position(Character* character, GameState* state, GameAssets* assets);
void handle_menu_interactions(GameState* state, GameAssets* assets, int keycode);
void draw_game(GameAssets* assets, GameState* state, Character* character);


#endif 

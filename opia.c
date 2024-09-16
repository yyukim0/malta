//Importar as Bibliotecas
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
// 77 - Largura
// 95 - Altura


//Funcao Inicial
int main() {

    //Declaracoes do Inicio do Codigo
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    
    //Aba Inicial
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Opia");

    //Declarando Fonte e o Tic
    ALLEGRO_FONT* font = al_load_font("./YumeNikkiTitleScreen.ttf", 25, 0);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    //Declarando Imagem
    ALLEGRO_BITMAP* mainCharacter = al_load_bitmap("./mc - precisamos decidir um nome.png");

    //Fila de Eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    //Declarando X e Y da Imagem do Personagem
    float frame = 0.f;
    int pos_x = 0, pos_y = 0;
    int current_frame_y = 95;

    //Caso de Error 
    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
            //Movimentacao do Character
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
            current_frame_y = 95;
            pos_x += 10; //velocidade
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
            current_frame_y = 95 * 3;
            pos_x -= 10;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
            current_frame_y = 95 * 2;
            pos_y += 10;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
            current_frame_y = 0;
            pos_y -= 10;
        }
        frame += 0.03f; //3 frames
        if (frame > 3) { //se passar de 3 frames
            frame -= 3; //volta para o frame inicial
        }

        //Desenhar ou Printar os Arquivos na Tela
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap_region(mainCharacter, 70 * (int)frame, current_frame_y, 77, 95, pos_x, pos_y, 0);
        al_flip_display();
    }

    //Encerrando e Fechando as Fila de Eventos
    al_destroy_bitmap(mainCharacter);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
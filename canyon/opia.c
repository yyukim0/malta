//Importar as Bibliotecas
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
// 79 / 3 -> 26 - Largura
// 128 / 4 -> 32 - Altura


//Funcao Inicial
int main() {

    //Declaracoes do Inicio do Codigo
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();

    //Aba Inicial
    ALLEGRO_DISPLAY* display = al_create_display(640, 480);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Esta Funcionando!");

    //Declarando Fonte e o Tic
    ALLEGRO_FONT* font = al_load_font("./YumeNikkiTitleScreen.ttf", 25, 0);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    //Declarando Imagem
    ALLEGRO_BITMAP* sprite = al_load_bitmap("./mc - precisamos decidir um nome.png");
    //ALLEGRO_BITMAP* bg = al_load_bitmap("./bg.PNG");

    //Fila de Eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    //Declarando X e Y da Imagem do Personagem
    float frame = 0.f;
    int pos_x = 0, pos_y = 0;
    int current_frame_y = 32;

    //Caso de Error 
    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
            //Movimentacao do Character
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
            current_frame_y = 36;
            pos_x += 10;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
            current_frame_y = 33 * 3;
            pos_x -= 10;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
            current_frame_y = 33 * 2;
            pos_y += 10;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
            current_frame_y = 0;
            pos_y -= 10;
        }
        //Tic com a Imagem do Character
        frame += 0.03f;
        if (frame > 3) {
            frame -= 3;
        }

        //Desenhar ou Printar os Arquivos na Tela
        al_clear_to_color(al_map_rgb(0, 0, 0));
        //al_draw_text(font, al_map_rgb(0, 0, 0), 230, 200, 0, "Esta Funcionando!");
        //al_draw_bitmap(bg, 0, 0, 0);
        al_draw_bitmap_region(sprite, 36 * (int)frame, current_frame_y, 28, 26, pos_x, pos_y, 0);
        al_flip_display();
    }

    //Encerrando e Fechando as Fila de Eventos
    //al_destroy_bitmap(bg);
    al_destroy_bitmap(sprite);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

// Função inicial
int main(void) {
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_keyboard();

	// Aba inicial
	ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
	al_set_window_position(display, 200, 200);
	al_set_window_title(display, "Opia");

	// Declarando fonte e o timer
	ALLEGRO_FONT* font = al_load_font("./YumeNikkiTitleScreen.ttf", 25, 0);
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

	// Declarando imagens
	ALLEGRO_BITMAP* mainCharacter = al_load_bitmap("./mc - precisamos decidir um nome.png");
	ALLEGRO_BITMAP* bg = al_load_bitmap("./quarto inteiro.png");
	ALLEGRO_BITMAP* bottom_wall = al_load_bitmap("./parede - baixo.png");
	ALLEGRO_BITMAP* left_wall = al_load_bitmap("./parede - lado.png");
	ALLEGRO_BITMAP* right_wall = al_load_bitmap("./parede - lado.png");
	ALLEGRO_BITMAP* bottom_right_wall = al_load_bitmap("./parede - canto - direita.png");
	ALLEGRO_BITMAP* bottom_left_wall = al_load_bitmap("./parede - canto - esquerda.png");
	ALLEGRO_BITMAP* top_wall = al_load_bitmap("./parede - cima.png");
	ALLEGRO_BITMAP* menu_start = al_load_bitmap("./menu - start.png");
	ALLEGRO_BITMAP* menu_controls = al_load_bitmap("./menu - controls.png");
	ALLEGRO_BITMAP* page_controls = al_load_bitmap("./controls.png");

	// Fila de eventos
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_display_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_start_timer(timer);

	// Variáveis do menu
	bool menu = true;
	bool start = true;

	// Coordenadas do personagem
	float frame = 0.f;
	int pos_x = 640, pos_y = 360;
	int current_frame_y = 128;

	// Limites da sala (ajustar conforme necessário)
	int top_wall_y = 150 + 50; //150 + 145;
	int bottom_wall_y = 630;
	int left_wall_x = 325 + 18;
	int right_wall_x = 970;

	// Eventos
	while (true) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
			current_frame_y = 128;
			// Verifica colisão com a parede direita
			if (pos_x + 90 < right_wall_x) {
				pos_x += 10; // Velocidade
			}
			frame += 0.4f;
			if (frame > 3) {
				frame -= 3;
			}
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
			current_frame_y = 128 * 3;
			// Verifica colisão com a parede esquerda
			if (pos_x > left_wall_x) {
				pos_x -= 10; // Velocidade
			}
			frame += 0.4f;
			if (frame > 3) {
				frame -= 3;
			}
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			current_frame_y = 128 * 2;
			// Verifica colisão com a parede inferior
			if (pos_y + 128 < bottom_wall_y) {
				pos_y += 10; // Velocidade
			}
			frame += 0.4f;
			if (frame > 3) {
				frame -= 3;
			}
		}
		else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
			current_frame_y = 0;
			// Verifica colisão com a parede superior
			if (pos_y > top_wall_y) {
				pos_y -= 10; // Velocidade
			}
			frame += 0.4f;
			if (frame > 3) {
				frame -= 3;
			}
		}

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap_region(bg, -30, 0, 1280, 720, 0, 50, 0);
		al_draw_bitmap_region(top_wall, 0, 0, 503, 145, 405, 108, 0);
		al_draw_bitmap_region(bottom_right_wall, 0, 0, 69, 210, 905, 108, 0);
		al_draw_bitmap_region(bottom_left_wall, 0, 0, 69, 210, 340, 108, 0);
		al_draw_bitmap_region(left_wall, 0, 0, 18, 465, 325, 170, 0);
		al_draw_bitmap_region(right_wall, 0, 0, 18, 465, 970, 170, 0);
		al_draw_bitmap_region(bottom_wall, 0, 0, 672, 17, 320, 630, 0);
		al_draw_bitmap_region(mainCharacter, 100 * (int)frame, current_frame_y, 90, 128, pos_x, pos_y, 0);


		if (menu) {
			if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
					start = false; 
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
					start = true; 
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_Z) {
					if (start) {
						menu = false; 
					}
					else {
						al_draw_bitmap(page_controls, 0, 0, 0);
						al_flip_display();
						al_rest(5.0); 
					}
				}
			}

			al_clear_to_color(al_map_rgb(0, 0, 0)); 
			if (start) {
				al_draw_bitmap_region(menu_start, 0, 0, 1280, 720, 0, 0, 0);
			}
			else {
				al_draw_bitmap_region(menu_controls, 0, 0, 1280, 720, 0, 0, 0);
			}
		}

		al_flip_display();
	}

	al_destroy_bitmap(menu_start);
	al_destroy_bitmap(top_wall);
	al_destroy_bitmap(bottom_left_wall);
	al_destroy_bitmap(bottom_right_wall);
	al_destroy_bitmap(right_wall);
	al_destroy_bitmap(left_wall);
	al_destroy_bitmap(mainCharacter);
	al_destroy_bitmap(bottom_wall);
	al_destroy_bitmap(bg);
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

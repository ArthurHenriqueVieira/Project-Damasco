#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>

int main(){
	ALLEGRO_DISPLAY *display = NULL;

	ALLEGRO_FONT *font = NULL;

	al_init();
	al_init_font_addon();
	al_init_ttf_addon();

	al_create_display(640, 480);
	font = al_load_font("Arial.TTF", 48, 0);
	if(!font){
		al_destroy_display(display);
		fprintf(stderr, "Erro ao carregar imagem");
		return -1;
	}
	al_clear_to_color(al_map_rgb(255,255,255));

	al_draw_text(font, al_map_rgb(0,0,0), 10, 10, ALLEGRO_ALIGN_CENTRE, "Hello World");

	al_flip_display();

	al_rest(5.0);

	al_destroy_font(font);
	al_destroy_display(display);
	return 0;
}
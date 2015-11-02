#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define LARGURA 1280
#define ALTURA 720

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *image = NULL, *bee = NULL;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_FONT *font = NULL;

bool initialize();

int main(){
	bool exit = false;
	bool over = false, over2 = false, over3 = false;

	float raio = 30.0;
    float x = raio;
    float y = raio;
    int dir_x = 1, dir_y = 1;
    int oi =false;

	initialize();

	while(!exit){
		ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        
        al_draw_bitmap(image, 0, 0, 0);
        /// - Analise onde esta o mouse - ///
        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
	        if (ev.mouse.x >= 530 && ev.mouse.x <= 730 && ev.mouse.y >= 300 && ev.mouse.y <= 340){
	        	over = true;
	        }else over = false;

	        if (ev.mouse.x >= 500 && ev.mouse.x <= 760 && ev.mouse.y >= 350 && ev.mouse.y <= 390){
	        	over2 = true;
	        }else over2 = false;

	        if (ev.mouse.x >= 560 && ev.mouse.x <= 700 && ev.mouse.y >= 400 && ev.mouse.y <= 440){
	        	over3 = true;
	        }else over3 = false;
        }
       	
       	/// Colore e escreve dependendo da posicao do mouse ///
       	if(!over)
			al_draw_text(font, al_map_rgb(0,0,0), 630, 300,ALLEGRO_ALIGN_CENTRE, "Jogar");
       	else al_draw_text(font, al_map_rgb(255,255,255), 630, 300,ALLEGRO_ALIGN_CENTRE, "Jogar");
       	
       	if(!over2)
       		al_draw_text(font, al_map_rgb(0,0,0), 630, 350,ALLEGRO_ALIGN_CENTRE, "Tutorial");
        else al_draw_text(font, al_map_rgb(255,255,255), 630, 350,ALLEGRO_ALIGN_CENTRE, "Tutorial");
        
        if(!over3)	
        	al_draw_text(font, al_map_rgb(0,0,0), 630, 400,ALLEGRO_ALIGN_CENTRE, "Sair");
        else al_draw_text(font, al_map_rgb(255,255,255), 630, 400,ALLEGRO_ALIGN_CENTRE, "Sair");

        al_draw_bitmap(bee, x, y, ALLEGRO_FLIP_HORIZONTAL*oi);

        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
        
        x += 2 * dir_x;
        y += 2 * dir_y;        
 
        if (x >= LARGURA - raio)
        {
            dir_x = -1;
            x = LARGURA - raio;
        } else if (x <= raio) {
            dir_x = 1;
            x = raio;
        }
 
        if (y >= ALTURA - raio)
        {
            dir_y = -1;
            y = ALTURA - raio;
        } else if (y <= raio) {
            dir_y = 1;
            y = raio;
        }
		if(x >= LARGURA - raio){
			oi = true;
		}else if(x <= 30)
			oi = false;
		
	}

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(image);
	al_destroy_bitmap(bee);
	al_destroy_timer(timer);
	al_destroy_font(font);

}

bool initialize(){
        if(!al_init()){
            fprintf(stderr, "failed to initialize allegro!\n");
            return -1;
        }
        
        display = al_create_display(LARGURA, ALTURA);
        
        if(!display){
            fprintf(stderr, "failed to create display!\n");
            return -1;
        }

        if (!al_install_audio()){
            fprintf(stderr, "Falha ao inicializar áudio.\n");
            return false;
        }
     
        if (!al_init_acodec_addon()){
            fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
            return false;
        }
     
        if (!al_reserve_samples(1)){
            fprintf(stderr, "Falha ao alocar canais de áudio.\n");
            return false;
        }

        if(!al_install_keyboard()){
          fprintf(stderr, "failed to initialize the keyboard!\n");
          return -1;
        }
        
        if(!al_install_mouse()){
          fprintf(stderr, "failed to initialize the mouse!\n");
          return -1;
        }

        if(!al_init_image_addon()){
            fprintf(stderr, "failed to initialize image\n");
            return -1;
        }
        al_init_font_addon();
        
        if (!al_init_ttf_addon()){
            fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
            return -1;
        }
        
        event_queue = al_create_event_queue();
        
        if(!event_queue) {
            fprintf(stderr, "failed to create event_queue!\n");
            al_destroy_display(display);
            return -1;
        }

        font = al_load_font("04B_30__.ttf", 45, 0);
        if(!font){
            al_destroy_display(display);
            fprintf(stderr, "Erro ao carregar fonte\n");
            return -1;
        }
        
        image = al_load_bitmap("menu.jpg");
        bee = al_load_bitmap("bee.png");
  
        timer = al_create_timer(1.0/60);
        
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_mouse_event_source());
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
       
        al_start_timer(timer);
        
        return true;
    }
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
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_AUDIO_STREAM *musica = NULL;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_BITMAP *area_central=0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

bool initialize();

int main(){
    bool exit = false;
    if (!initialize()){
        return -1;
    }

    al_draw_bitmap(image, 0, 0, 0);
    al_flip_display();

    while(!exit){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        al_draw_bitmap(image, 0, 0, 0);
        al_draw_line(1150, 500, 200, 500,al_map_rgb(0,0,0), 3);
        al_draw_line(250, 550, 250, 50,al_map_rgb(0,0,0), 3);
            
            if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);  
        }
        
        al_flip_display();
    }

    al_destroy_sample(sample);
    al_destroy_bitmap(image);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_audio_stream(musica);
   
    return 0;
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

    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return -1;
    }
    musica = al_load_audio_stream("bits.ogg", 4, 1024);
    if (!musica)
    {
        fprintf(stderr, "Falha ao carregar audio.\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_sample(sample);
        return false;
    }
    
    sample = al_load_sample("palmas.wav");
    if (!sample)
    {
        fprintf(stderr, "Falha ao carregar sample.\n");
        al_destroy_display(display);
        return false;
    }
    event_queue = al_create_event_queue();
    
    if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        return -1;
    }
    
    image = al_load_bitmap("ciao.jpg");
    
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    return true;
}
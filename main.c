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

ALLEGRO_TIMER *timer;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *image2 = NULL;
ALLEGRO_AUDIO_STREAM *musica = NULL;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_BITMAP *botao=0, *botao_g = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_FONT *font = NULL, *font2 = NULL;

enum FUNC{CONS, PRIM, SEC};
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};

typedef struct
{
    float x;
    float y;
    float velX;
    float velY;
    int dirX;
    int dirY;
    int width;
    int height;

    ALLEGRO_BITMAP *image;

}Background;

Background BG;

bool initialize();
void coordenadas();
void segundograu(float a, float b, float c);

struct projetil
{
    float x;
    float y;

    float raio;
};

struct projetil bala;

// Background
void initback(Background *fundo, float x, float y, float velx, int width, int height, int dirX, ALLEGRO_BITMAP *image);
void updateback(Background *fundo);
void drawback(Background *fundo);

int main(){
    bool exit = false;
    bool render = false;
    bool keys[5] = {false,false,false,false,false};
    bool func[3] = {false, false, false};
    int a = 0;
    int b = 0;
    int c = 0;
    int x, y;

    initialize();
   
    while(!exit){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:    
                    a += 1;
                    break;
                case ALLEGRO_KEY_DOWN:
                    a -= 1;
                    break;
                case ALLEGRO_KEY_LEFT:
                    b -= 1;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    b += 1;
                    break;
                case ALLEGRO_KEY_SPACE:
                    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); 
                    keys[SPACE] = true;
                    break; 
            }
        }else if(ev.type == ALLEGRO_EVENT_KEY_UP){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:    
                    keys[UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    exit = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = false;
                    break;
            } 
        }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        
        }else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if(!func[0] && !func[1] && !func[2]){
                    if (ev.mouse.x >= 216 && ev.mouse.x <= 416 && ev.mouse.y >= 575 && ev.mouse.y <= 675){
                            func[CONS] = true;
                    }else if (ev.mouse.x >= 560 && ev.mouse.x <= 760 && ev.mouse.y >= 575 && ev.mouse.y <= 675){
                            func[PRIM] = true;
                    }else if (ev.mouse.x >= 890 && ev.mouse.x <= 1090 && ev.mouse.y >= 575 && ev.mouse.y <= 675){
                            func[SEC] = true;
                    }
                }
                
                if(func[0]){
                    if (ev.mouse.x >= 695 && ev.mouse.x <= 725 && ev.mouse.y >= 570 && ev.mouse.y <= 600){
                        b += 1;
                    }else if (ev.mouse.x >= 695 && ev.mouse.x <= 725 && ev.mouse.y >= 650 && ev.mouse.y <= 685){
                        b -= 1;
                    }
                }else if(func[1]){
                    if (ev.mouse.x >= 515 && ev.mouse.x <= 545 && ev.mouse.y >= 570 && ev.mouse.y <= 600){
                        a += 1;
                    }else if (ev.mouse.x >= 515 && ev.mouse.x <= 545 && ev.mouse.y >= 650 && ev.mouse.y <= 685){
                        a -= 1;
                    }else if (ev.mouse.x >= 730 && ev.mouse.x <= 760 && ev.mouse.y >= 570 && ev.mouse.y <= 600){
                        b += 1;
                    }else if (ev.mouse.x >= 730 && ev.mouse.x <= 760 && ev.mouse.y >= 650 && ev.mouse.y <= 685){
                        b -= 1;
                    }
                }else if(func[2]){
                    if (ev.mouse.x >= 515 && ev.mouse.x <= 545 && ev.mouse.y >= 570 && ev.mouse.y <= 600){
                        a += 1;
                    }else if (ev.mouse.x >= 515 && ev.mouse.x <= 545 && ev.mouse.y >= 650 && ev.mouse.y <= 685){
                        a -= 1;
                    }else if (ev.mouse.x >= 730 && ev.mouse.x <= 760 && ev.mouse.y >= 570 && ev.mouse.y <= 600){
                        b += 1;
                    }else if (ev.mouse.x >= 730 && ev.mouse.x <= 760 && ev.mouse.y >= 650 && ev.mouse.y <= 685){
                        b -= 1;
                    }else if (ev.mouse.x >= 945 && ev.mouse.x <= 975 && ev.mouse.y >= 570 && ev.mouse.y <= 600){
                        c += 1;
                    }else if (ev.mouse.x >= 945 && ev.mouse.x <= 975 && ev.mouse.y >= 650 && ev.mouse.y <= 685){
                        c -= 1;
                    }
                }
                    if (ev.mouse.x >= 1100 && ev.mouse.x <= 1230 && ev.mouse.y >= 670 && ev.mouse.y <= 700){
                        func[0] = false;
                        func[1] = false;
                        func[2] = false;
                        a = 0;
                        b = 0;
                        c = 0;
                        x = 0;
                        y = 0;
                    }
            }
        if(ev.type == ALLEGRO_EVENT_TIMER){
            updateback(&BG);
            render = true;
        }
        
        if(render && al_is_event_queue_empty(event_queue)){
            drawback(&BG);
            al_draw_bitmap(image2, 0, 480, 0);
            //    x=a;
            //    y=b;
            //coordenadas(&x,&y);
            segundograu(a,b,c);
            al_draw_circle(x, y, 10, al_map_rgb(0, 0, 0), 2.0);
            al_draw_line(1150, 500, 200, 500,al_map_rgb(0,0,0), 3);
            al_draw_line(250, 550, 250, 50,al_map_rgb(0,0,0), 3);
            
            al_set_target_bitmap(botao);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_set_target_bitmap(botao_g);
            al_clear_to_color(al_map_rgb(0,0,0));

            al_set_target_bitmap(al_get_backbuffer(display));
            if(func[0] || func[1] || func[2]){
                al_draw_text(font2, al_map_rgb(0,0,0), 1100, 670, 0, "Voltar");
            }
            if(!func[0] && !func[1] && !func[2]){
                al_draw_bitmap(botao_g, LARGURA/6, 575, 0);
                al_draw_bitmap(botao_g, 560, 575, 0);
                al_draw_bitmap(botao_g, 890, 575, 0);   
            }
            if(func[0]){
                al_draw_bitmap(botao, 685, 570, 0);
                al_draw_bitmap(botao, 685, 650, 0);

                al_draw_line(1150, 500 - (b*20), 200, 500 - (b*20),al_map_rgb(131,139,131), 3);
                al_draw_text(font, al_map_rgb(0,0,0), 525, 600, ALLEGRO_ALIGN_CENTRE, "F(x) = ");
                al_draw_textf(font, al_map_rgb(0,0,0), 700, 600, ALLEGRO_ALIGN_CENTRE, "%d", b);
                
            }else if(func[1]){
                al_draw_bitmap(botao, 515, 570, 0);
                al_draw_bitmap(botao, 515, 650, 0);
                al_draw_bitmap(botao, 730, 570, 0);
                al_draw_bitmap(botao, 730, 650, 0);
                
                al_draw_text(font, al_map_rgb(0,0,0), 380, 600, ALLEGRO_ALIGN_CENTRE, "F(x)= ");
                al_draw_textf(font, al_map_rgb(0,0,0), 525, 600, ALLEGRO_ALIGN_CENTRE, "%dX", a);
                al_draw_text(font, al_map_rgb(0,0,0), 640, 600, ALLEGRO_ALIGN_CENTRE, "+");
                al_draw_textf(font, al_map_rgb(0,0,0), 745, 600, ALLEGRO_ALIGN_CENTRE, "%d", b);
                
            }else if(func[2]){
                al_draw_bitmap(botao, 515, 570, 0);
                al_draw_bitmap(botao, 515, 650, 0);
                al_draw_bitmap(botao, 730, 570, 0);
                al_draw_bitmap(botao, 730, 650, 0);
                al_draw_bitmap(botao, 945, 570, 0);
                al_draw_bitmap(botao, 945, 650, 0);
                

                al_draw_text(font, al_map_rgb(0,0,0), 380, 600, ALLEGRO_ALIGN_CENTRE, "F(x)= ");
                al_draw_textf(font, al_map_rgb(0,0,0), 525, 600, ALLEGRO_ALIGN_CENTRE, "%dX", a);
                al_draw_text(font2, al_map_rgb(0,0,0), 600, 590, ALLEGRO_ALIGN_CENTRE, "2");
                al_draw_text(font, al_map_rgb(0,0,0), 640, 600, ALLEGRO_ALIGN_CENTRE, "+");
                al_draw_textf(font, al_map_rgb(0,0,0), 745, 600, ALLEGRO_ALIGN_CENTRE, "%dX", b);
                al_draw_text(font, al_map_rgb(0,0,0), 860, 600, ALLEGRO_ALIGN_CENTRE, "+");
                al_draw_textf(font, al_map_rgb(0,0,0), 960, 600, ALLEGRO_ALIGN_CENTRE, "%d", c);
                
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

    al_destroy_font(font2);
    al_destroy_font(font);
    al_destroy_sample(sample);
    al_destroy_bitmap(image);
    al_destroy_bitmap(botao);
    al_destroy_bitmap(botao_g);
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
        al_init_font_addon();
        
        if (!al_init_ttf_addon()){
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
        image2 = al_load_bitmap("chas2.jpg");
        image = al_load_bitmap("chas.jpg");
        initback(&BG, 0, 0, 0.2, 1280, 720, -1, image);
        
        botao = al_create_bitmap(30,30);
        if(!botao){
            fprintf(stderr, "Falha ao iniciar bitmap\n");
            al_destroy_display(display);
            return -1;
        }

        botao_g = al_create_bitmap(200,100);
        if(!botao_g){
            fprintf(stderr, "Falha ao iniciar bitmap\n");
            al_destroy_display(display);
            return -1;
        }

        font = al_load_font("04B_30__.ttf", 45, 0);
        if(!font){
            al_destroy_display(display);
            fprintf(stderr, "Erro ao carregar fonte\n");
            return -1;
        }
        font2 = al_load_font("04B_30__.ttf", 25, 0);
        if(!font2){
            al_destroy_display(display);
            fprintf(stderr, "Erro ao carregar fonte\n");
            return -1;
        }
        
        al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
        al_set_audio_stream_playing(musica, true);
        
        timer = al_create_timer(1.0/60);
        
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_mouse_event_source());
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
       
        al_start_timer(timer);
        
        return true;
    }

void coordenadas(float *x, float *y){
    float OrigemX = 250;
    float OrigemY = 500;

    *x=OrigemX + ((*x) * 35);
    *y=OrigemY - ((*y));

}


void segundograu(float a, float b, float c){
    float i,x1,x2,y1,y2;
    for(i = 0; i < 500; i ++){
        x1 = i;
        x2 = i+1;

    	y1 = a*(x1*x1)+b*x1+c;
    	y2 = a*(x2*x2)+b*x2+c;

        coordenadas(&x1,&y1);
        coordenadas(&x2,&y2);

    	al_draw_line(x1, y1, x2, y2,al_map_rgb(0,0,0), 3);
    }

    return;
}

void initback(Background *fundo, float x, float y, float velx, int width, int height, int dirX, ALLEGRO_BITMAP *image){
    fundo->x = x;
    fundo->y = y;
    fundo->velX = velx;
    fundo->width = width;
    fundo->height = height;
    fundo->dirX = dirX;
    fundo->image = image;
}

void updateback(Background *fundo){
    fundo->x += fundo->velX * fundo->dirX;
    if(fundo->x + fundo->width <= 0)
        fundo->x = 0;
}

void drawback(Background *fundo){
    al_draw_bitmap(fundo->image, fundo->x, fundo->y, 0);

    if((fundo->x + fundo->width) < LARGURA)
        al_draw_bitmap(fundo->image, (fundo->x + fundo->width), fundo->y, 0);

}
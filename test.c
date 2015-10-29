#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
 
#include <stdio.h>
#include <stdbool.h>
 
const int LARGURA_TELA = 1280;
const int ALTURA_TELA = 720;
 
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *image2 = NULL;
ALLEGRO_AUDIO_STREAM *musica = NULL;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_BITMAP *botao=0, *botao_g = 0;
ALLEGRO_FONT *font = NULL, *font2 = NULL;

enum FUNC{CONS, PRIM, SEC};
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};

// Structs
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

// Variaveis
int a,b,c,x,y;
int pos;

Background imagemDeFundo;

// Metodos
bool inicializar();
void desenharBotoes(bool equacao[3]);
void desenharImagens();
void resetarTela();
void coordenadas();
void segundograu(float a, float b, float c);
int pegarValorEmX(int valor);
int pegarValorEmY(int valor);

// Background
void initback(Background *fundo, float x, float y, float velx, int width, int height, int dirX, ALLEGRO_BITMAP *image);
void updateback(Background *fundo);
void drawback(Background *fundo);
 
int main(void)
{
    bool exit    = false;
    bool render  = false;
    bool keys[5] = {false,false,false,false,false};
    bool equacoes[3] = {false, false, false};
    bool sair = false;

    pos = 0; 
    a = 0;
    b = 0;
    c = 0;
    x = 0;
    y = 0;

    int count = 0;
 
    if (!inicializar())
    {
        return -1;
    }
 
    while (!sair)
    {
        if (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT ev;
            al_wait_for_event(fila_eventos, &ev);

            if(ev.type == ALLEGRO_EVENT_TIMER)
            {
                 updateback(&imagemDeFundo);
                 render = true;
            }

            if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(ev.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:    
                        keys[UP] = true;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        keys[DOWN] = true;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        pos -= 1;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        pos += 1;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        sair = true;
                        break;
                    case ALLEGRO_KEY_SPACE:
                        keys[SPACE] = true;
                        break;
                }
            }
            else if(ev.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch(ev.keyboard.keycode)
                {
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
                        sair = true;
                        break;
                    case ALLEGRO_KEY_SPACE:
                        keys[SPACE] = false;
                        break;
                } 
            }
            
            
            if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                break;
            }
        }

        // Desenha na tela
        if (render)
        {
            drawback(&imagemDeFundo);
            al_draw_bitmap(image2, 0, 485, 0);
            desenharImagens();
            desenharBotoes(equacoes);
            segundograu(a, b, c);
            
            if (count == 10)
            {
                count = 0;

                x +=1;

                y = a*(x*x)+b*x+c;
            }
            if(pos < 0)
                pos = 2;
            
            if(pos > 2)
                pos = 0;
            
            if(pos == 0){
                count++;
                if (count >= 10){
                    a += keys[UP]*1;
                    a -= keys[DOWN]*1;    
                }    
            }

            else if(pos == 1){
                count++;
                if (count >= 10){
                    count = 0;
                    b += keys[UP]*1;
                    b -= keys[DOWN]*1;    
                }
            }

            else if(pos == 2){
                count++;
                if (count >= 10){
                    count = 0;
                    c += keys[UP]*1;
                    c -= keys[DOWN]*1;    
                }
            }
            
            al_draw_filled_circle(pegarValorEmX(x), pegarValorEmY(y), 15, al_map_rgb(255, 0, 0));

            resetarTela();
        }
    }

    al_destroy_font(font2);
    al_destroy_font(font);
    al_destroy_sample(sample);
    al_destroy_bitmap(image);
    al_destroy_bitmap(botao);
    al_destroy_bitmap(botao_g);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
    al_destroy_audio_stream(musica);
 
    return 0;
}

//////
// Plano Cartesiano
//////
int pegarValorEmX(int valor)
{
    int origemX = 250;

    int resposta = origemX + (valor*100);
    return resposta;
}
int pegarValorEmY(int valor)
{
    int origemY = 500;

    int resposta = origemY - (valor*50);
    return resposta;
}
void coordenadas(float *x, float *y){
    float OrigemX = 250;
    float OrigemY = 500;

    *x=OrigemX + ((*x) * 100);
    *y=OrigemY - ((*y) * 50);

}


void segundograu(float a, float b, float c){
    float i,x1,x2,y1,y2;
    for(i = 0; i < 9; i += .1){
        x1 = i;
        x2 = i+.1;

        y1 = a*(x1*x1)+b*x1+c;
        y2 = a*(x2*x2)+b*x2+c;

        coordenadas(&x1,&y1);
        coordenadas(&x2,&y2);

        al_draw_line(x1, y1, x2, y2,al_map_rgb(0,0,0), 3);
    }

    return;
}

//////
// Background
//////
void initback(Background *fundo, float x, float y, float velx, int width, int height, int dirX, ALLEGRO_BITMAP *image)
{
    fundo->x = x;
    fundo->y = y;
    fundo->velX = velx;
    fundo->width = width;
    fundo->height = height;
    fundo->dirX = dirX;
    fundo->image = image;
}
void updateback(Background *fundo)
{
    fundo->x += fundo->velX * fundo->dirX;
    if(fundo->x + fundo->width <= 0)
        fundo->x = 0;
}
void drawback(Background *fundo)
{
    al_draw_bitmap(fundo->image, fundo->x, fundo->y, 0);

    if((fundo->x + fundo->width) < LARGURA_TELA)
        al_draw_bitmap(fundo->image, (fundo->x + fundo->width), fundo->y, 0);

}
//////
// Metodos de Desenho
//////
void resetarTela()
{
    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
}
void desenharImagens()
{
    // Desenha as linhas do plano cartesiano
    al_draw_line(1150, 500, 200, 500,al_map_rgb(0,0,0), 3);
    al_draw_line(250, 550, 250, 50,al_map_rgb(0,0,0), 3);
}
void desenharBotoes(bool equacao[3])
{

    al_set_target_bitmap(al_get_backbuffer(janela));

        al_draw_textf(font, al_map_rgb(0,0,0), 380, 600, ALLEGRO_ALIGN_CENTRE, "F(x)= %dX + %dX + %d", a,b,c);
    
}
 
bool inicializar()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }
 
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_primitives.\n");
        return false;
    }
 
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }
 
    al_set_window_title(janela, "Project Damasco");
 
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
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

    if (!al_init_ttf_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return -1;
    }

    musica = al_load_audio_stream("bits.ogg", 4, 1024);
    if (!musica)
    {
        fprintf(stderr, "Falha ao carregar audio.\n");
        al_destroy_event_queue(fila_eventos);
        al_destroy_display(janela);
        al_destroy_sample(sample);
        return false;
    }

    sample = al_load_sample("palmas.wav");
    if (!sample)
    {
        fprintf(stderr, "Falha ao carregar sample.\n");
        al_destroy_display(janela);
        return false;
    }

    fila_eventos = al_create_event_queue();
    if(!fila_eventos) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(janela);
        return -1;
    }

    image2 = al_load_bitmap("chas2.jpg");
    image = al_load_bitmap("chas.jpg");
    initback(&imagemDeFundo, 0, 0, 0.2, 1280, 720, -1, image);
    
    botao = al_load_bitmap("button.bmp");
    if(!botao)
    {
        fprintf(stderr, "Falha ao iniciar bitmap\n");
        al_destroy_display(janela);
        return -1;
    }

    botao_g = al_load_bitmap("buttong.bmp");
    if(!botao_g)
    {
        fprintf(stderr, "Falha ao iniciar bitmap\n");
        al_destroy_display(janela);
        return -1;
    }

    font = al_load_font("04B_30__.ttf", 45, 0);
    if(!font)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Erro ao carregar fonte\n");
        return -1;
    }

    font2 = al_load_font("04B_30__.ttf", 25, 0);
    if(!font2)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Erro ao carregar fonte\n");
        return -1;
    }
 
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);
    
    timer = al_create_timer(1.0/60);

    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
   
    al_start_timer(timer);
 
    return true;
}
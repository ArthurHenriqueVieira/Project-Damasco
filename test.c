#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "objects.h"
 
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
 
const int LARGURA_TELA = 1280;
const int ALTURA_TELA = 720;
const int NUM_BULLETS = 5;
 
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *menuBg = NULL;
ALLEGRO_BITMAP *image = NULL,*image2 = NULL, *TreeHouse = NULL, *fundo = NULL, *pkfundo = NULL, *aba = NULL;
ALLEGRO_BITMAP *Seta = NULL;
ALLEGRO_AUDIO_STREAM *musica = NULL, *musica2 = NULL;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_BITMAP *Finn = NULL,*Jake = NULL,*BMO = NULL,*Gunter = NULL,*LadyRainicorn = NULL, *IceKing = NULL, *finn2 = NULL;
ALLEGRO_BITMAP *Flame = NULL, *Fireball = NULL, *Bomb = NULL,*FinnBomb = NULL, *ThrowJake = NULL, *dialog = NULL, *hp = NULL, *hp2 = NULL;
ALLEGRO_FONT *font = NULL, *font2 = NULL, *font3 = NULL;

enum ESTADO{MENU, TUTORIAL, JOGO, FIM};
enum FUNC{CONS, PRIM, SEC};
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, ENTER};


// Variaveis
int a,b,c,x,y;
int pos,aux=1,temp=0, ct = 1280, cr = -50, cf = 1280, prox = 0, i = 0;
int curframe = 0, curframeb = 0, curframer = 0, curframee = 0, curframeLady = 0;
int framecount = 0, framecountr = 0, framecounte = 0,framecountLady = 0, framedelay = 60;
int framewidth = 111;
int frameheight = 131;
bool keys[6] = {false,false,false,false,false, false};
bool Fire = false;

bool posicaoInimigoY;

//Variaveis Struct 
Character FinnJake;
Background imagemDeFundo;
Bullet bullets;
Alvo listaDeAlvos[4];

// Metodos
bool inicializar();
void desenharBotoes(bool equacao[3]);
void desenharImagens();
void resetarTela();
void coordenadas();
void segundograu(float a, float b, float c, int aux, int *auxtemp);
int pegarValorEmX(int valor);
int pegarValorEmY(int valor);
// Personagem
void InitCharacter(Character *FinnJake, int *c);
void DrawCharacter(Character *FinnJake, Bullet *bullet);
// Balas
void InitBullet(Bullet *bullet);
void DrawBullet(Bullet *bullet);
void FireBullet(Bullet *bullet, Character *FinnJake);
void UpdateBullet(Bullet *bullet,int a, int b, int c, float *posicao);
// Alvos
bool inicializarAlvos(Alvo alvos[]);
void desenharAlvos(Alvo alvos[], int quantidade);
void verificaColisao(Alvo alvos[], Bullet *bullet);
// Background
void initback(Background *fundo, float x, float y, float velx, int width, int height, int dirX, ALLEGRO_BITMAP *image);
void updateback(Background *fundo);
void drawback(Background *fundo);
// Estado
void mudarEstado(int *estado, int novoEstado);

void inicializaJogo()
{
    pos = 0; 
    a = 0;
    b = 0;
    c = 0;
    x = 0;
    y = 0;
    inicializarAlvos(listaDeAlvos);
}
 
int main(void)
{
    bool exit    = false;
    bool render  = false;

    bool over = false, over2 = false, over3 = false;
    
    bool equacoes[3] = {false, false, false};
    bool sair = false, end = false;

    float posicao = 0;

    int count = 0;
    int estado = -1;

    mudarEstado(&estado, MENU);
 
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

            if(!keys[SPACE] && !bullets.live && estado == JOGO)
            {

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
                        	curframe = 0;
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
                        	keys[SPACE] = true;
                        	break;
                	} 
            	}
            }  
            else if(estado == TUTORIAL){
                    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
                    {
                        switch(ev.keyboard.keycode)
                        {
                        case ALLEGRO_KEY_UP:    
                            pos -= 1;
                            break;
                        case ALLEGRO_KEY_DOWN:
                            pos += 1;
                            break;
                        case ALLEGRO_KEY_ESCAPE:
                            sair = true;
                            break;
                        case ALLEGRO_KEY_ENTER:
                            if(ct > 150) ct = 150;
                            else prox += 1;
                            keys[ENTER] = true;
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
                            case ALLEGRO_KEY_ENTER:
                                keys[ENTER] = false;
                                break;
                        } 
                    }
                }

            if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
               if (estado == MENU)
               {
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
               else if (estado == FIM)
               {
                    if (ev.mouse.x >= 530 && ev.mouse.x <= 730 && ev.mouse.y >= 300 && ev.mouse.y <= 340){
                        over = true;
                    }else over = false;

               }
            }
            // aqui ele identifica o clique do mouse no menu, esta em ordem Jogar, Tutorial e Sair
            if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if (estado == MENU)
                {
                    if (ev.mouse.x >= 530 && ev.mouse.x <= 730 && ev.mouse.y >= 300 && ev.mouse.y <= 340)
                        mudarEstado(&estado, JOGO);
                    else if (ev.mouse.x >= 500 && ev.mouse.x <= 760 && ev.mouse.y >= 350 && ev.mouse.y <= 390)
                        mudarEstado(&estado, TUTORIAL);
                    else if (ev.mouse.x >= 560 && ev.mouse.x <= 700 && ev.mouse.y >= 400 && ev.mouse.y <= 440)
                    sair = true;
                }
                else if (estado == FIM)
                {
                    if (ev.mouse.x >= 530 && ev.mouse.x <= 730 && ev.mouse.y >= 300 && ev.mouse.y <= 340)
                    {
                        mudarEstado(&estado, JOGO);
                        inicializarAlvos(listaDeAlvos);
                    }
                }
            }
            
            if(pos < 0) pos = 2;
            if(pos > 2) pos = 0;
            
            if(pos == 0){
                count++;
                if (count >= 10){
                    count = 0;
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
                if(c > 9) c = 9;
                if(c < -2) c = -2;

                if (count >= 10){
                    count = 0;
                    c += keys[UP]*1;
                    c -= keys[DOWN]*1;    
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
            if (estado == MENU)
            {
                al_draw_bitmap(menuBg, 0, 0, 0);
                al_draw_bitmap(BMO, 110, -30, 0);

                if(!over)
                    al_draw_text(font, al_map_rgb(0,0,0), 630, 300,ALLEGRO_ALIGN_CENTRE, "Jogar");
                else al_draw_text(font, al_map_rgb(255,255,255), 630, 300,ALLEGRO_ALIGN_CENTRE, "Jogar");
        
                if(!over2)
                    al_draw_text(font, al_map_rgb(0,0,0), 630, 350,ALLEGRO_ALIGN_CENTRE, "Tutorial");
                else al_draw_text(font, al_map_rgb(255,255,255), 630, 350,ALLEGRO_ALIGN_CENTRE, "Tutorial");
        
                if(!over3)  
                    al_draw_text(font, al_map_rgb(0,0,0), 630, 400,ALLEGRO_ALIGN_CENTRE, "Sair");
                else al_draw_text(font, al_map_rgb(255,255,255), 630, 400,ALLEGRO_ALIGN_CENTRE, "Sair");
            }
            else if(estado == TUTORIAL)
            {
                if(bullets.x > LARGURA_TELA || bullets.y > ALTURA_TELA)
                {
                    bullets.live = false;
                    posicao = 0;
                    bullets.x = 0;
                    bullets.y = 0;
                }

                al_draw_bitmap(fundo, 0, 0, 0);
                al_draw_bitmap(BMO, ct, 300, 0);

                ct -= 2;
                if(prox >= 7) prox = 7;
                if(ct <= 150){
                    al_draw_bitmap(dialog, 400, 0, 0);
                    ct = 150;

                    if(prox == 1){
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 50, 0, "O Rei Gelado esta");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 100, 0, "tentando novamente"); 
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 150, 0, "sequestrar todas as");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 200, 0, "princesas de Ooo.");
                        al_draw_text(font2, al_map_rgb(0,0,0), 850, 300, 0, "Aperte Enter");
                    }
                    else if(prox == 2){
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 50, 0, "Finn e Jake estao");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 100, 0, "tentando derrota-lo"); 
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 150, 0, "mas sem matematica e");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 200, 0, "impossivel!");
                        al_draw_text(font2, al_map_rgb(0,0,0), 850, 300, 0, "Aperte Enter");  
                    }
                    else if(prox == 3){
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 50, 0, "Eu BMO e voce temos");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 100, 0, "uma missao, voce precisa"); 
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 150, 0, "me fornecer dados para");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 200, 0, "que eu possa dar as");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 250, 0, "coordenadas do Rei e do");
                        al_draw_text(font2, al_map_rgb(0,0,0), 850, 300, 0, "Aperte Enter");  
                    }
                    else if(prox == 4){
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 50, 0, "Gunter, para que os");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 100, 0, "meninos acabem com"); 
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 150, 0, "essa loucura e ainda");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 200, 0, "sobre tempo pra comer");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 250, 0, "umas panquecas de bacon");
                        al_draw_text(font2, al_map_rgb(0,0,0), 850, 300, 0, "Aperte Enter");
                        al_draw_scaled_bitmap(pkfundo, 0, 0, 1280, 720, 275, 350, 110, 100, 0);  
                    }
                    else if(prox == 5){
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 50, 0, "E simples, olhe para o");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 100, 0, "meu display!");
                        al_draw_text(font2, al_map_rgb(0,0,0), 850, 300, 0, "Aperte Enter");
                        al_draw_scaled_bitmap(pkfundo, 0, 0, 1280, 720, 275, 350, 110, 100, 0); 
                        al_set_audio_stream_playing(musica, false);
                        al_attach_audio_stream_to_mixer(musica2, al_get_default_mixer());
                    }
                    else if(prox == 6){
                        al_draw_bitmap(pkfundo, 0,0,0);
                        al_set_audio_stream_playing(musica2, true);
                        cr += 2;
                        cf -= 2;
                        if(cr >= 900) cr = 900;
                        if(cf <= 150) cf = 150; 
                        if(++framecountr >= 25){
                            if(++curframer >= 6)
                                curframer = 0;
                        framecountr = 0;
                        }
                        al_draw_bitmap_region(IceKing, curframer * 169, 0, 169, 153, cr, 20,  1);
                        al_draw_scaled_bitmap(finn2, 0, 0, 100, 200, cf, 200, 180, 360, 0);
                        al_draw_text(font3, al_map_rgb(0,0,0), 100, 570, 0, "A wild ICEKING");
                        al_draw_text(font3, al_map_rgb(0,0,0), 70, 620, 0, "appeared!");
                        if(cr == 900 && cf == 150){
                            al_draw_bitmap(hp, 600, 300, 0);
                            al_draw_bitmap(hp2, 50, 50, 0);
                            al_draw_text(font3,al_map_rgb(0,0,0), 660, 270, 0, "FINN THE HUMAN");
                            al_draw_text(font3, al_map_rgb(0,0,0), 50, 30, 0, "ICEKING");
                        }
                    }
                    else if(prox == 7){
                        al_draw_bitmap(pkfundo, 0,0,0);
                        if(++framecountr >= 25){
                            if(++curframer >= 6)
                                curframer = 0;
                        framecountr = 0;
                        }
                        al_draw_bitmap_region(IceKing, curframer * 169, 0, 169, 153, 900, 20,  1);
                        al_draw_scaled_bitmap(finn2, 0, 0, 100, 200, 150, 200, 180, 360, 0);
                        al_draw_bitmap(hp, 600, 300, 0);
                        al_draw_bitmap(hp2, 50, 50, 0);
                        al_draw_text(font3,al_map_rgb(0,0,0), 660, 270, 0, "FINN THE HUMAN");
                        al_draw_text(font3, al_map_rgb(0,0,0), 50, 30, 0, "ICEKING");
                        al_draw_scaled_bitmap(aba, 0, 0, 1280, 442, 580, 285, 700, 430, 0);
                        al_draw_text(font3,al_map_rgb(0,0,0), 700, 540, 0, "FIGHT");
                        al_draw_text(font3,al_map_rgb(0,0,0), 700, 590, 0, "PLAY");
                        al_draw_text(font3,al_map_rgb(0,0,0), 700, 640, 0, "RUN");

                        if(pos == 0){
                            al_draw_rotated_bitmap(Seta, 26.50, 21, 670, 545, -80.09, -1); 
                            al_draw_text(font3, al_map_rgb(0,0,0), 50, 540, 0, "Neste modo, te");
                            al_draw_text(font3, al_map_rgb(0,0,0), 50, 590, 0, "ensino sobre pode-");
                            al_draw_text(font3, al_map_rgb(0,0,0), 50, 640, 0, "res matematicos");  
                        }
                        else if(pos == 1){
                            al_draw_rotated_bitmap(Seta, 26.50, 21, 670, 595, -80.09, -1);
                            al_draw_text(font3, al_map_rgb(0,0,0), 50, 540, 0, "Ja aprendeu tudo?");
                            al_draw_text(font3, al_map_rgb(0,0,0), 50, 590, 0, "entao HORA DE ");
                            al_draw_text(font3, al_map_rgb(0,0,0), 50, 640, 0, "AVENTURA!");  
                        }
                        else if(pos == 2){
                            al_draw_rotated_bitmap(Seta, 26.50, 21, 670, 645, -80.09, -1);
                            al_draw_text(font3, al_map_rgb(0,0,0), 50, 540, 0, "Deseja voltar");
                            al_draw_text(font3, al_map_rgb(0,0,0), 50, 590, 0, "pro menu? ok!");
                        }

                        if(pos == 0 && keys[ENTER] && i >= 100){
                            al_draw_scaled_bitmap(aba, 0, 0, 1280, 442, 300, 285, 1000, 430, 0);
                            al_draw_text(font3,al_map_rgb(0,0,0), 400, 540, 0, "Lancar Bomba(2 grau)");
                            al_draw_text(font3,al_map_rgb(0,0,0), 400, 590, 0, "Espada de fogo(1 grau)");
                            al_draw_text(font3,al_map_rgb(0,0,0), 400, 640, 0, "Lancar Jake(Constante)");
                        }else if(pos == 1 && keys[ENTER] && i >= 100){
                            mudarEstado(&estado, JOGO);
                            al_set_audio_stream_playing(musica2, false);
                            pos = 0;
                        }else if(pos == 2 && keys[ENTER] && i >= 100){
                            mudarEstado(&estado, MENU);
                            al_set_audio_stream_playing(musica2, false);
                            al_set_audio_stream_playing(musica, true);
                            i = 0;
                            prox = 0;
                            ct = 1280;
                            cr = -50; 
                            cf = 1280;
                        }
                        i += 1;
                    }
                    else{
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 50, 0, "Ola, eu sou o BMO e vou");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 100, 0, "te explicar como podemos"); 
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 150, 0, "ajudar Finn e Jake");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 200, 0, "a derrotar o Rei Gelado.");
                        al_draw_text(font, al_map_rgb(0,0,0), 450, 250, 0, "Vai ser Matematico! :D ");
                        al_draw_text(font2, al_map_rgb(0,0,0), 850, 300, 0, "Aperte Enter"); 
                    }
                } 
                
                InitCharacter(&FinnJake, &c);
                if(end){
                    segundograu(a, b, c, aux, &temp);
                    desenharBotoes(equacoes);
                    DrawCharacter(&FinnJake, &bullets);
                    desenharImagens();
                    desenharAlvos(listaDeAlvos, 4);
                    if(pos == 0)
                        al_draw_bitmap(Seta, 570, 640, 0);
                    else if(pos == 1)
                        al_draw_bitmap(Seta, 690, 640, 0);
                    else if(pos == 2)
                        al_draw_bitmap(Seta, 820, 640, 0);
                }
                DrawBullet(&bullets);
                verificaColisao(listaDeAlvos, &bullets);
                UpdateBullet(&bullets, a, b, c, &posicao);
                
                if(Fire)
                    FireBullet(&bullets, &FinnJake);

                if(temp<50)
                    aux=1;
                else if(temp>=50 && temp<100)
                    aux=-1;
                else
                    temp=0;

                if (count == 10)
                    count = 0;
            }
            else if (estado == JOGO)
            {
                if(bullets.x > LARGURA_TELA || bullets.y > ALTURA_TELA)
                {
                    bullets.live = false;
                    posicao = 0;
                    bullets.x = 0;
                    bullets.y = 0;

                    mudarEstado(&estado, FIM);
                }

                drawback(&imagemDeFundo);
                al_draw_bitmap(image2, 0, 485, 0);
                al_draw_bitmap(TreeHouse, -109, -120, 0);
                desenharImagens();
                desenharBotoes(equacoes);
                if(!bullets.live && !keys[SPACE])
                    segundograu(a, b, c, aux, &temp);
                InitCharacter(&FinnJake, &c);
                DrawCharacter(&FinnJake, &bullets);
                DrawBullet(&bullets);
                verificaColisao(listaDeAlvos, &bullets);
                UpdateBullet(&bullets, a, b, c, &posicao);
                desenharAlvos(listaDeAlvos, 4);
                
                if(pos == 0)
                    al_draw_bitmap(Seta, 570, 640, 0);
                else if(pos == 1)
                    al_draw_bitmap(Seta, 690, 640, 0);
                else if(pos == 2)
                    al_draw_bitmap(Seta, 820, 640, 0);

                
                if(Fire)
                    FireBullet(&bullets, &FinnJake);

                if(temp<50)
                    aux=1;
                else if(temp>=50 && temp<100)
                    aux=-1;
                else
                    temp=0;

                if (count == 10)
                    count = 0;
            }
            else if (estado == FIM)
            {
                al_draw_bitmap(menuBg, 0, 0, 0);

                if(!over)
                    al_draw_text(font, al_map_rgb(0,0,0), 630, 300,ALLEGRO_ALIGN_CENTRE, "Jogar Novamente");
                else al_draw_text(font, al_map_rgb(255,255,255), 630, 300,ALLEGRO_ALIGN_CENTRE, "Jogar Novamente");
            }
            resetarTela();
        }
    }

    al_destroy_font(font);
    al_destroy_font(font2);
    al_destroy_bitmap(hp);
    al_destroy_bitmap(hp2);
    al_destroy_bitmap(aba);
    al_destroy_font(font3);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(pkfundo);
    al_destroy_sample(sample);
    al_destroy_bitmap(image);
    al_destroy_bitmap(Finn);
    al_destroy_bitmap(finn2);
    al_destroy_bitmap(Jake);
    al_destroy_bitmap(LadyRainicorn);
    al_destroy_bitmap(BMO);
    al_destroy_bitmap(Gunter);
    al_destroy_bitmap(IceKing);
    al_destroy_bitmap(menuBg);
    al_destroy_bitmap(FinnBomb);
    al_destroy_bitmap(ThrowJake);
    al_destroy_bitmap(Flame);
    al_destroy_bitmap(Fireball);
    al_destroy_bitmap(Bomb);
    al_destroy_bitmap(TreeHouse);
    al_destroy_display(janela);
    al_destroy_bitmap(Seta);
    al_destroy_bitmap(dialog);
    al_destroy_event_queue(fila_eventos);
    al_destroy_audio_stream(musica);
    al_destroy_audio_stream(musica2);
 
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

void segundograu(float a, float b, float c,int aux, int * auxtemp){
    float i,x1,x2,y1,y2;
    for(i = 0; i < 9; i += .125){
        x1 = i;
        x2 = i+.1;

        y1 = a*(x1*x1)+b*x1+c;
        y2 = a*(x2*x2)+b*x2+c;

        coordenadas(&x1,&y1);
        coordenadas(&x2,&y2);
        if (aux>0)
            al_draw_line(x1, y1, x2, y2,al_map_rgb(0,0,0), 3);
        aux*=-1;

        
    }
    *auxtemp=*auxtemp+1; 
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
// Metodos de desenharBotoes`
//////
void resetarTela()
{
    al_flip_display();
    al_clear_to_color(al_map_rgb(0, 0, 0));
}
void desenharImagens()
{
    // Desenha as linhas do plano cartesiano
    //al_draw_line(1150, 500, 200, 500,al_map_rgb(0,0,0), 3);
    //al_draw_line(250, 550, 250, 50,al_map_rgb(0,0,0), 3);
}
void desenharBotoes(bool equacao[3])
{

    al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_text(font2, al_map_rgb(0,0,0), 630, 670, ALLEGRO_ALIGN_CENTRE, "2");
        al_draw_textf(font, al_map_rgb(0,0,0), 640, 680, ALLEGRO_ALIGN_CENTRE, "F(x)= %dX + %dX + %d", a,b,c);
    
}

//////
// Metodos do personagem
//////
void InitCharacter(Character *FinnJake, int *c)
{
    FinnJake->x = 150;
    FinnJake->y = 450 - (*c * 50);
    FinnJake->ID = PLAYER;
    FinnJake->live = 3;
    FinnJake->score = 0;
}

void DrawCharacter(Character *FinnJake, Bullet *bullet)
{
    if(keys[SPACE] && a == 0 && b == 0 && !bullet->live)
    {
        if(++framecount >= 10)
        {
            if(++curframe >= 14)
            {
                Fire = true;
                keys[SPACE] = false;
            }
            framecount = 0;
        }
            al_draw_bitmap_region(ThrowJake, curframe * 179, 0, 179, 97, FinnJake->x - 20, FinnJake->y - 10, 0);
    }else

    if(keys[SPACE] && a == 0 && b != 0 && !bullet->live)
    {
        if(++framecount >= 20)
        {
            if(++curframe >= 14)
            {
                Fire = true;
                keys[SPACE] = false;
            }
            framecount = 0;
        }
            al_draw_bitmap_region(Flame, curframe * 175, 0, 175, 163, FinnJake->x - 30, FinnJake->y - 50, 0);
    }else

    if(keys[SPACE] && a != 0 && !bullet->live)
    {
        if(++framecount >= 15)
        {
            if(++curframe >= 13)
            {
                Fire = true;
                keys[SPACE] = false;
            }
            framecount = 0;
        }
            al_draw_bitmap_region(FinnBomb, curframe * framewidth, 0, framewidth, frameheight, FinnJake->x + 20, FinnJake->y - 30, 0);
    }else
    {
        if(++framecount >= framedelay)
        {
            if(++curframe >= 42)
            curframe = 0;
            framecount = 0;
        }
        al_draw_bitmap_region(Finn, curframe * framewidth, 0, framewidth, frameheight, FinnJake->x + 20, FinnJake->y - 30, 0);
    }

    if(c > 0){
        if(++framecountLady >= 20)
            {
                if(++curframeLady >= 15)
                    curframeLady = 0;
                framecountLady = 0;
            }
            al_draw_bitmap_region(LadyRainicorn, curframeLady * 282, 0, 282, 159, FinnJake->x -150 , FinnJake->y + 40, 0);
    }
}

//////
// Metodos do projetil
//////
void InitBullet(Bullet *bullet)
{
        bullet->ID = BULLET;
        bullet->live = false;
        bullet->speed = 5;
}

void DrawBullet(Bullet *bullet)
{
    if(bullet->live && a == 0 && b != 0)
        al_draw_bitmap(Fireball, bullet->x -50, bullet->y - 50, 0);
    else if(bullet->live && a != 0)
        al_draw_bitmap(Bomb, bullet->x -40, bullet->y -30, 0);
    else if(bullet->live && a == 0 && b == 0)
        al_draw_bitmap(Jake, bullet->x -25, bullet->y -23, 0);
}

void FireBullet(Bullet *bullet, Character *FinnJake)
{
    if(!bullet->live)
    {
        bullet->x = FinnJake->x+100;
        bullet->y = FinnJake->y+50;
        bullet->live = true;
    }else Fire = false;
}

void UpdateBullet(Bullet *bullet, int a, int b, int c, float *posicao)
{
    if(bullet->live)
    {
        float posicaoX,posicaoY;

        posicaoX = *posicao;
        posicaoY = a*(posicaoX * posicaoX) + b*posicaoX + c;

        coordenadas(&posicaoX,&posicaoY);

        bullet->x = posicaoX;
        bullet->y = posicaoY;

        *posicao += 0.02;
    }
}

//////
// Metodos do Alvo
//////
bool inicializarAlvos(Alvo alvos[])
{
	int tipo, a,b,c;
	float x1,x2,x3,x4,y1,y2,y3,y4;
	srand((unsigned)time(NULL));
	tipo = rand() % 3;

	x1 = rand() % 26;
	x1/=10;
	x2 = 25 + (rand() % 26);
	x2/=10;
	x3 = 50 + (rand() % 26);
	x3/=10;
	x4 = 75 + (rand() % 16);
	x4/=10;
     
    do{
		a= (rand() % 5) -1;
	}while(a==0);

    do{
		b= (rand() % 5) -1;
	}while(b==0);

    do{
		c= (rand() % 11) -1;
	}while(c==0);

	if(tipo==0){
    	y1=c;
    	y2=c;
    	y3=c;
    	y4=c;
    	a=0;
    	b=0;
	}	
	else if(tipo==1){
		y1=(x1*b)+c;
    	y2=(x2*b)+c;
    	y3=(x3*b)+c;
    	y4=(x4*b)+c;
    	a=0;
	}
	else if(tipo==2){
	    y1=(a*(x1*x1))+(x1*b)+c;
    	y2=(a*(x2*x2))+(x2*b)+c;
    	y3=(a*(x3*x3))+(x3*b)+c;
    	y4=(a*(x4*x4))+(x4*b)+c;
	}
    alvos[0].ID = ALVO;
    alvos[0].x = x1;
    alvos[0].y = y1;
    alvos[0].tamanho = 15;
    alvos[0].acertado = false;

    alvos[1].ID = ALVO;
    alvos[1].x = x2;
    alvos[1].y = y2;
    alvos[1].tamanho = 15;
    alvos[1].acertado = false;

    alvos[2].ID = ALVO;
    alvos[2].x = x3;
    alvos[2].y = y3;
    alvos[2].tamanho = 15;
    alvos[2].acertado = false;

    alvos[3].ID = ALVOFINAL;
    alvos[3].x = x4;
    alvos[3].y = y4;
    alvos[3].tamanho = 75;
    alvos[3].acertado = false;
}

void desenharAlvos(Alvo alvos[], int quantidade)
{
    float valorX, valorY;

    int i;
    for(i = 0; i < quantidade; i++)
    {
        if (!alvos[i].acertado)
        {
            valorX = alvos[i].x;
            valorY = alvos[i].y;

            coordenadas(&valorX, &valorY);

            if (alvos[i].ID == ALVOFINAL)
            {
                if(++framecountr >= 25){
                    if(++curframer >= 6)
                        curframer = 0;
                    framecountr = 0;
                }
                al_draw_bitmap_region(IceKing, curframer * 169, 0, 169, 153, valorX - 84, valorY - 71,  1);
            }
            else {
                if(++framecounte >= 65)
                {
                    if(++curframee >= 4)
                        curframee = 0;
                    framecounte = 0;
                }

                al_draw_bitmap_region(Gunter, curframee * 63, 0, 63, 68, valorX - 32, valorY - 34, 1);
            }
        }
    }
}

void verificaColisao(Alvo alvos[], Bullet *bullet)
{
    float valorX, valorY;

    int i;
    for(i = 0; i < 4; i++)
    {
        valorX = alvos[i].x;
        valorY = alvos[i].y;

        coordenadas(&valorX, &valorY);

        if (bullet->x > (valorX - alvos[i].tamanho) && bullet->x < (valorX + alvos[i].tamanho))
        {
            if (bullet->y > (valorY - alvos[i].tamanho) && bullet->y < (valorY + alvos[i].tamanho))
            {
                alvos[i].acertado = true;
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
        }
    }
}


//////
// Metodos do estado
//////
void mudarEstado(int *estado, int novoEstado)
{
    *estado = novoEstado;

    if (novoEstado == JOGO)
    {
        inicializaJogo();
    }
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

    InitBullet(&bullets);

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
    musica2 = al_load_audio_stream("Pokemon.ogg", 4, 1024);
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
    Finn = al_load_bitmap("Finn.png");
    finn2 = al_load_bitmap("finntut.png");
    Jake = al_load_bitmap("Jake.png");
    LadyRainicorn = al_load_bitmap("LadyRainicorn.png");
    BMO = al_load_bitmap("BMO.png");
    Gunter = al_load_bitmap("Gunter.png");
    IceKing = al_load_bitmap("IceKing.png");
    FinnBomb = al_load_bitmap("FinnBomb.png");
    Flame = al_load_bitmap("Flame.png");
    ThrowJake = al_load_bitmap("ThrowJake.png");
    Fireball = al_load_bitmap("Fireball.png");
    Bomb = al_load_bitmap("Bomb.png");
    TreeHouse = al_load_bitmap("TreeHouse.png");
    Seta = al_load_bitmap("Seta.png");
    fundo = al_load_bitmap("oi.jpg");
    pkfundo = al_load_bitmap("pkfundo.jpg");
    dialog= al_load_bitmap("dialog.png");
    hp = al_load_bitmap("life.png");
    hp2 = al_load_bitmap("life2.png");
    aba = al_load_bitmap("aba.png");

    initback(&imagemDeFundo, 0, 0, 0.2, 1280, 720, -1, image);
    
    font = al_load_font("04B_30__.ttf", 30, 0);
    font2 = al_load_font("04B_30__.ttf", 15, 0);
    font3 = al_load_font("Pokemon GB.ttf", 30, 0);
    
    if(!font)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Erro ao carregar fonte\n");
        return -1;
    }

    if(!font2)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Erro ao carregar fonte\n");
        return -1;
    }
 
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);
    
    al_reserve_samples(1);
    menuBg = al_load_bitmap("menu.jpg");
    timer = al_create_timer(1.0/60);

    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
   
    al_start_timer(timer);
 
    return true;
}
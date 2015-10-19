#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <time.h>

//Variaveis Globais/Allegro
const int LARG = 1300;
const int ALT = 680;
double Score = 0;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *filadeeventos = NULL;
ALLEGRO_BITMAP *chao = NULL;
ALLEGRO_BITMAP *plat = NULL;
ALLEGRO_BITMAP *bgImage = NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_FONT *fontescore = NULL;
//----------------------------


//--------------------------------
//Structs
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

Background Fundo_Principal;
Background Chao;

//--------------------------------------------

// ---------------------------------------------------------------------------------------------------------------
// Funções
bool Inicializar()
{
       if(!al_init())
        {
        fprintf(stderr,"Falha ao iniciar Allegro5!\n");
        return false;
        }

        al_init_font_addon();


        if (!al_init_ttf_addon())
        {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
        }

        janela = al_create_display(LARG,ALT);
        if(!janela)
        {
        fprintf(stderr,"Falha ao criar janela!\n");
        return false;
        }


        al_init_image_addon();
        al_install_keyboard();



        filadeeventos = al_create_event_queue();
        if(!filadeeventos)
        {
            fprintf(stderr, "Falha ao criar fila de eventos!\n");
            return false;
        }


        chao = al_load_bitmap("chao.png");
        if(!chao)
        {
            fprintf(stderr, "Falha ao carregar imagem chao\n");
            return false;
        }


        plat = al_load_bitmap("Plataforma.png");
        if(!plat)
        {
            fprintf(stderr, "Falha ao carregar imagem plataforma\n");
            return false;
        }


        bgImage = al_load_bitmap("fundo.png");
        if(!bgImage)
        {
            fprintf(stderr, "Falha ao carregar imagem fundo\n");
            return false;
        }

        fonte = al_load_font("Super Mario Bros.ttf", 75, 0);
        fontescore = al_load_font("Super Mario Bros.ttf", 35, 0);
        if (!fonte || !fontescore)
        {
            fprintf(stderr, "Falha ao carregar fontes.\n");
            return false;
        }


        al_register_event_source(filadeeventos, al_get_keyboard_event_source());
        al_register_event_source(filadeeventos, al_get_display_event_source(janela));
        return true;
}


void Finalizar()
{
    al_destroy_display(janela);
    al_destroy_event_queue(filadeeventos);
    al_destroy_bitmap(chao);
    al_destroy_bitmap(plat);
    al_destroy_bitmap(bgImage);
    al_destroy_font(fonte);
    al_destroy_font(fontescore);
}

void MovimentoPlataforma(float *plataforma_X)
{
    //Muda velocidade
    *plataforma_X -= 1.1;

    if (*plataforma_X <= -al_get_bitmap_width(plat))
    *plataforma_X = LARG;

    al_draw_bitmap(plat, *plataforma_X, 465,0);
}

void IniciaFundo(Background *fundo, float x, float y, float velx, int width, int height, int dirX, ALLEGRO_BITMAP *image)
{
    fundo->x = x;
    fundo->y = y;
    fundo->velX = velx;
    fundo->width = width;
    fundo->height = height;
    fundo->dirX = dirX;
    fundo->image = image;
}

void AtualizaDesenhaFundo(Background *fundo)
{
    //Atualiza a Posição
    fundo->x += fundo->velX * fundo->dirX;
    if(fundo->x + fundo->width <= 0)
        fundo->x = 0;

    //Desenha o fundo
    al_draw_bitmap(fundo->image, fundo->x, fundo->y, 0);

    if((fundo->x + fundo->width) < LARG)
        al_draw_bitmap(fundo->image, (fundo->x + fundo->width), fundo->y, 0);
}

void TrocaValorOperacao(int *operando_1, int *operando_2, int *tempo_operacao)
{

    *tempo_operacao += 1;

    if(*tempo_operacao != 2)
    {
        *operando_1 = (rand() % 9) + 1;
        *operando_2 = (rand() % 9) + 1;
    }
    else
    {
        *operando_1 = (rand() % 3) + 1;
        *operando_2 = (rand() % 3) + 1;
    }
    if(*operando_1 == *operando_2)
    *operando_2 += 1;


}

void DesenhaValorOperacao(int operando_1, int operando_2, int *tempo_operacao, int plataforma_X)
{
    int pos_X = (((plataforma_X + al_get_bitmap_width(plat)) - plataforma_X) / 2) + plataforma_X - 15;
    char Operando_Matematico1, Operando_Matematico2;


    if(*tempo_operacao == 2)
    {
        switch(operando_1)
        {
        case 1:
            Operando_Matematico1 = '+';
            break;
        case 2:
            Operando_Matematico1 = '-';
            break;
        case 3:
            Operando_Matematico1 = 'x';
            break;
        case 4:
            Operando_Matematico1 = '/';
            break;
        }

        {
        case 1:
            Operando_Matematico2 = '+';         switch(operando_2)

            break;
        case 2:
            Operando_Matematico2 = '-';
            break;
        case 3:
            Operando_Matematico2 = 'x';
            break;
        case 4:
            Operando_Matematico2 = '/';
            break;
        }
    al_draw_textf(fonte, al_map_rgb(0,0,139), pos_X, 390, 0, "%c", Operando_Matematico1);
    al_draw_textf(fonte, al_map_rgb(139,0,0), pos_X, 510, 0, "%c", Operando_Matematico2);
    }
    else
    {
    al_draw_textf(fonte, al_map_rgb(139,0,0), pos_X, 390, 0, "%d", operando_1);
    al_draw_textf(fonte, al_map_rgb(0,0,139), pos_X, 515, 0, "%d", operando_2);
    }

    if(*tempo_operacao == 4)
        *tempo_operacao = 0;
    }

    void DesenhaScore()
    {
     al_draw_textf(fontescore, al_map_rgb(0,0,139), LARG - 300, 25, 0, "Score: %.0f", Score += 0.02);
    }
// ---------------------------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------------
// Main
int main(void){

int operando_1, operando_2, tempo_operacao = 0;
float plataforma_X = LARG;

srand((unsigned)time(NULL));

    //Iniciando Funções
    if(!Inicializar())
        return -1;

    IniciaFundo(&Fundo_Principal, 0, 0, 0.3, 1366, 768, -1, bgImage);
    IniciaFundo(&Chao, 0, ALT - al_get_bitmap_height(chao), 0.8, 1200, 55, -1, chao);
    //---------------

    int fimdojogo = 0;

        while(!fimdojogo)
        {
            //Parallax Fundo, Chão, Plataforma e Operandos
            //Parallax fundo e chão
            AtualizaDesenhaFundo(&Fundo_Principal);
            AtualizaDesenhaFundo(&Chao);

            //Desenho movimentação operandos
            if(plataforma_X == LARG)
                TrocaValorOperacao(&operando_1, &operando_2, &tempo_operacao);
                DesenhaValorOperacao(operando_1, operando_2, &tempo_operacao, plataforma_X);

            //Desenho movimentação plataforma
            MovimentoPlataforma(&plataforma_X);

            //--------------------------------------------------------


           ALLEGRO_EVENT evento;
           ALLEGRO_TIMEOUT timeout;
           al_init_timeout(&timeout, 0.005);

            int tem_eventos = al_wait_for_event_until(filadeeventos, &evento , &timeout);

                if(tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                    fimdojogo = 1;

        DesenhaScore();
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        }


    Finalizar();

   return 0;
}
// ---------------------------------------------------------------------------------------------------------------
// Fim da Main

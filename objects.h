// Objects ID
enum IDS{PLAYER, BULLET, ALVO, ALVOFINAL};

typedef struct{
	int ID;
	int x;
	int y;
	int live;
	int score;
}Character;

// Bullet or Arrow
typedef struct{
	int ID;
	int x;
	int y;
	int speed;	
	bool live;
}Bullet;

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

typedef struct
{
	int ID;
	int x;
	int y;
	bool acertado;
}Alvo;
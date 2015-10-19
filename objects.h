// Objects ID
enum IDS{PLAYER, BULLET, ENEMY};

typedef struct{
	int ID;
	int x;
	int y;
	int live;
	int score;
}Shooter;

// Bullet or Arrow
typedef struct{
	int ID;
	int x;
	int y;
	int live;
}Bullet;

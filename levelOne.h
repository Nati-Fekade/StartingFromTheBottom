#include <stdlib.h>
#include <stdio.h>

// Constants
#define MAPHEIGHT 256
#define MAPWIDTH 512

// Variables
extern int hOff;
extern int vOff;
extern OBJ_ATTR shadowOAM[128];
extern SPRITE fishOne;
extern SPRITE enemy;
extern SPRITE enemy1;
extern SPRITE enemy2;
extern SPRITE enemy3;
extern SPRITE enemy4;
extern SPRITE enemy5;

#define COINS 4
extern SPRITE coins[COINS];

#define SCORENUM 2
extern SPRITE scoreNum[SCORENUM];

extern int health;
extern int enemyCount;

// Prototypes
void initLevelOne();
void initPlayer();

void initCoins();

void initScoreNum();
void initEnemy();
void initEnemy1();
void initEnemy2();
void initEnemy3();
void initEnemy4();
void initEnemy5();

int rand();

void updateLevelOne();
void updatePlayer();

void updateCoins();

void animatePlayer();
void updateEnemy();
void updateEnemy1();
void updateEnemy2();
void updateEnemy3();
void updateEnemy4();
void updateEnemy5();

void drawLevelOne();
void drawScore();
void drawPlayer();

void drawCoins();
void drawHealth();

void drawEnemy();
void drawEnemy1();
void drawEnemy2();
void drawEnemy3();
void drawEnemy4();
void drawEnemy5();

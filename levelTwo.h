#include <stdlib.h>
#include <stdio.h>

// Constants
#define MAPHEIGHT 256
#define MAPWIDTH 512

// Variables
extern int hOff;
extern int vOff;
extern OBJ_ATTR shadowOAM[128];
extern SPRITE fishTwo;
extern SPRITE enemy;
extern SPRITE enemy1;
extern SPRITE enemy2;
extern SPRITE enemy3;
extern SPRITE enemy4;
extern SPRITE enemy5;
extern SPRITE enemy6;
extern SPRITE enemy7;
extern SPRITE enemy8;
extern SPRITE enemy9;

#define COINSTWO 4
extern SPRITE coinsTwo[COINSTWO];

#define SCORENUMTWO 3
extern SPRITE scoreNumTwo[SCORENUMTWO];

extern int healthTwo;
extern int enemyCountTwo;

// Function Prototypes
void initLevelTwo();
void initPlayerTwo();
void initScoreNumTwo();
void initCoinsTwo();

void initTwoEnemy();
void initTwoEnemy1();
void initTwoEnemy2();
void initTwoEnemy3();
void initTwoEnemy4();
void initTwoEnemy5();
void initTwoEnemy6();
void initTwoEnemy7();
void initTwoEnemy8();
void initTwoEnemy9();


int rand();

void updateLevelTwo();
void updatePlayerTwo();
void animatePlayerTwo();
void updateCoinsTwo();

void updateTwoEnemy();
void updateTwoEnemy1();
void updateTwoEnemy2();
void updateTwoEnemy3();
void updateTwoEnemy4();
void updateTwoEnemy5();
void updateTwoEnemy6();
void updateTwoEnemy7();
void updateTwoEnemy8();
void updateTwoEnemy9();

void drawLevelTwo();
void drawScoreTwo();
void drawPlayerTwo();
void drawTwoEnemy();
void drawTwoEnemy1();
void drawTwoEnemy2();
void drawTwoEnemy3();
void drawTwoEnemy4();
void drawTwoEnemy5();
void drawTwoEnemy6();
void drawTwoEnemy7();
void drawTwoEnemy8();
void drawTwoEnemy9();

void drawCoinsTwo();
void drawHealthTwo();
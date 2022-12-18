#include <stdlib.h>
#include <stdio.h>
#include "gba.h"
#include "levelOne.h"
#include "print.h"

#include "sound.h"
#include "screaming.h"
#include "coinSound.h"
#include "yeahSound.h"

// Variables
int hOff;
int vOff;
OBJ_ATTR shadowOAM[128];
SPRITE fishOne;
SPRITE coins[COINS];
SPRITE enemy;
SPRITE enemy1;
SPRITE enemy2;
SPRITE enemy3;
SPRITE enemy4;
SPRITE enemy5;
SPRITE scoreNum[SCORENUM];

int health;
int enemyCount;

int possibleScore[3] = {10, 1};
int scoreTracker;


// Link animation states for aniState
enum {FISHFRONT, FISHBACK, FISHRIGHT, FISHLEFT, FISHIDLE};
enum {COINSIDE, COINFRONT};
enum {ENEMYFRONT, ENEMYBACK, ENEMYRIGHT, ENEMYLEFT, ENEMYIDLE};

// Initialize Level One
void initLevelOne() {
	// Place screen on map
    vOff = 70;
    hOff = 10;

    health = 3;
    enemyCount = 6;

    initPlayer();
    initScoreNum();
    initCoins();

    initEnemy();
    initEnemy1();
    initEnemy2();
    initEnemy3();
    initEnemy4();
    initEnemy5();
}
// Initialize the player
void initPlayer() {
    fishOne.width = 16;
    fishOne.height = 16;
    fishOne.rdel = 1;
    fishOne.cdel = 1;

    // Place in the middle of the screen in the world location chosen earlier
    fishOne.worldRow = SCREENHEIGHT / 2 - fishOne.width / 2 + vOff;
    fishOne.worldCol = SCREENWIDTH / 2 - fishOne.height / 2 + hOff;
    fishOne.aniCounter = 0;
    fishOne.curFrame = 0;
    fishOne.numFrames = 3;
    fishOne.aniState = FISHFRONT;
    fishOne.aniCol = fishOne.aniState;

    fishOne.power = 1;
}
//Initialize the coins
void initCoins() {
    for (int i = 0; i < COINS; i++) {
        coins[i].width = 8;
        coins[i].height = 8;
        coins[i].worldCol = rand() % (MAPWIDTH - coins[i].width);
        coins[i].worldRow = (rand() % (200 - 160 - coins[i].height)) + 162;
        coins[i].aniCounter = 0;
        coins[i].curFrame = 0;
        coins[i].numFrames = 2;
        coins[i].aniState = 1;
        coins[i].active = 1;
        coins[i].power = i + 1;
    }
}
// Initializes the score on top of the fish
void initScoreNum() {
    for (int i = 0; i < SCORENUM; i++) {
        scoreNum[i].width = 8;
        scoreNum[i].height = 8;
        scoreNum[i].worldCol = fishOne.worldCol + (i * 8);
        scoreNum[i].worldRow = fishOne.worldRow - 5;
        scoreNum[i].aniState = 0;
    }
}
// Initialize the red horizontal enemy
void initEnemy() {
    enemy.width = 16;
    enemy.height = 16;
    enemy.rdel = 1;
    enemy.cdel = 1;

    enemy.worldRow = 200;
    enemy.worldCol = 180;
    enemy.aniCounter = 0;
    enemy.curFrame = 0;
    enemy.numFrames = 3;
    enemy.aniState = ENEMYRIGHT;

    enemy.power = 2;
    enemy.active = 1;
}
// Initialize the green vertical enemy
void initEnemy1() {
    enemy1.width = 16;
    enemy1.height = 32;
    enemy1.rdel = 1;
    enemy1.cdel = 1;

    enemy1.worldRow = 180;
    enemy1.worldCol = 60;
    enemy1.aniCounter = 0;
    enemy1.curFrame = 0;
    enemy1.numFrames = 0;
    enemy1.aniState = ENEMYFRONT;

    enemy1.power = 20;
    enemy1.active = 1;
}
// Initialize the brown vertical enemy
void initEnemy2() {
    enemy2.width = 16;
    enemy2.height = 32;
    enemy2.rdel = 1;
    enemy2.cdel = 1;

    enemy2.worldRow = 180;
    enemy2.worldCol = 250;
    enemy2.aniCounter = 0;
    enemy2.curFrame = 0;
    enemy2.numFrames = 0;
    enemy2.aniState = ENEMYFRONT;

    enemy2.power = 30;
    enemy2.active = 1;
}
// Initialize the blue horizontal enemy
void initEnemy3() {
    enemy3.width = 16;
    enemy3.height = 16;
    enemy3.rdel = 1;
    enemy3.cdel = 1;

    enemy3.worldRow = 220;
    enemy3.worldCol = 300;
    enemy3.aniCounter = 0;
    enemy3.curFrame = 0;
    enemy3.numFrames = 3;
    enemy3.aniState = ENEMYRIGHT;

    enemy3.power = 5;
    enemy3.active = 1;
}
// Initialize the green horizontal enemy
void initEnemy4() {
    enemy4.width = 16;
    enemy4.height = 16;
    enemy4.rdel = 1;
    enemy4.cdel = 1;

    enemy4.worldRow = 200;
    enemy4.worldCol = 400;
    enemy4.aniCounter = 0;
    enemy4.curFrame = 0;
    enemy4.numFrames = 3;
    enemy4.aniState = ENEMYRIGHT;

    enemy4.power = 9;
    enemy4.active = 1;
}
// Initialize the blue vertical enemy
void initEnemy5() {
    enemy5.width = 16;
    enemy5.height = 32;
    enemy5.rdel = 1;
    enemy5.cdel = 1;

    enemy5.worldRow = 180;
    enemy5.worldCol = 460;
    enemy5.aniCounter = 0;
    enemy5.curFrame = 0;
    enemy5.numFrames = 0;
    enemy5.aniState = ENEMYFRONT;

    enemy5.power = 15;
    enemy5.active = 1;
}
// Updates the game each frame
void updateLevelOne() {
	updatePlayer();

    updateCoins();

    updateEnemy();
    updateEnemy1();
    updateEnemy2();
    updateEnemy3();
    updateEnemy4();
    updateEnemy5();
}
// Handle every-frame actions of the player
void updatePlayer() {
    if(BUTTON_HELD(BUTTON_UP)) {

        if (fishOne.worldRow > 125) {
            fishOne.worldRow -= fishOne.rdel;

            if (vOff > 0 && (fishOne.worldRow - vOff) <= SCREENHEIGHT / 2) {
                vOff--;
            }
        }
    }
    if(BUTTON_HELD(BUTTON_DOWN)) {
        if (fishOne.worldRow + fishOne.height < 256) {
            fishOne.worldRow += fishOne.rdel;

            if (vOff < MAPHEIGHT - SCREENHEIGHT && (fishOne.worldRow - vOff) > (SCREENHEIGHT / 2)) {
                vOff++;
            }
        }
    }
    if(BUTTON_HELD(BUTTON_LEFT)) {
        if (fishOne.worldCol > 0) {
            fishOne.worldCol -= fishOne.cdel;

            if (hOff > 0 && (fishOne.worldCol - hOff) <= SCREENWIDTH / 2) {
                hOff--;
            }
        }
    }
    if(BUTTON_HELD(BUTTON_RIGHT)) {
        if (fishOne.worldCol + fishOne.width < 512) {
            fishOne.worldCol += fishOne.cdel;

            if (hOff < MAPWIDTH - SCREENWIDTH && (fishOne.worldCol - hOff) > (SCREENWIDTH / 2)) {
                hOff++;
            }
        }
    }

    if (BUTTON_PRESSED(BUTTON_B)) { // SETS the CHEAT MODE !!!
        SPRITEPALETTE[0x09] = SPRITEPALETTE[0x04];
        for (int i = 0; i < COINS; i++) {
            coins[i].power += 3;
        }
    }
    animatePlayer();
}
// Handle player animation states
void animatePlayer() {
    // Set previous state to current state
    fishOne.prevAniState = fishOne.aniState;
    fishOne.aniState = FISHIDLE;

    // Change the animation frame every 10 frames of gameplay
    if (fishOne.aniCounter % 10 == 0) {
        fishOne.curFrame = (fishOne.curFrame + 1) % fishOne.numFrames;
    }

    // Control movement and change animation state
    if (BUTTON_HELD(BUTTON_UP))
        fishOne.aniState = FISHBACK;
    if (BUTTON_HELD(BUTTON_DOWN))
        fishOne.aniState = FISHFRONT;
    if (BUTTON_HELD(BUTTON_LEFT))
        fishOne.aniState = FISHLEFT;
    if (BUTTON_HELD(BUTTON_RIGHT))
        fishOne.aniState = FISHRIGHT;

    // If fishOne's aniState is idle, frame is fishOne standing
    if (fishOne.aniState == FISHIDLE) {
        fishOne.curFrame = 0;
        fishOne.aniCounter = 0;
        fishOne.aniState = fishOne.prevAniState;
    } else {
        fishOne.aniCounter++;
    }

    if (fishOne.aniState == FISHLEFT) {
        fishOne.aniCol = FISHRIGHT;
    } else {
        fishOne.aniCol = fishOne.aniState;
    }
}

// Updates the coins
void updateCoins() {
    for (int i = 0; i < COINS; i++) {
        coins[i].aniCounter++;
        if (coins[i].aniCounter == 20) {
            coins[i].aniCounter = 0;
            coins[i].curFrame = (coins[i].curFrame + 1) % 2;
        }
        if (collision(coins[i].worldCol, coins[i].worldRow, coins[i].width, coins[i].height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
            mgba_printf("Array Coin and fish collide");
            playSoundB(coinSound_data, coinSound_length, 0);
            fishOne.power += coins[i].power;
            coins[i].active = 0;
        }
    }
}
// Updates the red horizontal enemy
void updateEnemy() {
    if (enemy.active) {
        if (enemy.worldCol < 160 || enemy.worldCol > 230) {
            enemy.cdel *= -1;
        }
        enemy.worldCol += enemy.cdel;
        enemy.aniCounter++;

        if (enemy.aniCounter == 20) {
            enemy.aniCounter = 0;
            enemy.curFrame = (enemy.curFrame + 1) % 2;
        }
    }

    if (fishOne.power < enemy.power && 
        collision(enemy.worldCol, enemy.worldRow, enemy.width, enemy.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishOne.worldRow = SCREENHEIGHT / 2 - fishOne.width / 2 + vOff;
        fishOne.worldCol = SCREENWIDTH / 2 - fishOne.height / 2 + hOff;
        health--;
    } else if (fishOne.power > enemy.power && 
        collision(enemy.worldCol, enemy.worldRow, enemy.width, enemy.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishOne.power += enemy.power;
        enemy.active = 0;
        enemyCount--;
    }
}
// Updates the green vertical enemy
void updateEnemy1() {
    if (enemy1.active) {
        if (enemy1.worldRow < 150 || enemy1.worldRow > 220) {
            enemy1.rdel *= -1;
        }
        enemy1.worldRow += enemy1.rdel;
        enemy1.aniCounter++;

        if (enemy1.aniCounter == 20) {
            enemy1.aniCounter = 0;
            enemy1.curFrame = (enemy1.curFrame + 1) % 2;
        }
    }

    if (fishOne.power < enemy1.power && 
        collision(enemy1.worldCol, enemy1.worldRow, enemy1.width, enemy1.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishOne.worldRow = SCREENHEIGHT / 2 - fishOne.width / 2 + vOff;
        fishOne.worldCol = SCREENWIDTH / 2 - fishOne.height / 2 + hOff;
        health--;
    } else if (fishOne.power > enemy1.power && 
        collision(enemy1.worldCol, enemy1.worldRow, enemy1.width, enemy1.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishOne.power += enemy1.power;
        enemy1.active = 0;
        enemyCount--;
    }
}
// Updates the brown vertical enemy
void updateEnemy2() {
    if (enemy2.active) {
        if (enemy2.worldRow < 180 || enemy2.worldRow > 220) {
            enemy2.rdel *= -1;
        }
        enemy2.worldRow += enemy2.rdel;
        enemy2.aniCounter++;

        if (enemy2.aniCounter == 20) {
            enemy2.aniCounter = 0;
            enemy2.curFrame = (enemy2.curFrame + 1) % 2;
        }
    }

    if (fishOne.power < enemy2.power && 
        collision(enemy2.worldCol, enemy2.worldRow, enemy2.width, enemy2.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishOne.worldRow = SCREENHEIGHT / 2 - fishOne.width / 2 + vOff - 15;
        fishOne.worldCol = SCREENWIDTH / 2 - fishOne.height / 2 + hOff;
        health--;
    } else if (fishOne.power > enemy2.power && 
        collision(enemy2.worldCol, enemy2.worldRow, enemy2.width, enemy2.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishOne.power += enemy2.power;
        enemy2.active = 0;
        enemyCount--;
    }
}
// Updates the blue horizontal enemy
void updateEnemy3() {
    if (enemy3.active) {
        if (enemy3.worldCol < 260 || enemy3.worldCol > 330) {
            enemy3.cdel *= -1;
        }
        enemy3.worldCol += enemy3.cdel;
        enemy3.aniCounter++;

        if (enemy3.aniCounter == 20) {
            enemy3.aniCounter = 0;
            enemy3.curFrame = (enemy3.curFrame + 1) % 2;
        }
    }

    if (fishOne.power < enemy3.power && 
        collision(enemy3.worldCol, enemy3.worldRow, enemy3.width, enemy3.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishOne.worldRow = SCREENHEIGHT / 2 - fishOne.width / 2 + vOff;
        fishOne.worldCol = SCREENWIDTH / 2 - fishOne.height / 2 + hOff;
        health--;
    } else if (fishOne.power > enemy3.power && 
        collision(enemy3.worldCol, enemy3.worldRow, enemy3.width, enemy3.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishOne.power += enemy3.power;
        enemy3.active = 0;
        enemyCount--;
    }
}
// Updates the green horizontal enemy
void updateEnemy4() {
    if (enemy4.active) {
        if (enemy4.worldCol < 350 || enemy4.worldCol > 430) {
            enemy4.cdel *= -1;
        }
        enemy4.worldCol += enemy4.cdel;
        enemy4.aniCounter++;

        if (enemy4.aniCounter == 20) {
            enemy4.aniCounter = 0;
            enemy4.curFrame = (enemy4.curFrame + 1) % 2;
        }
    }

    if (fishOne.power < enemy4.power && 
        collision(enemy4.worldCol, enemy4.worldRow, enemy4.width, enemy4.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishOne.worldRow = SCREENHEIGHT / 2 - fishOne.width / 2 + vOff;
        fishOne.worldCol = SCREENWIDTH / 2 - fishOne.height / 2 + hOff;
        health--;
    } else if (fishOne.power > enemy4.power && 
        collision(enemy4.worldCol, enemy4.worldRow, enemy4.width, enemy4.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishOne.power += enemy4.power;
        enemy4.active = 0;
        enemyCount--;
    }
}
// Updates the blue vertizal enemy
void updateEnemy5() {
    if (enemy5.active) {
        if (enemy5.worldRow < 150 || enemy5.worldRow > 220) {
            enemy5.rdel *= -1;
        }
        enemy5.worldRow += enemy5.rdel;
        enemy5.aniCounter++;

        if (enemy5.aniCounter == 20) {
            enemy5.aniCounter = 0;
            enemy5.curFrame = (enemy5.curFrame + 1) % 2;
        }
    }

    if (fishOne.power < enemy5.power && 
        collision(enemy5.worldCol, enemy5.worldRow, enemy5.width, enemy5.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishOne.worldRow = SCREENHEIGHT / 2 - fishOne.width / 2 + vOff;
        fishOne.worldCol = SCREENWIDTH / 2 - fishOne.height / 2 + hOff;
        health--;
    } else if (fishOne.power > enemy5.power && 
        collision(enemy5.worldCol, enemy5.worldRow, enemy5.width, enemy5.height, fishOne.worldCol, fishOne.worldRow, fishOne.width, fishOne.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishOne.power += enemy5.power;
        enemy5.active = 0;
        enemyCount--;
    }
}
// Draws the game each frame
void drawLevelOne() {
    drawPlayer();
    drawCoins();
    drawScore();
    drawHealth();

    drawEnemy();
    drawEnemy1();
    drawEnemy2();
    drawEnemy3();
    drawEnemy4();
    drawEnemy5();

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128 * 4);

    REG_BG0HOFF = hOff;
    REG_BG0VOFF = vOff;
    
    REG_BG1HOFF = hOff / 3;
    REG_BG1VOFF = vOff / 3;
}

// Draw the player
void drawPlayer() {
    shadowOAM[0].attr0 = (ROWMASK & (fishOne.worldRow - vOff)) | ATTR0_SQUARE;
    shadowOAM[0].attr1 = (COLMASK & (fishOne.worldCol - hOff)) | ATTR1_SMALL;
    shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(fishOne.aniCol * 2, fishOne.curFrame * 2) | ATTR2_PRIORITY(1);

    if (fishOne.aniState == FISHLEFT) {
        shadowOAM[0].attr1 |= ATTR1_HFLIP;
    }
}
// Draw the coins all over the screen
void drawCoins() {
    for (int i = 0; i < COINS; i++) {
        if (coins[i].active) {
            if (coins[i].worldCol + coins[i].width > hOff && coins[i].worldCol < SCREENWIDTH + hOff) {
                shadowOAM[100 + i].attr0 = (ROWMASK & (coins[i].worldRow - vOff)) | ATTR0_SQUARE;
                shadowOAM[100 + i].attr1 = (ROWMASK & (coins[i].worldCol - hOff)) | ATTR1_TINY;
                shadowOAM[100 + i].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(7 + coins[i].aniState, 28 + coins[i].curFrame);
            } else {
                shadowOAM[100 + i].attr0 = ATTR0_HIDE;
            } 
        } else {
            shadowOAM[100 + i].attr0 = ATTR0_HIDE;
            coins[i].worldCol = 0;
            coins[i].power = 0;
        }
    }
}

void drawHealth() {
    shadowOAM[50].attr0 = 150 | ATTR0_WIDE;
    shadowOAM[50].attr1 = 3 | ATTR1_SMALL;
    shadowOAM[50].attr2 = ATTR2_TILEID(0, 29);

    for (int i = 0; i < health; i++) {
        SCREENBLOCK[28].tilemap[OFFSET(5, 19, 32)] = 1;
        SCREENBLOCK[28].tilemap[OFFSET(7, 19, 32)] = 1;
        SCREENBLOCK[28].tilemap[OFFSET(9, 19, 32)] = 1;

        if (health == 2) {
            SCREENBLOCK[28].tilemap[OFFSET(9, 19, 32)] = 2;
        } else if (health == 1) {
            SCREENBLOCK[28].tilemap[OFFSET(9, 19, 32)] = 2;
            SCREENBLOCK[28].tilemap[OFFSET(7, 19, 32)] = 2;
        } else if (health == 0) {
            SCREENBLOCK[28].tilemap[OFFSET(9, 19, 32)] = 2;
            SCREENBLOCK[28].tilemap[OFFSET(7, 19, 32)] = 2;
            SCREENBLOCK[28].tilemap[OFFSET(5, 19, 32)] = 2;
        }
    }
}

void drawScore() {
    scoreTracker = fishOne.power;
    for (int i = 0; i < SCORENUM; i++) {
        scoreNum[i].aniState = scoreTracker / possibleScore[i];
        scoreTracker = fishOne.power % possibleScore[i];

        shadowOAM[120 + i].attr0 = (ROWMASK & (fishOne.worldRow - 5 - vOff)) | ATTR0_SQUARE;
        shadowOAM[120 + i].attr1 = (COLMASK & (fishOne.worldCol - hOff + i*8)) | ATTR1_TINY;
        shadowOAM[120 + i].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(scoreNum[i].aniState, 31);
    }
}
// draws the red horizontal enemy fish
void drawEnemy() {
   if (enemy.active) {
        shadowOAM[1].attr0 = (ROWMASK & (enemy.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[1].attr1 = (COLMASK & (enemy.worldCol - hOff)) | ATTR1_SMALL;
        shadowOAM[1].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(13 - enemy.cdel, enemy.curFrame*2);

        shadowOAM[10].attr0 = (ROWMASK & (enemy.worldRow - 5 - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[10].attr1 = (COLMASK & (enemy.worldCol - hOff)) | ATTR1_TINY;
        shadowOAM[10].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2, 31);
    } else {
        shadowOAM[1].attr0 = ATTR0_HIDE;
        shadowOAM[10].attr0 = ATTR0_HIDE;
        enemy.cdel = 0;
        enemy.worldCol = 0;
    }
}

void drawEnemy1() {    
    if (enemy1.active) {
        shadowOAM[2].attr0 = (ROWMASK & (enemy1.worldRow - vOff)) | ATTR0_4BPP | ATTR0_TALL;
        shadowOAM[2].attr1 = (COLMASK & (enemy1.worldCol - hOff)) | ATTR1_MEDIUM;
        shadowOAM[2].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(25 - enemy1.rdel , enemy1.curFrame*4);

        shadowOAM[11].attr0 = (ROWMASK & (enemy1.worldRow - vOff - 8)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[11].attr1 = (COLMASK & (enemy1.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[11].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2, 31);
        
        shadowOAM[16].attr0 = (ROWMASK & (enemy1.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[16].attr1 = (COLMASK & (enemy1.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[16].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 31);
    } else {
        shadowOAM[2].attr0 = ATTR0_HIDE;
        shadowOAM[11].attr0 = ATTR0_HIDE;
        shadowOAM[16].attr0 = ATTR0_HIDE;
        enemy1.rdel = 0;
        enemy1.worldCol = 0;
    }
}

void drawEnemy2() {    
    if (enemy2.active) {
        shadowOAM[3].attr0 = (ROWMASK & (enemy2.worldRow - vOff)) | ATTR0_4BPP | ATTR0_TALL;
        shadowOAM[3].attr1 = (COLMASK & (enemy2.worldCol - hOff)) | ATTR1_MEDIUM;
        shadowOAM[3].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(17 - enemy2.rdel , enemy2.curFrame*4);

        shadowOAM[12].attr0 = (ROWMASK & (enemy2.worldRow - vOff - 8)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[12].attr1 = (COLMASK & (enemy2.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[12].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(3, 31);

        shadowOAM[17].attr0 = (ROWMASK & (enemy2.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[17].attr1 = (COLMASK & (enemy2.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[17].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 31);
    } else {
        shadowOAM[3].attr0 = ATTR0_HIDE;
        shadowOAM[12].attr0 = ATTR0_HIDE;
        shadowOAM[17].attr0 = ATTR0_HIDE;
        enemy2.rdel = 0;
        enemy2.worldCol = 0;
    }
}
// draws the blue horizontal fish
void drawEnemy3() {
   if (enemy3.active) {
        shadowOAM[4].attr0 = (ROWMASK & (enemy3.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[4].attr1 = (COLMASK & (enemy3.worldCol - hOff)) | ATTR1_SMALL;
        shadowOAM[4].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(29 - enemy3.cdel, 6 + enemy3.curFrame*2);

        shadowOAM[13].attr0 = (ROWMASK & (enemy3.worldRow - 5 - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[13].attr1 = (COLMASK & (enemy3.worldCol - hOff)) | ATTR1_TINY;
        shadowOAM[13].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(5, 31);
    } else {
        shadowOAM[4].attr0 = ATTR0_HIDE;
        shadowOAM[13].attr0 = ATTR0_HIDE;
        enemy3.cdel = 0;
        enemy3.worldCol = 0;
    }
}
// draws the green horizontal fish
void drawEnemy4() {
   if (enemy4.active) {
        shadowOAM[5].attr0 = (ROWMASK & (enemy4.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[5].attr1 = (COLMASK & (enemy4.worldCol - hOff)) | ATTR1_SMALL;
        shadowOAM[5].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(29 - enemy4.cdel, enemy4.curFrame*2);

        shadowOAM[14].attr0 = (ROWMASK & (enemy4.worldRow - 5 - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[14].attr1 = (COLMASK & (enemy4.worldCol - hOff)) | ATTR1_TINY;

        shadowOAM[14].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(9, 31);
    } else {
        shadowOAM[5].attr0 = ATTR0_HIDE;
        shadowOAM[14].attr0 = ATTR0_HIDE;
        enemy4.cdel = 0;
        enemy4.worldCol = 0;        
    }
}

void drawEnemy5() {    
    if (enemy5.active) {
        shadowOAM[6].attr0 = (ROWMASK & (enemy5.worldRow - vOff)) | ATTR0_4BPP | ATTR0_TALL;
        shadowOAM[6].attr1 = (COLMASK & (enemy5.worldCol - hOff)) | ATTR1_MEDIUM;
        shadowOAM[6].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(25 - enemy5.rdel , 12 + enemy5.curFrame*4);

        shadowOAM[15].attr0 = (ROWMASK & (enemy5.worldRow - vOff - 8)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[15].attr1 = (COLMASK & (enemy5.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[15].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(1, 31);

        shadowOAM[18].attr0 = (ROWMASK & (enemy5.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[18].attr1 = (COLMASK & (enemy5.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[18].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(5, 31);
    } else {
        shadowOAM[6].attr0 = ATTR0_HIDE;
        shadowOAM[15].attr0 = ATTR0_HIDE;
        shadowOAM[18].attr0 = ATTR0_HIDE;
        enemy5.rdel = 0;
        enemy5.worldCol = 0;
    }
}

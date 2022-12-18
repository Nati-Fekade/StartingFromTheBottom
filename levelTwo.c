#include <stdlib.h>
#include <stdio.h>
#include "gba.h"
#include "levelTwo.h"
#include "print.h"

#include "sound.h"
#include "screaming.h"
#include "coinSound.h"
#include "yeahSound.h"

// Variables
int hOff;
int vOff;
OBJ_ATTR shadowOAM[128];
SPRITE fishTwo;

SPRITE coinsTwo[COINSTWO];

SPRITE enemy;
SPRITE enemy1;
SPRITE enemy2;
SPRITE enemy3;
SPRITE enemy4;
SPRITE enemy5;
SPRITE enemy6;
SPRITE enemy7;
SPRITE enemy8;
SPRITE enemy9;
SPRITE scoreNumTwo[SCORENUMTWO];

int healthTwo;
int enemyCountTwo;

int possibleScoreTwo[3] = {100, 10, 1};
int scoreTracker;

// Link animation states for aniState
enum {FISHFRONT, FISHBACK, FISHRIGHT, FISHLEFT, FISHIDLE};
enum {COINSIDE, COINFRONT};
enum {ENEMYFRONT, ENEMYBACK, ENEMYRIGHT, ENEMYLEFT, ENEMYIDLE};

// Initialize Level Two
void initLevelTwo() {
	// Place screen on map
    vOff = 70;
    hOff = 10;

    healthTwo = 3;
    enemyCountTwo = 10;

    initPlayerTwo();
    initScoreNumTwo();
    initCoinsTwo();

    initTwoEnemy();
    initTwoEnemy1();
    initTwoEnemy2();
    initTwoEnemy3();
    initTwoEnemy4();
    initTwoEnemy5();
    initTwoEnemy6();
    initTwoEnemy7();
    initTwoEnemy8();
    initTwoEnemy9();
}
// Initialize the player
void initPlayerTwo() {
    fishTwo.width = 16;
    fishTwo.height = 16;
    fishTwo.rdel = 1;
    fishTwo.cdel = 1;

    // Place in the middle of the screen in the world location chosen earlier
    fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff;
    fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
    fishTwo.aniCounter = 0;
    fishTwo.curFrame = 0;
    fishTwo.numFrames = 3;
    fishTwo.aniState = FISHFRONT;
    fishTwo.aniCol = fishTwo.aniState;

    fishTwo.power = 1;
}
// Initialize the coins
void initCoinsTwo() {
    for (int i = 0; i < COINSTWO; i++) {
        coinsTwo[i].width = 8;
        coinsTwo[i].height = 8;
        coinsTwo[i].worldCol = rand() % (MAPWIDTH - coinsTwo[i].width);
        coinsTwo[i].worldRow = (rand() % (MAPHEIGHT - coinsTwo[i].height));
        coinsTwo[i].aniCounter = 0;
        coinsTwo[i].curFrame = 0;
        coinsTwo[i].numFrames = 2;
        coinsTwo[i].aniState = 1;
        coinsTwo[i].active = 1;
        coinsTwo[i].power = i + 2;
    }
}

// Initializes the score on top of the fish
void initScoreNumTwo() {
    for (int i = 0; i < SCORENUMTWO; i++) {
        scoreNumTwo[i].width = 8;
        scoreNumTwo[i].height = 8;
        scoreNumTwo[i].worldCol = fishTwo.worldCol + (i * 8);
        scoreNumTwo[i].worldRow = fishTwo.worldRow - 5;
        scoreNumTwo[i].aniState = 0;
    }
}
// Initialize the red horizontal enemy
void initTwoEnemy() {
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
void initTwoEnemy1() {
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
void initTwoEnemy2() {
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
void initTwoEnemy3() {
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
void initTwoEnemy4() {
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
void initTwoEnemy5() {
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
// Initialize the brown horizontal enemy
void initTwoEnemy6() {
    enemy6.width = 16;
    enemy6.height = 16;
    enemy6.rdel = 1;
    enemy6.cdel = 1;

    enemy6.worldRow = 50;
    enemy6.worldCol = 400;
    enemy6.aniCounter = 0;
    enemy6.curFrame = 0;
    enemy6.numFrames = 3;
    enemy6.aniState = ENEMYRIGHT;

    enemy6.power = 35;
    enemy6.active = 1;    
}
// Initialize the blue horizontal enemy
void initTwoEnemy7() {
    enemy7.width = 16;
    enemy7.height = 16;
    enemy7.rdel = 1;
    enemy7.cdel = 1;

    enemy7.worldRow = 100;
    enemy7.worldCol = 20;
    enemy7.aniCounter = 0;
    enemy7.curFrame = 0;
    enemy7.numFrames = 3;
    enemy7.aniState = ENEMYRIGHT;

    enemy7.power = 25;
    enemy7.active = 1;    
}
// Initialize the red vertical enemy
void initTwoEnemy8() {
    enemy8.width = 16;
    enemy8.height = 32;
    enemy8.rdel = 1;
    enemy8.cdel = 1;

    enemy8.worldRow = 80;
    enemy8.worldCol = 300;
    enemy8.aniCounter = 0;
    enemy8.curFrame = 0;
    enemy8.numFrames = 0;
    enemy8.aniState = ENEMYFRONT;

    enemy8.power = 50;
    enemy8.active = 1;
}
// Initialize the green vertical enemy
void initTwoEnemy9() {
    enemy9.width = 16;
    enemy9.height = 32;
    enemy9.rdel = 1;
    enemy9.cdel = 1;

    enemy9.worldRow = 80;
    enemy9.worldCol = 360;
    enemy9.aniCounter = 0;
    enemy9.curFrame = 0;
    enemy9.numFrames = 0;
    enemy9.aniState = ENEMYFRONT;

    enemy9.power = 40;
    enemy9.active = 1;
}
// Updates the game each frame
void updateLevelTwo() {
	updatePlayerTwo();
    updateCoinsTwo();

    updateTwoEnemy();
    updateTwoEnemy1();
    updateTwoEnemy2();
    updateTwoEnemy3();
    updateTwoEnemy4();
    updateTwoEnemy5();
    updateTwoEnemy6();
    updateTwoEnemy7();
    updateTwoEnemy8();
    updateTwoEnemy9();
}

// Handle every-frame actions of the player
void updatePlayerTwo() {
    if(BUTTON_HELD(BUTTON_UP)) {

        if (fishTwo.worldRow > 1) {
            fishTwo.worldRow -= fishTwo.rdel;

            if (vOff > 0 && (fishTwo.worldRow - vOff) <= SCREENHEIGHT / 2) {
                vOff--;
            }
        }
    }
    if(BUTTON_HELD(BUTTON_DOWN)) {
        if (fishTwo.worldRow + fishTwo.height < 256) {
            fishTwo.worldRow += fishTwo.rdel;

            if (vOff < MAPHEIGHT - SCREENHEIGHT && (fishTwo.worldRow - vOff) > (SCREENHEIGHT / 2)) {
                vOff++;
            }
        }
    }
    if(BUTTON_HELD(BUTTON_LEFT)) {
        if (fishTwo.worldCol > 0) {
            fishTwo.worldCol -= fishTwo.cdel;

            if (hOff > 0 && (fishTwo.worldCol - hOff) <= SCREENWIDTH / 2) {
                hOff--;
            }
        }
    }
    if(BUTTON_HELD(BUTTON_RIGHT)) {
        if (fishTwo.worldCol + fishTwo.width < 512) {
            fishTwo.worldCol += fishTwo.cdel;

            if (hOff < MAPWIDTH - SCREENWIDTH && (fishTwo.worldCol - hOff) > (SCREENWIDTH / 2)) {
                hOff++;
            }
        }
    }
    
    if (BUTTON_PRESSED(BUTTON_B)) { // SETS the CHEAT MODE !!!
        SPRITEPALETTE[0x09] = SPRITEPALETTE[0x04];
        for (int i = 0; i < COINSTWO; i++) {
            coinsTwo[i].power += 10;
        }
    }
    animatePlayerTwo();
}
// Handle player animation states
void animatePlayerTwo() {
    // Set previous state to current state
    fishTwo.prevAniState = fishTwo.aniState;
    fishTwo.aniState = FISHIDLE;

    // Change the animation frame every 10 frames of gameplay
    if (fishTwo.aniCounter % 10 == 0) {
        fishTwo.curFrame = (fishTwo.curFrame + 1) % fishTwo.numFrames;
    }

    // Control movement and change animation state
    if (BUTTON_HELD(BUTTON_UP))
        fishTwo.aniState = FISHBACK;
    if (BUTTON_HELD(BUTTON_DOWN))
        fishTwo.aniState = FISHFRONT;
    if (BUTTON_HELD(BUTTON_LEFT))
        fishTwo.aniState = FISHLEFT;
    if (BUTTON_HELD(BUTTON_RIGHT))
        fishTwo.aniState = FISHRIGHT;

    // If fishTwo's aniState is idle, frame is fishTwo standing
    if (fishTwo.aniState == FISHIDLE) {
        fishTwo.curFrame = 0;
        fishTwo.aniCounter = 0;
        fishTwo.aniState = fishTwo.prevAniState;
    } else {
        fishTwo.aniCounter++;
    }

    if (fishTwo.aniState == FISHLEFT) {
        fishTwo.aniCol = FISHRIGHT;
    } else {
        fishTwo.aniCol = fishTwo.aniState;
    }
}

// Updates the coins
void updateCoinsTwo() {
    for (int i = 0; i < COINSTWO; i++) {
        coinsTwo[i].aniCounter++;
        if (coinsTwo[i].aniCounter == 20) {
            coinsTwo[i].aniCounter = 0;
            coinsTwo[i].curFrame = (coinsTwo[i].curFrame + 1) % 2;
        }
        if (collision(coinsTwo[i].worldCol, coinsTwo[i].worldRow, coinsTwo[i].width, coinsTwo[i].height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
            mgba_printf("Coin and fish collide");
            playSoundB(coinSound_data, coinSound_length, 0);
            fishTwo.power += coinsTwo[i].power;
            coinsTwo[i].active = 0;
        }
    }
}

// Updates the red horizontal enemy
void updateTwoEnemy() {
    if (enemy.active) {
        if (enemy.worldCol < 100 || enemy.worldCol > 230) {
            enemy.cdel *= -1;
        }
        enemy.worldCol += enemy.cdel;
        enemy.aniCounter++;

        if (enemy.aniCounter == 20) {
            enemy.aniCounter = 0;
            enemy.curFrame = (enemy.curFrame + 1) % 2;
        }
    }

    if (fishTwo.power < enemy.power && 
        collision(enemy.worldCol, enemy.worldRow, enemy.width, enemy.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff;
        fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
        healthTwo--;
    } else if (fishTwo.power > enemy.power && 
        collision(enemy.worldCol, enemy.worldRow, enemy.width, enemy.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishTwo.power += enemy.power;
        enemy.active = 0;
        enemyCountTwo--;
    }
}
// Updates the green vertical enemy
void updateTwoEnemy1() {
    if (enemy1.active) {
        if (enemy1.worldRow < 100 || enemy1.worldRow > 220) {
            enemy1.rdel *= -1;
        }
        enemy1.worldRow += enemy1.rdel;
        enemy1.aniCounter++;

        if (enemy1.aniCounter == 20) {
            enemy1.aniCounter = 0;
            enemy1.curFrame = (enemy1.curFrame + 1) % 2;
        }
    }

    if (fishTwo.power < enemy1.power && 
        collision(enemy1.worldCol, enemy1.worldRow, enemy1.width, enemy1.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff;
        fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
        healthTwo--;
    } else if (fishTwo.power > enemy1.power && 
        collision(enemy1.worldCol, enemy1.worldRow, enemy1.width, enemy1.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishTwo.power += enemy1.power;
        enemy1.active = 0;
        enemyCountTwo--;
    }
}
// Updates the brown vertical enemy
void updateTwoEnemy2() {
    if (enemy2.active) {
        if (enemy2.worldRow < 100 || enemy2.worldRow > 200) {
            enemy2.rdel *= -1;
        }
        enemy2.worldRow += enemy2.rdel;
        enemy2.aniCounter++;

        if (enemy2.aniCounter == 20) {
            enemy2.aniCounter = 0;
            enemy2.curFrame = (enemy2.curFrame + 1) % 2;
        }
    }

    if (fishTwo.power < enemy2.power && 
        collision(enemy2.worldCol, enemy2.worldRow, enemy2.width, enemy2.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff - 15;
        fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
        enemy2.worldCol += 20;
        healthTwo--;
    } else if (fishTwo.power > enemy2.power && 
        collision(enemy2.worldCol, enemy2.worldRow, enemy2.width, enemy2.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishTwo.power += enemy2.power;
        enemy2.active = 0;
        enemyCountTwo--;
    }
}
// Updates the blue horizontal enemy
void updateTwoEnemy3() {
    if (enemy3.active) {
        if (enemy3.worldCol < 160 || enemy3.worldCol > 330) {
            enemy3.cdel *= -1;
        }
        enemy3.worldCol += enemy3.cdel;
        enemy3.aniCounter++;

        if (enemy3.aniCounter == 20) {
            enemy3.aniCounter = 0;
            enemy3.curFrame = (enemy3.curFrame + 1) % 2;
        }
    }

    if (fishTwo.power < enemy3.power && 
        collision(enemy3.worldCol, enemy3.worldRow, enemy3.width, enemy3.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff;
        fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
        enemy3.worldCol += 50;
        healthTwo--;
    } else if (fishTwo.power > enemy3.power && 
        collision(enemy3.worldCol, enemy3.worldRow, enemy3.width, enemy3.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishTwo.power += enemy3.power;
        enemy3.active = 0;
        enemyCountTwo--;
    }
}
// Updates the green horizontal enemy
void updateTwoEnemy4() {
    if (enemy4.active) {
        if (enemy4.worldCol < 350 || enemy4.worldCol > 500) {
            enemy4.cdel *= -1;
        }
        enemy4.worldCol += enemy4.cdel;
        enemy4.aniCounter++;

        if (enemy4.aniCounter == 20) {
            enemy4.aniCounter = 0;
            enemy4.curFrame = (enemy4.curFrame + 1) % 2;
        }
    }

    if (fishTwo.power < enemy4.power && 
        collision(enemy4.worldCol, enemy4.worldRow, enemy4.width, enemy4.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff;
        fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
        healthTwo--;
    } else if (fishTwo.power > enemy4.power && 
        collision(enemy4.worldCol, enemy4.worldRow, enemy4.width, enemy4.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishTwo.power += enemy4.power;
        enemy4.active = 0;
        enemyCountTwo--;
    }
}
// Updates the blue vertizal enemy
void updateTwoEnemy5() {
    if (enemy5.active) {
        if (enemy5.worldRow < 50 || enemy5.worldRow > 220) {
            enemy5.rdel *= -1;
        }
        enemy5.worldRow += enemy5.rdel;
        enemy5.aniCounter++;

        if (enemy5.aniCounter == 20) {
            enemy5.aniCounter = 0;
            enemy5.curFrame = (enemy5.curFrame + 1) % 2;
        }
    }

    if (fishTwo.power < enemy5.power && 
        collision(enemy5.worldCol, enemy5.worldRow, enemy5.width, enemy5.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff;
        fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
        enemy5.worldRow -= 20;
        healthTwo--;
    } else if (fishTwo.power > enemy5.power && 
        collision(enemy5.worldCol, enemy5.worldRow, enemy5.width, enemy5.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishTwo.power += enemy5.power;
        enemy5.active = 0;
        enemyCountTwo--;
    }
}
// Updates the brown horizontal enemy
void updateTwoEnemy6() {
    if (enemy6.active) {
        if (enemy6.worldCol < 350 || enemy6.worldCol > 450) {
            enemy6.cdel *= -1;
        }
        enemy6.worldCol += enemy6.cdel;
        enemy6.aniCounter++;

        if (enemy6.aniCounter == 20) {
            enemy6.aniCounter = 0;
            enemy6.curFrame = (enemy6.curFrame + 1) % 2;
        }
    }

    if (fishTwo.power < enemy6.power && 
        collision(enemy6.worldCol, enemy6.worldRow, enemy6.width, enemy6.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff;
        fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
        healthTwo--;
    } else if (fishTwo.power > enemy6.power && 
        collision(enemy6.worldCol, enemy6.worldRow, enemy6.width, enemy6.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishTwo.power += enemy6.power;
        enemy6.active = 0;
        enemyCountTwo--;
    }
}
// Updates the blue horizontal enemy
void updateTwoEnemy7() {
    if (enemy7.active) {
        if (enemy7.worldCol < 10 || enemy7.worldCol > 400) {
            enemy7.cdel *= -1;
        }
        enemy7.worldCol += enemy7.cdel;
        enemy7.aniCounter++;

        if (enemy7.aniCounter == 20) {
            enemy7.aniCounter = 0;
            enemy7.curFrame = (enemy7.curFrame + 1) % 2;
        }
    }

    if (fishTwo.power < enemy7.power && 
        collision(enemy7.worldCol, enemy7.worldRow, enemy7.width, enemy7.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff;
        fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
        enemy7.worldRow -= 20;
        healthTwo--;
    } else if (fishTwo.power > enemy7.power && 
        collision(enemy7.worldCol, enemy7.worldRow, enemy7.width, enemy7.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishTwo.power += enemy7.power;
        enemy7.active = 0;
        enemyCountTwo--;
    }
}
// Updates the red vertical enemy
void updateTwoEnemy8() {
    if (enemy8.active) {
        if (enemy8.worldRow < 50 || enemy8.worldRow > 220) {
            enemy8.rdel *= -1;
        }
        enemy8.worldRow += enemy8.rdel;
        enemy8.aniCounter++;

        if (enemy8.aniCounter == 20) {
            enemy8.aniCounter = 0;
            enemy8.curFrame = (enemy8.curFrame + 1) % 2;
        }
    }

    if (fishTwo.power < enemy8.power && 
        collision(enemy8.worldCol, enemy8.worldRow, enemy8.width, enemy8.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff;
        fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
        enemy8.worldCol += 20;
        healthTwo--;
    } else if (fishTwo.power > enemy8.power && 
        collision(enemy8.worldCol, enemy8.worldRow, enemy8.width, enemy8.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishTwo.power += enemy8.power;
        enemy8.active = 0;
        enemyCountTwo--;
    }
}
// Updates the green vertical enemy
void updateTwoEnemy9() {
    if (enemy9.active) {
        if (enemy9.worldRow < 50 || enemy9.worldRow > 220) {
            enemy9.rdel *= -1;
        }
        enemy9.worldRow += enemy9.rdel;
        enemy9.aniCounter++;

        if (enemy9.aniCounter == 20) {
            enemy9.aniCounter = 0;
            enemy9.curFrame = (enemy9.curFrame + 1) % 2;
        }
    }

    if (fishTwo.power < enemy9.power && 
        collision(enemy9.worldCol, enemy9.worldRow, enemy9.width, enemy9.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(screaming_data, screaming_length, 0);
        fishTwo.worldRow = SCREENHEIGHT / 2 - fishTwo.width / 2 + vOff;
        fishTwo.worldCol = SCREENWIDTH / 2 - fishTwo.height / 2 + hOff;
        enemy9.worldCol += 20;
        healthTwo--;
    } else if (fishTwo.power > enemy9.power && 
        collision(enemy9.worldCol, enemy9.worldRow, enemy9.width, enemy9.height, fishTwo.worldCol, fishTwo.worldRow, fishTwo.width, fishTwo.height)) {
        playSoundB(yeahSound_data, yeahSound_length, 0);
        fishTwo.power += enemy9.power;
        enemy9.active = 0;
        enemyCountTwo--;
    }
}
// Draws the game each frame
void drawLevelTwo() {
    drawPlayerTwo();
    drawCoinsTwo();
    drawHealthTwo();
    drawScoreTwo();

    drawTwoEnemy();
    drawTwoEnemy1();
    drawTwoEnemy2();
    drawTwoEnemy3();
    drawTwoEnemy4();
    drawTwoEnemy5();
    drawTwoEnemy6();
    drawTwoEnemy7();
    drawTwoEnemy8();
    drawTwoEnemy9();

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128 * 4);

    REG_BG1HOFF = hOff;
    REG_BG1VOFF = vOff;

    REG_BG0HOFF = hOff / 3;
    REG_BG0VOFF = vOff / 3;
}

// Draw the player
void drawPlayerTwo() {
    shadowOAM[30].attr0 = (ROWMASK & (fishTwo.worldRow - vOff)) | ATTR0_SQUARE;
    shadowOAM[30].attr1 = (COLMASK & (fishTwo.worldCol - hOff)) | ATTR1_SMALL;
    shadowOAM[30].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(fishTwo.aniCol * 2, fishTwo.curFrame * 2) | ATTR2_PRIORITY(1);

    if (fishTwo.aniState == FISHLEFT) {
        shadowOAM[30].attr1 |= ATTR1_HFLIP;
    }
}

// Draw the coins all over the screen
void drawCoinsTwo() {
    for (int i = 0; i < COINSTWO; i++) {
        if (coinsTwo[i].active) {
            if (coinsTwo[i].worldCol + coinsTwo[i].width > hOff && coinsTwo[i].worldCol < SCREENWIDTH + hOff) {
                shadowOAM[100 + i].attr0 = (ROWMASK & (coinsTwo[i].worldRow - vOff)) | ATTR0_SQUARE;
                shadowOAM[100 + i].attr1 = (ROWMASK & (coinsTwo[i].worldCol - hOff)) | ATTR1_TINY;
                shadowOAM[100 + i].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(7 + coinsTwo[i].aniState, 28 + coinsTwo[i].curFrame);
            } else {
                shadowOAM[100 + i].attr0 = ATTR0_HIDE;
            } 
        } else {
            shadowOAM[100 + i].attr0 = ATTR0_HIDE;
            coinsTwo[i].worldCol = 0;
            coinsTwo[i].power = 0;
        }
    }
}
// Draws the hearts for player
void drawHealthTwo() {
    shadowOAM[90].attr0 = 150 | ATTR0_WIDE;
    shadowOAM[90].attr1 = 3 | ATTR1_SMALL;
    shadowOAM[90].attr2 = ATTR2_TILEID(0, 29);

    for (int i = 0; i < healthTwo; i++) {
        SCREENBLOCK[28].tilemap[OFFSET(5, 19, 32)] = 1;
        SCREENBLOCK[28].tilemap[OFFSET(7, 19, 32)] = 1;
        SCREENBLOCK[28].tilemap[OFFSET(9, 19, 32)] = 1;

        if (healthTwo == 2) {
            SCREENBLOCK[28].tilemap[OFFSET(9, 19, 32)] = 2;
        } else if (healthTwo == 1) {
            SCREENBLOCK[28].tilemap[OFFSET(9, 19, 32)] = 2;
            SCREENBLOCK[28].tilemap[OFFSET(7, 19, 32)] = 2;
        } else if (healthTwo == 0) {
            SCREENBLOCK[28].tilemap[OFFSET(9, 19, 32)] = 2;
            SCREENBLOCK[28].tilemap[OFFSET(7, 19, 32)] = 2;
            SCREENBLOCK[28].tilemap[OFFSET(5, 19, 32)] = 2;
        }
    }
}
// Draws player's score
void drawScoreTwo() {
    scoreTracker = fishTwo.power;
    for (int i = 0; i < SCORENUMTWO; i++) {
        scoreNumTwo[i].aniState = scoreTracker / possibleScoreTwo[i];
        scoreTracker = fishTwo.power % possibleScoreTwo[i];

        shadowOAM[70 + i].attr0 = (ROWMASK & (fishTwo.worldRow - 5 - vOff)) | ATTR0_SQUARE;
        shadowOAM[70 + i].attr1 = (COLMASK & (fishTwo.worldCol - hOff + i*8)) | ATTR1_TINY;
        shadowOAM[70 + i].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(scoreNumTwo[i].aniState, 31);
    }
}
// Draw red horizontal
void drawTwoEnemy() {
   if (enemy.active) {
        shadowOAM[31].attr0 = (ROWMASK & (enemy.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[31].attr1 = (COLMASK & (enemy.worldCol - hOff)) | ATTR1_SMALL;
        shadowOAM[31].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(13 - enemy.cdel, enemy.curFrame*2);

        shadowOAM[32].attr0 = (ROWMASK & (enemy.worldRow - 5 - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[32].attr1 = (COLMASK & (enemy.worldCol - hOff)) | ATTR1_TINY;
        shadowOAM[32].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2, 31);
    } else {
        shadowOAM[31].attr0 = ATTR0_HIDE;
        shadowOAM[32].attr0 = ATTR0_HIDE;
        enemy.cdel = 0;
        enemy.worldCol = 0;        
    }
}
// Draw green vertical
void drawTwoEnemy1() {    
    if (enemy1.active) {
        shadowOAM[33].attr0 = (ROWMASK & (enemy1.worldRow - vOff)) | ATTR0_4BPP | ATTR0_TALL;
        shadowOAM[33].attr1 = (COLMASK & (enemy1.worldCol - hOff)) | ATTR1_MEDIUM;
        shadowOAM[33].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(25 - enemy1.rdel , enemy1.curFrame*4);

        shadowOAM[34].attr0 = (ROWMASK & (enemy1.worldRow - vOff - 8)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[34].attr1 = (COLMASK & (enemy1.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[34].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2, 31);

        shadowOAM[57].attr0 = (ROWMASK & (enemy1.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[57].attr1 = (COLMASK & (enemy1.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[57].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 31);
    } else {
        shadowOAM[33].attr0 = ATTR0_HIDE;
        shadowOAM[34].attr0 = ATTR0_HIDE;
        shadowOAM[57].attr0 = ATTR0_HIDE;
        enemy1.rdel = 0;
        enemy1.worldCol = 0;
    }
}
// Draw brown vertical
void drawTwoEnemy2() {    
    if (enemy2.active) {
        shadowOAM[35].attr0 = (ROWMASK & (enemy2.worldRow - vOff)) | ATTR0_4BPP | ATTR0_TALL;
        shadowOAM[35].attr1 = (COLMASK & (enemy2.worldCol - hOff)) | ATTR1_MEDIUM;
        shadowOAM[35].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(17 - enemy2.rdel , enemy2.curFrame*4);

        shadowOAM[36].attr0 = (ROWMASK & (enemy2.worldRow - vOff - 8)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[36].attr1 = (COLMASK & (enemy2.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[36].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(3, 31);

        shadowOAM[58].attr0 = (ROWMASK & (enemy2.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[58].attr1 = (COLMASK & (enemy2.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[58].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 31);
    } else {
        shadowOAM[35].attr0 = ATTR0_HIDE;
        shadowOAM[36].attr0 = ATTR0_HIDE;
        shadowOAM[58].attr0 = ATTR0_HIDE;
        enemy2.rdel = 0;
        enemy2.worldCol = 0;
    }
}
// Draw blue horizontal
void drawTwoEnemy3() {
   if (enemy3.active) {
        shadowOAM[38].attr0 = (ROWMASK & (enemy3.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[38].attr1 = (COLMASK & (enemy3.worldCol - hOff)) | ATTR1_SMALL;
        shadowOAM[38].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(29 - enemy3.cdel, 6 + enemy3.curFrame*2);

        shadowOAM[39].attr0 = (ROWMASK & (enemy3.worldRow - 5 - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[39].attr1 = (COLMASK & (enemy3.worldCol - hOff)) | ATTR1_TINY;
        shadowOAM[39].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(5, 31);
    } else {
        shadowOAM[38].attr0 = ATTR0_HIDE;
        shadowOAM[39].attr0 = ATTR0_HIDE;
        enemy3.cdel = 0;
        enemy3.worldCol = 0;        
    }
}
// Draw green horizontal
void drawTwoEnemy4() {
   if (enemy4.active) {
        shadowOAM[40].attr0 = (ROWMASK & (enemy4.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[40].attr1 = (COLMASK & (enemy4.worldCol - hOff)) | ATTR1_SMALL;
        shadowOAM[40].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(29 - enemy4.cdel, enemy4.curFrame*2);

        shadowOAM[41].attr0 = (ROWMASK & (enemy4.worldRow - 5 - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[41].attr1 = (COLMASK & (enemy4.worldCol - hOff)) | ATTR1_TINY;
        shadowOAM[41].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(9, 31);
    } else {
        shadowOAM[40].attr0 = ATTR0_HIDE;
        shadowOAM[41].attr0 = ATTR0_HIDE;
        enemy4.cdel = 0;
        enemy4.worldCol = 0;        
    }
}
// Draw blue vertical
void drawTwoEnemy5() {    
    if (enemy5.active) {
        shadowOAM[54].attr0 = (ROWMASK & (enemy5.worldRow - vOff)) | ATTR0_4BPP | ATTR0_TALL;
        shadowOAM[54].attr1 = (COLMASK & (enemy5.worldCol - hOff)) | ATTR1_MEDIUM;
        shadowOAM[54].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(25 - enemy5.rdel , 12 + enemy5.curFrame*4);

        shadowOAM[55].attr0 = (ROWMASK & (enemy5.worldRow - vOff - 8)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[55].attr1 = (COLMASK & (enemy5.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[55].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(1, 31);

        shadowOAM[56].attr0 = (ROWMASK & (enemy5.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[56].attr1 = (COLMASK & (enemy5.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[56].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(5, 31);
    } else {
        shadowOAM[54].attr0 = ATTR0_HIDE;
        shadowOAM[55].attr0 = ATTR0_HIDE;
        shadowOAM[56].attr0 = ATTR0_HIDE;
        enemy5.rdel = 0;
        enemy5.worldCol = 0;
    }
}
// draw brown hor
void drawTwoEnemy6() {
   if (enemy6.active) {
        shadowOAM[42].attr0 = (ROWMASK & (enemy6.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[42].attr1 = (COLMASK & (enemy6.worldCol - hOff)) | ATTR1_SMALL;
        shadowOAM[42].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(21 - enemy6.cdel, enemy6.curFrame*2);

        shadowOAM[43].attr0 = (ROWMASK & (enemy6.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[43].attr1 = (COLMASK & (enemy6.worldCol - 13 - hOff)) | ATTR1_TINY;
        shadowOAM[43].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(3, 31);

        shadowOAM[44].attr0 = (ROWMASK & (enemy6.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[44].attr1 = (COLMASK & (enemy6.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[44].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(5, 31);
    } else {
        shadowOAM[42].attr0 = ATTR0_HIDE;
        shadowOAM[43].attr0 = ATTR0_HIDE;
        shadowOAM[44].attr0 = ATTR0_HIDE;
        enemy6.cdel = 0;
        enemy6.worldCol = 0;        
    }    
}
// Draw blue hor
void drawTwoEnemy7() {
   if (enemy7.active) {
        shadowOAM[45].attr0 = (ROWMASK & (enemy7.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[45].attr1 = (COLMASK & (enemy7.worldCol - hOff)) | ATTR1_SMALL;
        shadowOAM[45].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(29 - enemy7.cdel, 6 + enemy7.curFrame*2);

        shadowOAM[46].attr0 = (ROWMASK & (enemy7.worldRow - 13 - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[46].attr1 = (COLMASK & (enemy7.worldCol - hOff)) | ATTR1_TINY;
        shadowOAM[46].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2, 31);

        shadowOAM[47].attr0 = (ROWMASK & (enemy7.worldRow - 5 - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[47].attr1 = (COLMASK & (enemy7.worldCol - hOff)) | ATTR1_TINY;
        shadowOAM[47].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(5, 31);
    } else {
        shadowOAM[45].attr0 = ATTR0_HIDE;
        shadowOAM[46].attr0 = ATTR0_HIDE;
        shadowOAM[47].attr0 = ATTR0_HIDE;
        enemy7.cdel = 0;
        enemy7.worldCol = 0;        
    }    
}
// Draw red ver
void drawTwoEnemy8() {    
    if (enemy8.active) {
        shadowOAM[48].attr0 = (ROWMASK & (enemy8.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[48].attr1 = (COLMASK & (enemy8.worldCol - hOff)) | ATTR1_SMALL;
        shadowOAM[48].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(9 - enemy8.rdel , enemy8.curFrame*4);

        shadowOAM[49].attr0 = (ROWMASK & (enemy8.worldRow - 8 - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[49].attr1 = (COLMASK & (enemy8.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[49].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(5, 31);

        shadowOAM[50].attr0 = (ROWMASK & (enemy8.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[50].attr1 = (COLMASK & (enemy8.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[50].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 31);
    } else {
        shadowOAM[48].attr0 = ATTR0_HIDE;
        shadowOAM[49].attr0 = ATTR0_HIDE;
        shadowOAM[50].attr0 = ATTR0_HIDE;
        enemy8.rdel = 0;
        enemy8.worldCol = 0;
    }
}
// Draw green ver
void drawTwoEnemy9() {    
    if (enemy9.active) {
        shadowOAM[51].attr0 = (ROWMASK & (enemy9.worldRow - vOff)) | ATTR0_4BPP | ATTR0_TALL;
        shadowOAM[51].attr1 = (COLMASK & (enemy9.worldCol - hOff)) | ATTR1_MEDIUM;
        shadowOAM[51].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(25 - enemy9.rdel , enemy9.curFrame*4);

        shadowOAM[52].attr0 = (ROWMASK & (enemy9.worldRow - 8 -vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[52].attr1 = (COLMASK & (enemy9.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[52].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(4, 31);

        shadowOAM[53].attr0 = (ROWMASK & (enemy9.worldRow - vOff)) | ATTR0_4BPP | ATTR0_SQUARE;
        shadowOAM[53].attr1 = (COLMASK & (enemy9.worldCol - 5 - hOff)) | ATTR1_TINY;
        shadowOAM[53].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 31);
    } else {
        shadowOAM[51].attr0 = ATTR0_HIDE;
        shadowOAM[52].attr0 = ATTR0_HIDE;
        shadowOAM[53].attr0 = ATTR0_HIDE;
        enemy9.rdel = 0;
        enemy9.worldCol = 0;
    }
}
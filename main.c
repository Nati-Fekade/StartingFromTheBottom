#include <stdlib.h>
#include <stdio.h>

#include "gba.h"
#include "text.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "fish.h"
#include "level_One.h"
#include "level_Two.h"
#include "overlayHealth.h"
#include "foreground.h"
#include "foreground2.h"
#include "general_BGD.h"
#include "instruction.h"
#include "transition.h"
#include "lose.h"
#include "win.h"
#include "pause.h"
#include "print.h"

#include "sound.h"

////////////AUDIO/////////////
#include "levelOneMusic.h"
#include "levelTwoMusic.h"
#include "loseSound.h"
#include "pauseMusic.h"
#include "screaming.h"
#include "startMusic.h"
#include "winSound.h"
/////////////////////////////

// Prototypes
void initialize();

void goToStart();
void start();
void goToInstruction();
void instruction();
void goToLevelOne();
void levelOne();
void goToTransition();
void transition();
void goToLevelTwo();
void levelTwo();
void goToPause();
void pause();
void goToWin();
void win();
void goToLose();
void lose();

// States
enum {START, INSTRUCTION, LEVEL_ONE, TRANSITION, LEVEL_TWO, PAUSE, WIN, LOSE};
int state;
int level;

// Button Variables
unsigned short buttons;
unsigned short oldButtons;

int main() {
    mgba_open();

    initialize();

    while(1) {
        // Update button variables
        oldButtons = buttons;
        buttons = BUTTONS;
        
        // State Machine
        switch(state) {
            case START:
                start();
                break;
            case INSTRUCTION:
                instruction();
                break;
            case LEVEL_ONE:
                levelOne();
                break;
            case TRANSITION:
                transition();
                break;
            case LEVEL_TWO:
                levelTwo();
                break;
            case PAUSE:
                pause();
                break;
            case WIN:
                win();
                break;
            case LOSE:
                lose();
                break;
        }          
    }
}

// Sets up GBA
void initialize() {
    // Set up the first state
    goToStart();

    setupInterrupts();
    setupSounds();
}

void goToStart() {
    REG_DISPCTL = MODE0 | BG2_ENABLE;

    playSoundA(startMusic_data, startMusic_length, 1);
    // setup main menu background
    REG_BG2CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_4BPP | BG_SIZE_SMALL;
    DMANow(3, general_BGDPal, PALETTE, general_BGDPalLen / 2);
    DMANow(3, general_BGDTiles, &CHARBLOCK[0], general_BGDTilesLen / 2);
    DMANow(3, general_BGDMap, &SCREENBLOCK[31], general_BGDMapLen / 2);

    state = START;
}

void start() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        initLevelOne();
        goToLevelOne();
        // initLevelTwo();
        // goToLevelTwo();
    }
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToInstruction();
    }
}

void goToInstruction() {
    REG_DISPCTL = MODE0 | BG2_ENABLE;

    // setup main menu background
    REG_BG2CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_4BPP | BG_SIZE_SMALL;
    DMANow(3, instructionPal, PALETTE, instructionPalLen / 2);
    DMANow(3, instructionTiles, &CHARBLOCK[0], instructionTilesLen / 2);
    DMANow(3, instructionMap, &SCREENBLOCK[31], instructionMapLen / 2);

    state = INSTRUCTION;
}

void instruction() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        initLevelOne();
        goToLevelOne();
    }
}

// Sets up the game state
void goToLevelOne() {
    level = 1;
    playSoundA(levelOneMusic_data, levelOneMusic_length, 1);
    // Set up the display
    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE | BG2_ENABLE | SPRITE_ENABLE;
    REG_BG1CNT = BG_CHARBLOCK(1) | BG_SCREENBLOCK(20) | BG_SIZE_SMALL| 1; // Foreground Screen 
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(15) | BG_SIZE_WIDE | 2; // Game Background Screen
    REG_BG2CNT = BG_CHARBLOCK(2) | BG_SCREENBLOCK(28) | BG_SIZE_SMALL; // Health Overlay Screen
    
    // Make sure changes do not appear onscreen
    waitForVBlank();

    // Set up the background
    DMANow(3, level_OnePal, PALETTE, 256);
    DMANow(3, level_OneTiles, &CHARBLOCK[0], level_OneTilesLen / 2);
    DMANow(3, level_OneMap, &SCREENBLOCK[15], level_OneMapLen / 2);

    REG_BG0VOFF = vOff;
    REG_BG0HOFF = hOff;
    
    // Set up the overlay
    DMANow(3, overlayHealthTiles, &CHARBLOCK[2], overlayHealthTilesLen / 2);
    DMANow(3, overlayHealthMap + 32, &SCREENBLOCK[28], overlayHealthMapLen / 2);

    // Set up the foreground
    DMANow(3, foregroundTiles, &CHARBLOCK[1], foregroundTilesLen / 2);
    DMANow(3, foregroundMap, &SCREENBLOCK[20], foregroundMapLen / 2);

    REG_BG1VOFF = vOff / 3;
    REG_BG1HOFF = hOff / 3;

    // Set up the sprites
    DMANow(3, fishTiles, &CHARBLOCK[4], fishTilesLen / 2);
    DMANow(3, fishPal, SPRITEPALETTE, fishPalLen / 2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128 * 4);

    state = LEVEL_ONE;
}

// Runs every frame of the game state
void levelOne() {
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        pauseSound();
        goToPause();
    }

    if (health == 0) {
        stopSound();
        goToLose();
    }

    if (enemyCount == 0) {
        stopSound();
        goToTransition();
    }

    updateLevelOne();
    drawLevelOne();
}

void goToTransition() {
    state = TRANSITION;
    playSoundA(startMusic_data, startMusic_length, 1);
    REG_DISPCTL = MODE0 | BG2_ENABLE;
    // Setup win background
    REG_BG2CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_4BPP | BG_SIZE_SMALL;
    DMANow(3, transitionPal, PALETTE, transitionPalLen / 2);
    DMANow(3, transitionTiles, &CHARBLOCK[0], transitionTilesLen / 2);
    DMANow(3, transitionMap, &SCREENBLOCK[31], transitionMapLen / 2);
}

void transition() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        initLevelTwo();
        goToLevelTwo();
    }
}


void goToLevelTwo() {
    level = 2;
    playSoundA(levelTwoMusic_data, levelTwoMusic_length, 1);
    // Set up the display
    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE | BG2_ENABLE | SPRITE_ENABLE;
    REG_BG0CNT = BG_CHARBLOCK(1) | BG_SCREENBLOCK(25) | BG_SIZE_SMALL; // Foreground Screen 
    REG_BG1CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(20) | BG_SIZE_WIDE | 1; // Game Background Screen
    REG_BG2CNT = BG_CHARBLOCK(2) | BG_SCREENBLOCK(28) | BG_SIZE_SMALL; // Health Overlay Screen
    
    // Make sure changes do not appear onscreen
    waitForVBlank();

    // Set up the background
    DMANow(3, level_TwoPal, PALETTE, 256);
    DMANow(3, level_TwoTiles, &CHARBLOCK[0], level_TwoTilesLen / 2);
    DMANow(3, level_TwoMap, &SCREENBLOCK[20], level_TwoMapLen / 2);

    REG_BG1VOFF = vOff;
    REG_BG1HOFF = hOff;
    
    // Set up the overlay
    DMANow(3, overlayHealthTiles, &CHARBLOCK[2], overlayHealthTilesLen / 2);
    DMANow(3, overlayHealthMap + 32, &SCREENBLOCK[28], overlayHealthMapLen / 2);

    // Set up the foreground
    DMANow(3, foreground2Tiles, &CHARBLOCK[1], foreground2TilesLen / 2);
    DMANow(3, foreground2Map, &SCREENBLOCK[25], foreground2MapLen / 2);

    REG_BG0HOFF = hOff / 3;
    REG_BG0VOFF = vOff / 3;

    // Set up the sprites
    DMANow(3, fishTiles, &CHARBLOCK[4], fishTilesLen / 2);
    DMANow(3, fishPal, SPRITEPALETTE, fishPalLen / 2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128 * 4);

    state = LEVEL_TWO;
}

void levelTwo() {
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        pauseSound();
        goToPause();
    }

    if (healthTwo == 0) {
        stopSound();
        goToLose();
    }

    if (enemyCountTwo == 0) {
        stopSound();
        goToWin();
    }

    updateLevelTwo();
    drawLevelTwo();
}

void goToPause() {
    state = PAUSE;
    playSoundA(pauseMusic_data, pauseMusic_length, 1);
    REG_DISPCTL = MODE0 | BG2_ENABLE;
    // Setup pause background
    REG_BG2CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_4BPP | BG_SIZE_SMALL;
    DMANow(3, pausePal, PALETTE, pausePalLen / 2);
    DMANow(3, pauseTiles, &CHARBLOCK[0], pauseTilesLen / 2);
    DMANow(3, pauseMap, &SCREENBLOCK[31], pauseMapLen / 2);
}

void pause() {
    if (BUTTON_PRESSED(BUTTON_SELECT) && level == 1) {
        pauseSound();
        goToLevelOne();
    }
    if (BUTTON_PRESSED(BUTTON_SELECT) && level == 2) {
        pauseSound();
        goToLevelTwo();
    }
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        goToStart();
    }
}

void goToWin() {
    state = WIN;
    playSoundA(winSound_data, winSound_length, 1);
    REG_DISPCTL = MODE0 | BG2_ENABLE;
    // Setup win background
    REG_BG2CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_4BPP | BG_SIZE_SMALL;
    DMANow(3, winPal, PALETTE, winPalLen / 2);
    DMANow(3, winTiles, &CHARBLOCK[0], winTilesLen / 2);
    DMANow(3, winMap, &SCREENBLOCK[31], winMapLen / 2);
}

void win() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        goToStart();
    }
}

void goToLose() {
    state = LOSE;
    playSoundA(loseSound_data, loseSound_length, 1);
    REG_DISPCTL = MODE0 | BG2_ENABLE;
    // Setup lose background
    REG_BG2CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(31) | BG_4BPP | BG_SIZE_SMALL;
    DMANow(3, losePal, PALETTE, losePalLen / 2);
    DMANow(3, loseTiles, &CHARBLOCK[0], loseTilesLen / 2);
    DMANow(3, loseMap, &SCREENBLOCK[31], loseMapLen / 2);
}

void lose() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSound();
        goToStart();
    }
}
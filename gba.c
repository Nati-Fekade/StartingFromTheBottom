#include "gba.h"

// The start of the video memory
unsigned volatile short *videoBuffer = (unsigned short *)0x6000000;


// ---- Miscellaneous Functions ----

void waitForVBlank() {
    while (SCANLINECOUNTER >= 160);
    while (SCANLINECOUNTER < 160);
}


// ---- Mode 3 ----

void setPixel3(int col, int row, unsigned short color) {
    videoBuffer[OFFSET(col, row, SCREENWIDTH)] = color;
}

void drawRect3(int col, int row, int width, int height, volatile unsigned short color) {
    for (int r = 0; r < height; r++) {
        DMANow(3, &color, &videoBuffer[OFFSET(col, row + r, SCREENWIDTH)], DMA_SOURCE_FIXED | width);
    }
}

void fillScreen3(volatile unsigned short color) {
    unsigned short c = color;
    DMANow(3, &c, videoBuffer, DMA_SOURCE_FIXED | (SCREENWIDTH * SCREENHEIGHT));
}

void drawImage3(int col, int row, int width, int height, const unsigned short *image) {
    for (int r = 0; r < height; r++) {
        DMANow(3, &image[OFFSET(0, r, width)], &videoBuffer[OFFSET(col, row + r, SCREENWIDTH)], width);
    }
}

void drawFullscreenImage3(const unsigned short *image) {
    DMANow(3, image, videoBuffer, SCREENWIDTH * SCREENHEIGHT);
}


// ---- Mode 4 ----

void drawImage4(int col, int row, int width, int height, const unsigned short *image) {
    for (int r = 0; r < height; r++) {
        DMANow(3, &image[OFFSET(0, r, width/2)], &videoBuffer[OFFSET(col, row+r, SCREENWIDTH)/2], DMA_SOURCE_INCREMENT | width/2);
    } 
}

void setPixel4(int col, int row, unsigned char colorIndex) {
    volatile unsigned short pixelData = videoBuffer[OFFSET(col,row, SCREENWIDTH)/2];
    if(col & 1) {
        pixelData &= 0x00FF;
        pixelData |= colorIndex<<8;
    } else {
         pixelData &= 0xFF00;
        pixelData |= colorIndex;
    }
    videoBuffer[OFFSET(col,row,SCREENWIDTH)/2] = pixelData;
}

void drawRect4(int col, int row, int width, int height, volatile unsigned char colorIndex) {
    volatile unsigned short pixelData = colorIndex | (colorIndex << 8);
    if (width == 1) {
        for(int r = 0; r < height; r++) {
            setPixel4(col, row+r, colorIndex);
        }
   } else if (width == 2) {
        for (int r = 0; r < height; r++) {
            setPixel4(col, row+r, colorIndex);
            setPixel4(col+1, row+r, colorIndex);
        }
   } else if ((col&1) && (width&1)) { // odd col, odd width
        for (int r = 0; r < height; r++) {
            setPixel4(col, row+r, colorIndex);
            if (width - 1 > 0) {
                DMANow(3, &pixelData, &videoBuffer[OFFSET(col+1, row+r, SCREENWIDTH)/2], DMA_SOURCE_FIXED | (width - 1)/2);
            }
        }
    } else if ((width&1)) { // even col, odd width
        for (int r = 0; r < height; r++) {
            if (width - 1 > 0) {
                DMANow(3, &pixelData, &videoBuffer[OFFSET(col, row+r, SCREENWIDTH)/2], DMA_SOURCE_FIXED | (width - 1)/2);
            }
            setPixel4(col+width-1, row+r, colorIndex);
        }
    } else if (col&1) { // odd col, even width
        for (int r = 0; r < height; r++) {
            setPixel4(col, row+r, colorIndex);
            if (width - 2 > 0) {
                DMANow(3, &pixelData, &videoBuffer[OFFSET(col+1, row+r, SCREENWIDTH)/2], DMA_SOURCE_FIXED | (width - 2)/2);
            }
            setPixel4(col+width-1, row+r, colorIndex);
        }
    } else { // even col, even width
        for (int r = 0; r < height; r++) {
            if (width > 0) {
                DMANow(3, &pixelData, &videoBuffer[OFFSET(col, row+r, SCREENWIDTH)/2], DMA_SOURCE_FIXED | width/2);
            }
        }
    }
}

void fillScreen4(volatile unsigned char colorIndex) {
    volatile unsigned int pixelData = colorIndex | (colorIndex << 8) | (colorIndex << 16) | (colorIndex << 24);
    DMANow(3, &pixelData, videoBuffer, DMA_SOURCE_FIXED | (SCREENWIDTH*SCREENHEIGHT/4) | DMA_32);
}

void drawFullscreenImage4(const unsigned short *image) {
    DMANow(3, image, videoBuffer, (SCREENWIDTH*SCREENHEIGHT/4) | DMA_32);
}

void flipPage() {
    if (REG_DISPCTL & DISP_BACKBUFFER) {
        videoBuffer = BACKBUFFER;
    } else {
        videoBuffer = FRONTBUFFER;
    }
    REG_DISPCTL ^= DISP_BACKBUFFER;
}


// ---- Sprites ----

// Hides all sprites in the shadowOAM
void hideSprites() {
    for(int i = 0; i < 128; i++){
        shadowOAM[i].attr0 = ATTR0_HIDE;
    }
}


// ---- DMA ----

// The start of DMA registers
DMA *dma = (DMA *)0x40000B0;

void DMANow(int channel, volatile const void *src, volatile void *dst, unsigned int cnt) {
    dma[channel].cnt = 0; // turn off the DMA
    // set the source and destination
    dma[channel].src = src;
    dma[channel].dst = dst;
    // set control and turn on DMA
    dma[channel].cnt = cnt | DMA_ON;
}


// ---- Collisions ----

// Return true if the two rectangular areas are overlapping
int collision(int colA, int rowA, int widthA, int heightA, int colB, int rowB, int widthB, int heightB) {
    return rowA <= rowB + heightB - 1 && rowA + heightA - 1 >= rowB && colA <= colB + widthB - 1 && colA + widthA - 1 >= colB;
}

// Return the collision map entry at (col, row) from the passed in collision map.
// Use the OFFSET macro with the passed in mapWidth for this!
int collisionCheck(unsigned char *collisionMap, int mapWidth, int col, int row) {
    // Replace this 0 with the correct entry of the collision map
    return collisionMap[OFFSET(col, row, mapWidth)];
}
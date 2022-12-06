#include <iostream>
#include "Mover.h"

void Mover::deslocation(int from, int to, int * moves) {

    // right = 1
    // up = 2
    // left = 3
    // down = 4

    int x = from / 8;
    int y = from % 8;
    int x2 = to / 8;
    int y2 = to % 8;
    int xDiff = x2 - x;
    int yDiff = y2 - y;
    
    if (xDiff == 0 && yDiff == 0) {
        return;
    }

    int i = 0;
    if (yDiff > 0) {
        if (xDiff > 0) {
            // move right up
            // move half right
            moves[i++] = 1;
            moves[i++] = TILE_SIZE/2;
            // full up
            moves[i++] = 2;
            moves[i++] = TILE_SIZE*yDiff;

            moves[i++] = 1; 
            moves[i++] = TILE_SIZE/2 + TILE_SIZE*(xDiff-1);
        } else if (xDiff < 0) {
            // move left up
            // move half left
            moves[i++] = 3;
            moves[i++] = TILE_SIZE/2;
            // full up
            moves[i++] = 2;
            moves[i++] = TILE_SIZE*yDiff;

            moves[i++] = 3; 
            moves[i++] = TILE_SIZE/2 + TILE_SIZE*(xDiff+1);
        } else {
            // move up
            moves[i++] = 1;
            moves[i++] = TILE_SIZE/2;

            moves[i++] = 2;
            moves[i++] = TILE_SIZE*yDiff;

            moves[i++] = 3;
            moves[i++] = TILE_SIZE/2;
        }
    } else if (yDiff < 0) {
        if (xDiff > 0){ 

            moves[i++] = 1;
            moves[i++] = TILE_SIZE/2;
            // full down
            moves[i++] = 4;
            moves[i++] = TILE_SIZE*yDiff;

            moves[i++] = 1; 
            moves[i++] = TILE_SIZE/2 + TILE_SIZE*(xDiff-1);
        } else if (xDiff < 0) {
            // move left up
            // move half left
            moves[i++] = 3;
            moves[i++] = TILE_SIZE/2;
            // full down
            moves[i++] = 4;
            moves[i++] = TILE_SIZE*yDiff;

            moves[i++] = 3; 
            moves[i++] = TILE_SIZE/2 + TILE_SIZE*(xDiff+1);
        } else {
            // move up
            moves[i++] = 1;
            moves[i++] = TILE_SIZE/2;

            moves[i++] = 4;
            moves[i++] = TILE_SIZE*yDiff;

            moves[i++] = 3;
            moves[i++] = TILE_SIZE/2;
        }
    } else {
        if (xDiff > 0) {
            // move right            
            moves[i++] = 1;
            moves[i++] = TILE_SIZE/2;

            moves[i++] = 2;
            moves[i++] = TILE_SIZE/2;

            moves[i++] = 1;
            moves[i++] = TILE_SIZE/2 + TILE_SIZE*(xDiff-1);

            moves[i++] = 4;
            moves[i++] = TILE_SIZE/2;

        } else if (xDiff < 0) {
            // move left
            moves[i++] = 3;
            moves[i++] = TILE_SIZE/2;

            moves[i++] = 2;
            moves[i++] = TILE_SIZE/2;

            moves[i++] = 3;
            moves[i++] = TILE_SIZE/2 + TILE_SIZE*(xDiff+1);

            moves[i++] = 4;
            moves[i++] = TILE_SIZE/2;

        } else {
            // move up
            moves[i++] = 1;
            moves[i++] = TILE_SIZE/2;

            moves[i++] = 2;
            moves[i++] = TILE_SIZE*yDiff;

            moves[i++] = 3;
            moves[i++] = TILE_SIZE/2;
        }
    }
}
   
void Mover::deslocationByCoordinates(int from, int to, int * moves) {

    int x = (from / 8)*TILE_SIZE;
    int y = (from % 8)*TILE_SIZE;
    int x2 = (to / 8)*TILE_SIZE;
    int y2 = (to % 8)*TILE_SIZE;
    int xDiff = (x2 - x)/TILE_SIZE;
    int yDiff = (y2 - y)/TILE_SIZE;
    
    if (xDiff == 0 && yDiff == 0) {
        return;
    }

    int i = 0;
    int currentX = x;
    int currentY = y;
    if (yDiff > 0) {
        if (xDiff > 0) {
            // move right up
            // move half right
            currentX += TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;
            // full up
            moves[i++] = currentX;
            currentY += (TILE_SIZE*yDiff - TILE_SIZE/2);
            moves[i++] = currentY;
            
            currentX += (TILE_SIZE/2 + TILE_SIZE*(xDiff-1));
            moves[i++] = currentX;
            moves[i++] = currentY;

            moves[i++] = currentX;
            currentY += TILE_SIZE/2;
            moves[i++] = currentY;
             
        } else if (xDiff < 0) {
            // move left up
            // move half left
            currentX -= TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;
            // full up
            moves[i++] = currentX;
            currentY += (TILE_SIZE*yDiff - TILE_SIZE/2);
            moves[i++] = currentY;

            currentX += TILE_SIZE/2 + TILE_SIZE*(xDiff+1);
            moves[i++] = currentX;
            moves[i++] = currentY;

            moves[i++] = currentX;
            currentY += TILE_SIZE/2;
            moves[i++] = currentY;

        } else {
            // move up
            currentX += TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;

            moves[i++] = currentX;
            currentY += TILE_SIZE*yDiff;
            moves[i++] = currentY;

            currentX -= TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;
        }
    } else if (yDiff < 0) {
        if (xDiff > 0){ 
            // move right down
            currentX += TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;
            // full down
            currentY += (TILE_SIZE*yDiff + TILE_SIZE/2);
            moves[i++] = currentX;
            moves[i++] = currentY;

            currentX += TILE_SIZE/2 + TILE_SIZE*(xDiff-1);
            moves[i++] = currentX; 
            moves[i++] = currentY;

            moves[i++] = currentX;
            currentY -= TILE_SIZE/2;
            moves[i++] = currentY;

        } else if (xDiff < 0) {
            // move left dowm
            // move half left
            currentX -= TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;
            // full down
            currentY += (TILE_SIZE*yDiff + TILE_SIZE/2);
            moves[i++] = currentX;
            moves[i++] = currentY;

            currentX += TILE_SIZE/2 + TILE_SIZE*(xDiff+1);
            moves[i++] = currentX; 
            moves[i++] = currentY;

            moves[i++] = currentX;
            currentY -= TILE_SIZE/2;
            moves[i++] = currentY;
        } else {
            // move down
            currentX += TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;

            currentY += TILE_SIZE*yDiff;
            moves[i++] = currentX;
            moves[i++] = currentY;

            currentX -= TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;
        }
    } else {
        if (xDiff > 0) {
            // move right
            currentY += TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;

            currentX += TILE_SIZE*(xDiff);
            moves[i++] = currentX;
            moves[i++] = currentY;

            currentY -= TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;

        } else if (xDiff < 0) {
            // move left
            currentY -= TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;

            currentX += TILE_SIZE*(xDiff);
            moves[i++] = currentX;
            moves[i++] = currentY;

            currentY += TILE_SIZE/2;
            moves[i++] = currentX;
            moves[i++] = currentY;
        }
    }
}

Mover * Mover::moverInstance = nullptr;
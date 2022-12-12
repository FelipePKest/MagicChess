#include "Mover.h"

#define GRAVEYARD 65

void Mover::deslocationByCoordinates(int from, int to) {

    
    int x = (from / 8)*TILE_SIZE;
    int y = (from % 8)*TILE_SIZE;
    int x2 = (to / 8)*TILE_SIZE;
    int y2 = (to % 8)*TILE_SIZE;
    int xDiff = (x2 - x)/TILE_SIZE;
    int yDiff = (y2 - y)/TILE_SIZE;
    
    int * moves = new int[10];
    
    if (xDiff == 0 && yDiff == 0) {
        return;
    }

    bool isPieceToRemove = true;    
    if (board->tiles[to]->getOccupiedBy() != nullptr) {
        isPieceToRemove = false;
        int oldX = x;
        int oldY = y;
        int oldX2 = x2;
        int oldY2 = y2;
        int oldXD = xDiff;
        int oldYD = yDiff;

        deslocationByCoordinates(to,GRAVEYARD);

        int * moves = new int[10];
        x = oldX;
        y = oldY;
        x2 = oldX2;
        y2 = oldY2;
        xDiff = oldXD;
        yDiff = oldYD;

    }

    int i = 0;
    int currentX = x;
    int currentY = y;

    moves[i++] = currentX;
    moves[i++] = currentY;
    
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

    int xCoordinate = moves[0];
    int yCoordinate = moves[1];
    bool inGraveyard = false;
    int j = 0;
    for (j = 0; j<10; j++) {

        if (xCoordinate > 70 && inGraveyard && isPieceToRemove) {
            break;
        } else if (xCoordinate < 0 || yCoordinate < 0 || xCoordinate > 75) {
            break;
        }

        if (j%2 == 0) {
            xCoordinate = moves[j];
        } else if (j%2 == 1) {
            yCoordinate = moves[j];
            serial->print(String(xCoordinate)+" "+String(yCoordinate)+" ");
            if (xCoordinate > 75) { inGraveyard = true;}
        }
    }

    serial->println("D");
}

Mover * Mover::moverInstance = nullptr;

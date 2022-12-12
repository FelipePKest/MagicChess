#include <iostream>
#include "Mover.h"

#define GRAVEYARD 65

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
    
    if (board->tiles[to]->getOccupiedBy() != NULL) {
        int * firstMoves = (int *) malloc(sizeof(int)*10);
        std::cout << "HAS PIECE" << std::endl;
        deslocationByCoordinates(to,GRAVEYARD,firstMoves);
    } else { 
        std::cout << "DONT HAVE PIECE" << std::endl;
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

    int xCoordinate;
    int yCoordinate;
    for (int i = 0; i<10; i++) {
        if (xCoordinate > 70) {
            break;
        }
        if (i%2 == 0) {
            xCoordinate = moves[i];
            std::cout << "Coord X: " << std::endl;
        } else if (i%2 == 1) {
            std::cout << "Coord Y: " << std::endl;
            yCoordinate = moves[i];
            std::cout << "Move coordinates: " << xCoordinate << " " << yCoordinate << std::endl;
        }
    }

    std::cout << "D" << std::endl;

}

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
    if (board->tiles[to]->getOccupiedBy() != NULL) {
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
    int yCoordinate;
    bool inGraveyard = false;
    int j = 0;
    for (j = 0; j<10; j++) {

        if (xCoordinate > 70 && inGraveyard && isPieceToRemove) {
            break;
        } else if (xCoordinate > 75) {
            break;
        }

        if (j%2 == 0) {
            xCoordinate = moves[j];
        } else if (j%2 == 1) {
            yCoordinate = moves[j];
            std::cout << xCoordinate << " " << yCoordinate << " ";
            if (xCoordinate > 75) { inGraveyard = true;}
        }
    }

    std::cout << "D" << std::endl;
}

Mover * Mover::moverInstance = nullptr;
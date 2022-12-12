#include <iostream>
#include "Board.h"
#include "MoveManager.h"
#include "Piece.h"
#include "Mover.h"

int main() {
    Board* board = Board::GetBoardInstance();
    board->mockRookBoard();
    
    Mover * mover = Mover::GetMoverInstance();
    int moves[10];
    mover->deslocationByCoordinates(9, 11);

    int direction;
    int xCoordinate;
    int yCoordinate;
    for (int i = 0; i<10; i++) {
        if (xCoordinate > 280) {
            break;
        }
        if (i%2 == 0) {
            xCoordinate = moves[i];
        } else {
            yCoordinate = moves[i];
            std::cout << "Move coordinates: " << xCoordinate << " " << yCoordinate << std::endl;
        }
    }
    return 0;
}
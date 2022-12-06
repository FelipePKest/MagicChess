#include <iostream>
#include "Board.h"
#include "MoveManager.h"
#include "Piece.h"
#include "Mover.h"

int main() {
    Board* board = Board::GetBoardInstance();
    board->mockUpgradePawnBoard();
    board->printBoard();
    
    Mover * mover = Mover::GetMoverInstance();
    int moves[64];
    mover->deslocation(8, 16, moves);

    int direction = moves[0];
    for (int i = 0; i<64; i++) {
        if (moves[i] < 1) {
            break;
        }
        std::cout << moves[i] << std::endl;
    }

    return 0;
}
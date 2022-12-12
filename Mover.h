#include "Board.h"

class Mover {

public:
    void deslocation(int from, int to, int * moves);

    void deslocationByCoordinates(int from, int to, int * moves);

    void deslocationByCoordinates(int from, int to);

    static Mover* GetMoverInstance() {

        if (moverInstance == nullptr) {
            moverInstance = new Mover();
        }
        
        return moverInstance;
    }

private:
    Board * board;
    const int TILE_SIZE = 10;

    static Mover * moverInstance;
    Mover() {
        board = Board::GetBoardInstance();
    }


};

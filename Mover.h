#include <Stream.h>
#include "Board.h"

class Mover {

public:

    Stream * serial;
    
    void deslocation(int from, int to, int * moves);

    void deslocationByCoordinates(int from, int to, int * moves);

    void deslocationByCoordinates(int from, int to);

    static Mover* GetMoverInstance(Stream * serial) {

        if (moverInstance == nullptr) {
            moverInstance = new Mover(serial);
        }
        return moverInstance;
    }

private:
    Board * board;
    const int TILE_SIZE = 10;
    
    static Mover * moverInstance;
    
    Mover(Stream * serial) {
        board = Board::GetBoardInstance();
        this->serial = serial;
    }


};

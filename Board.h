#pragma once
#include "Piece.h"
#include "Tile.h"

class Board {

public:

	Tile * tiles[64];

	static Board* boardInstance;
	
	void setTiles();

	void movePiece(int from, int to);
	
	Board() {
		setTiles();
	};

	static Board * GetBoardInstance() {
		if (boardInstance == nullptr) {
			boardInstance = new Board();
			boardInstance->setTiles();
		}
		return boardInstance;
	};

	void mockRookBoard();

	void mockUpgradePawnBoard();
};

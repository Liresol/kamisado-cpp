#include "Piece.hpp"
#include "Board.hpp"

class Game {
	Board GameB;
	bool blackTurn;
	int scoreW;
	int scoreB;

	public:
	Game() {
		blackTurn = true;
		scoreW = 0;
		scoreB = 0;
	}

	void resetBoard() {
	}


};

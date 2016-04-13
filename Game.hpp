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

	Game(Board,turnV) {
		GameB = Board;
		blackTurn = turnV;
		scoreW = 0;
		scoreB = 0;
	}

	void setScore() {
		int bufW = 0;
		int bufB = 0;
		for(int i=0;i<8;i++) {
			bufW += WPieces[i].score();
			bufB += BPieces[i].score();
		}
		scoreW = bufW;
		scoreB = bufB;
	}

	void resetBoard() {
	}


};

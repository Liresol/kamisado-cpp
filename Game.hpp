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

	Game(Board BoardV, bool turnV) {
		GameB = BoardV;
		blackTurn = turnV;
		scoreW = 0;
		scoreB = 0;
	}

	void setScore() {
		int bufW = 0;
		int bufB = 0;
		for(int i=0;i<8;i++) {
			bufW += GameB.WPieces[i].score();
			bufB += GameB.BPieces[i].score();
		}
		scoreW = bufW;
		scoreB = bufB;
	}

	void resetBoard() {
	}


};

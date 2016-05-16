#include "Board.hpp"
#include <array>


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

	Board getBoard() {
		return GameB;
	}

	void setScore() {
		int bufW = 0;
		int bufB = 0;
		for(int i=0;i<8;i++) {
			bufW += GameB.mapPiece(i+8).score();
			bufB += GameB.mapPiece(i).score();
		}
		scoreW = bufW;
		scoreB = bufB;
	}

	//INCOMPLETE
	bool deadlocked() {
		return false;
	}

	//INCOMPLETE
	void resetBoard(bool Left) {
		if(Left) {fillLeft();}
		else {fillRight();}
	}

	//INCOMPLETE
	void fillLeft() {
		color WBuf[8];
		color BBuf[8];
		int buf=0;
		for(int y=0;y<8;y++) {
			for(int x=0;x<8;x++) {
				if(GameB.occupied(x,y) && GameB.occPiece(x,y).isBlack()) {
					BBuf[buf] = GameB.occPiece(x,y).getColor();
					buf += 1;
						}
			}
		}
		for(int y=7;y>=0;y--) {
			for(int x=7;x>=0;x--) {
				if(GameB.occupied(x,y) && !GameB.occPiece(x,y).isBlack()) {
					WBuf[buf] = GameB.occPiece(x,y).getColor();
					buf += 1;
						}
			}
		}
		GameB = Board();
	}
	
	//INCOMPLETE
	void fillRight() {
		Piece WBuf[8];
		Piece BBuf[8];
		int buf=0;
		for(int y=0;y<8;y++) {
			for(int x=0;x<8;x++) {
				if(GameB.occupied(x,y) && GameB.occPiece(x,y).isBlack()) {
					BBuf[buf] = GameB.occPiece(x,y);
					buf += 1;
						}
			}
		}
		for(int y=7;y>=0;y--) {
			for(int x=0;x<8;x--) {
				if(GameB.occupied(x,y) && !GameB.occPiece(x,y).isBlack()) {
					WBuf[buf] = GameB.occPiece(x,y);
					buf += 1;
						}
			}
		}

	}

	void resetGame() {
		GameB = Board();
		scoreB = scoreW = 0;
		blackTurn = true;
	}


	//INCOMPLETE
	void turn() {
	}


};

#include "Board.hpp"
#include <string>
#define FROM_LEFT true
#define FROM_RIGHT false
#define BLACK_TURN true
#define WHITE_TURN false

namespace kamisadoCPP
{

//Because the Game class is a synthesis of previous classes (and thus much more messy below the surface), functions not explicitly tested will be labeled.

class Game {
	Board GameB;
	bool blackTurn;
	int scoreW;
	int scoreB;
	id BMove;
	id WMove;

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

	id currentMover() {
		if(blackTurn) {
			return BMove;
		}
		else {return WMove;}
	}

	//UNTESTED
	bool deadlockCheck() {
		id Locked[16];
		for(int i=0;i<16;i+=1) {
			if(GameB.locked(currentMover())){
				Locked[i] = currentMover();
				for(int j=0;j<i;j+=1) {
					if(Locked[j] == Locked[i]) {return true;}
				}
				turnSwitch();
			}
			else {return false;}
		}

		return false;
	}

	//UNTESTED
	void assignMove(color c, bool EndingTurn) {
		id buf; buf = ID(c,EndingTurn);
		color endC = GameB.colorIn(buf);
		if(EndingTurn == BLACK_TURN) {
			WMove = ID(endC, WHITE_TURN);
		}
		else {
			BMove = ID(endC, BLACK_TURN);
		}
	}

	//UNTESTED
	void turnSwitch() {
		assignMove(GameB.colorIn(BMove),blackTurn);
		blackTurn = !blackTurn;
	}

	void resetBoard(bool Left) {
		if(Left) {fillLeft();}
		else {fillRight();}
	}

	//UNTESTED
	//Fills from left to right.
	void fillLeft() {
		id WBuf[8];
		id BBuf[8];
		int buf=0;
		for(int y=1;y<=8;y++) {
			for(int x=1;x<=8;x++) {
				if(GameB.occupied(x,y) && GameB.occPiece(x,y).isBlack()) {
					WBuf[buf] = GameB.occID(x,y);
					buf += 1;
						}
			}
		}
		buf = 0;
		for(int y=8;y>0;y--) {
			for(int x=8;x>0;x--) {
				if(GameB.occupied(x,y) && !GameB.occPiece(x,y).isBlack()) {
					BBuf[buf] = GameB.occID(x,y);
					buf += 1;
						}
			}
		}
		GameB = Board();
		for(int i=0;i<8;i+=1) {
			GameB.swap(WBuf[i],1,i+1);
			GameB.swap(BBuf[i],8,8-i);
		}
	}
	
	//UNTESTED
	//Fills from right to left.
	void fillRight() {
		id WBuf[8];
		id BBuf[8];
		int buf=0;
		for(int y=1;y<=8;y++) {
			for(int x=8;x<=1;x--) {
				if(GameB.occupied(x,y) && GameB.occPiece(x,y).isBlack()) {
					WBuf[buf] = GameB.occID(x,y);
					buf += 1;
						}
			}
		}
		buf = 0;
		for(int y=8;y>0;y--) {
			for(int x=1;x<8;x++) {
				if(GameB.occupied(x,y) && !GameB.occPiece(x,y).isBlack()) {
					BBuf[buf] = GameB.occID(x,y);
					buf += 1;
						}
			}
		}
		GameB = Board();
		for(int i=0;i<8;i+=1) {
			GameB.swap(WBuf[i],1,i+1);
			GameB.swap(BBuf[i],8,8-i);
		}
		}

	void resetGame() {
		GameB = Board();
		scoreB = scoreW = 0;
		blackTurn = true;
	}

	bool winnerCheck(int threshold) {
		setScore();
		if(scoreB >= threshold) {
			return true;
		}
		else if(scoreW >= threshold) {
			return true;
		}
		return false;
	}

};


};

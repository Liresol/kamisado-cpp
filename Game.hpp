#include "Board.hpp"
#include <string>
#define FILL_LEFT true
#define FILL_RIGHT false
#define BLACK_TURN true
#define WHITE_TURN false

namespace kamisadoCPP
{

//Because the Game class is a synthesis of previous classes (and thus much more messy below the surface), functions not explicitly tested will be labeled.

class Game {
	protected:
	Board GameB;
	bool blackTurn;
	int scoreW;
	int scoreB;
	id BMove;
	id WMove;
	unsigned int winThreshold;

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
		winThreshold = 1;
	}

	Game(Board BoardV, bool turnV, int winT) {
		GameB = BoardV;
		blackTurn = turnV;
		scoreW = 0;
		scoreB = 0;
		winThreshold = winT;
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
	//Promotes the last deadlocked piece in expectation of a board reset.
	bool deadlockCheck() {
		id Locked[16];
		for(int i=0;i<16;i+=1) {
			if(GameB.locked(currentMover())){
				Locked[i] = currentMover();
				for(int j=0;j<i;j+=1) {
					if(Locked[j] == Locked[i]) {GameB.promotePiece(Locked[i-1]); return true;}
				}
				turnSwitch();
			}
			else {return false;}
		}

		return false;
	}

	//UNTESTED
	id lastNonDeadlocked() {
		if(!deadlockCheck()) {return NA;}
	id Locked[16];
		for(int i=0;i<16;i+=1) {
			if(GameB.locked(currentMover())){
				Locked[i] = currentMover();
				for(int j=0;j<i;j+=1) {
					if(Locked[j] == Locked[i]) {return Locked[i-1];}
				}
				turnSwitch();
			}
			else {return NA;}
		}

		return NA;
	

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

	void fillBoard(bool Left) {
		if(Left) {fillLeft();}
		else {fillRight();}
	}

	//INCOMPLETE
	void newRound(bool FillLeft) {
		int BS[8];
		int WS[8];
		for(int x=1;x<=8;x+=1) {
			for(int y=1;y<=8;y+=1) {
				if(GameB.occInt(x,y) >= 8) {
					WS[GameB.occInt(x,y)] = GameB.occPiece(x,y).getSumo();
				}
				if(isBetweenInc(GameB.occInt(x,y),0,7)) {
					BS[GameB.occInt(x,y)] = GameB.occPiece(x,y).getSumo();
				}
			}
		}
		fillBoard(FillLeft);
		for(int i=0;i<8;i+=1) {
			for(int j=0;j<BS[i];j+=1) {
				GameB.promotePiece(i);
			}
			for(int j=0;j<WS[i];j+=1) {
				GameB.promotePiece(i+8);
			}
		}
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

	bool winnerCheck() {
		return winnerCheck(winThreshold);
	}

	//UNTESTED
	int determineWinner() {
		if(!winnerCheck(winThreshold)) {return 0;}
		if(scoreB >= winThreshold) {return 1;}
		if(scoreW >= winThreshold) {return 2;}
		else {return 0;}
	}

};


};

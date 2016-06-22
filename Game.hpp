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

	Piece moverPiece() {
		return GameB.MapID(currentMover());
	}

	//UNTESTED
	//Promotes the last deadlocked piece in expectation of a board reset.
	bool deadlockCheck() {
		id Locked[16];
		for(int i=0;i<16;i+=1) {
			if(GameB.locked(currentMover())){
				Locked[i] = currentMover();
				for(int j=0;j<i;j+=1) {
					if(Locked[j] == Locked[i]) {GameB.promotePiece(Locked[i-1]); 
						return true;}
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
		assignMove(GameB.colorIn(currentMover()),blackTurn);
		blackTurn = !blackTurn;
	}

	void fillBoard(bool Left) {
		if(Left) {fillLeft();}
		else {fillRight();}
	}

	void newRound(bool FillLeft) {
		int S[16];
		for(int i=0;i<16;i+=1) {
			S[i] = 0;
		}
		for(int x=1;x<=8;x+=1) {
			for(int y=1;y<=8;y+=1) {
				if(GameB.occInt(x,y) >= 0) {S[GameB.occInt(x,y)] = GameB.occPiece(x,y).getSumo();}
			}
		}
		/*
		for(int i=0;i<16;i+=1) {
			std::cout << S[i] << std::endl;
		}
		*/
		fillBoard(FillLeft);
		for(int i=0;i<16;i+=1) {
			for(int j=0;j<S[i];j+=1) {
				GameB.promotePiece(i);
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
				if(GameB.occupied(x,y) && GameB.occPiece(x,y).isWhite()) {
					WBuf[buf] = GameB.occID(x,y);
					printID(WBuf[buf]);
					buf += 1;
						}
			}
		}
		buf = 0;
		for(int y=8;y>0;y--) {
			for(int x=8;x>0;x--) {
				if(GameB.occupied(x,y) && GameB.occPiece(x,y).isBlack()) {
					BBuf[buf] = GameB.occID(x,y);
					buf += 1;
						}
			}
		}
		GameB = Board();
		for(int i=0;i<8;i+=1) {
			GameB.uWarp(WBuf[i], i+1, 2);
			GameB.uWarp(BBuf[i], 8-i, 7);
		}
		for(int i=0;i<8;i+=1) {
			GameB.uWarp(WBuf[i], i+1, 1);
			GameB.uWarp(BBuf[i], 8-i, 8);
		}
	}
	
	//UNTESTED
	//Fills from right to left.
	void fillRight() {
		std::cout << "PRINTING RIGHT" << std::endl;
		std::cout << "PRINTING RIGHT" << std::endl;
		std::cout << "PRINTING RIGHT" << std::endl;
		std::cout << "PRINTING RIGHT" << std::endl;
		std::cout << "PRINTING RIGHT" << std::endl;
		std::cout << "PRINTING RIGHT" << std::endl;
		id WBuf[8];
		id BBuf[8];
		int buf=0;
		for(int y=1;y<=8;y++) {
			for(int x=8;x>0;x--) {
				if(GameB.occupied(x,y) && GameB.occPiece(x,y).isWhite()) {
					WBuf[buf] = GameB.occID(x,y);
					buf += 1;
				}
			}
		}
		buf = 0;
		for(int y=8;y>0;y--) {
			for(int x=1;x<=8;x++) {
				if(GameB.occupied(x,y) && GameB.occPiece(x,y).isBlack()) {
					BBuf[buf] = GameB.occID(x,y);
					buf += 1;
						}
			}
		}
		GameB = Board();
		for(int i=0;i<8;i+=1) {
			GameB.uWarp(WBuf[i], i+1, 2);
			GameB.uWarp(BBuf[i], 8-i, 7);
		}
		for(int i=0;i<8;i+=1) {
			GameB.uWarp(WBuf[i], i+1, 1);
			GameB.uWarp(BBuf[i], 8-i, 8);
		}
		}

	void resetGame() {
		GameB = Board();
		scoreB = scoreW = 0;
		blackTurn = true;
	}

	//1 if Black, 2 if White, 0 if none
	int roundWinner() {
		if(GameB.whiteWin()) {return 2;}
		if(GameB.blackWin()) {return 1;}
		else {return 0;}
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

	int determineWinner() {
		if(!winnerCheck(winThreshold)) {return 0;}
		if(scoreB >= winThreshold) {return 1;}
		if(scoreW >= winThreshold) {return 2;}
		else {return 0;}
	}
	void printBoard() {
		GameB.printOut();
	}
	/*Piece occPiece(int x,int y) {
		return GameB.occPiece(x,y);
	}
	
	int occInt(int x, int y) {
		return GameB.occInt(x,y);
	}
	id occID(int x, int y) {
		return GameB.occID(x,y);
	}
	bool occupied(int x, int y) {
		return GameB.occupied(x,y);
	}*/

};


};

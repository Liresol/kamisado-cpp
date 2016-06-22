#include "Game.hpp"
#include <sstream>


//This is a very messy and simple way of utilizing the Board class. 
//After playing, this is actually just an exercise for keeping a board state in your head.
//Have a picture of the board colors at hand.

namespace kamisadoCPP
{
class BasicGame: private Game {

	void declareTurn() {
		if(blackTurn) {
			std::cout << "It is now Black's turn." << std::endl;
		}
		else {
			std::cout << "It is now White's turn." << std::endl;
		}
	}

	void declareMover() {
		moverPiece().printOut();
	}

	void declareWinner() {
		if(determineWinner() == 1) {std::cout << "Winner: Black" << std::endl;}
		else if(determineWinner() == 2) {std::cout << "Winner: White" << std::endl;}
		else {
			std::cout << "Winner has yet to be determined" << std::endl;
		}
	}
	public:

	void freshTurn(bool Challenger) {
		std::string buf;
		bool done = false;
		int intID;

		while(!done) {
		if(Challenger == BLACK) {
			std::cout << "Piece" << std::endl;
			std::cout << "Use the following (very confusing) conversion: Brown is 0, Green is 1, Red is 2, Yellow is 3, Pink is 4, Purple is 5, Blue is 6, and Orange is 7." << std::endl;
			getline(std::cin, buf);
			std::stringstream(buf) >> intID;
			BMove = integerToID(intID);
		std::cout << BMove << std::endl;
			if(IDIsBlack(BMove)) {
			done = true;
			}
			else {
				std::cout << "Invalid Piece" << std::endl;
			}

		}
		else {
			std::cout << "Piece" << std::endl;
			std::cout << "Use the following (very confusing) conversion: Brown is 8, Green is 9, Red is 10, Yellow is 11, Pink is 12, Purple is 13, Blue is 14, and Orange is 15." << std::endl;
			getline(std::cin, buf);
			std::stringstream(buf) >> intID;
			WMove = integerToID(intID);
		std::cout << WMove << std::endl;
			if(IDIsWhite(WMove)) {
			done = true;
			}
			else {
				std::cout << "Invalid Piece" << std::endl;
			}



		}
		}
	}

	void firstTurn() {
		bool doneW = false;
		bool doneP = false;
		std::string buf;
		int intID;
		int x;
		int y;
		blackTurn = BLACK_TURN;
		setScore();

		while(!doneW) {
		std::cout << "Win Threshold" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> winThreshold;
		if(winThreshold > 0 && winThreshold < 120) {doneW = true;}
		else {std::cout << "Invalid response for win threshold" << std::endl;}
		if(winThreshold >= 15 && winThreshold < 120) {std::cout << "Nice job. This game is going to be very long." << std::endl;}
		}

		while (!doneP) {
		std::cout << "Piece" << std::endl;
		std::cout << "Use the following (very confusing) conversion: Brown is 0, Green is 1, Red is 2, Yellow is 3, Pink is 4, Purple is 5, Blue is 6, and Orange is 7." << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> intID;
		BMove = integerToID(intID);
		std::cout << BMove << std::endl;
		if(IDIsBlack(BMove)) {
			doneP = true;
		}
		else{
			std::cout << "Invalid Piece" << std::endl;
		}

		}

		turn();
	}

	//UNTESTED
	void turn() {
		bool done1 = false;
		bool done2 = false;
		int req;
		std::string buf;
		//std::string debug;
		while (!done1) {
		int x;
		int y;
		std::cout << "x" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> x;

		std::cout << "y" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> y;
		if(GameB.canTakeTurn(currentMover(),x,y)) {
			GameB.move(currentMover(),x,y);
			done1 = true;
		}
		else {std::cout << "Move cannot be made." << std::endl;}
		}
		deadlockCheck();
		std::cout << "Spitting out the current board state." << std::endl;
		GameB.printOut();
		turnSwitch();

		if(GameB.blackWin() || GameB.whiteWin() || deadlockCheck()) {
			if(winnerCheck(winThreshold)) {
				declareWinner();
			}
			while(!done2) {
				bool debug = GameB.blackWin();
				if(winnerCheck()) {break;}
				std::cout << "Fill Left? (1/0)" << std::endl;
				getline(std::cin, buf);
				std::stringstream(buf) >> req;
				std::cout << req << std::endl;
				if(GameB.blackWin()){
					freshTurn(WHITE);
				}
				else {
					freshTurn(BLACK);
				}
				//debug = std::stringstream(buf);
				//std::cout << req << std::endl;
				//std::cout << debug << std::endl;
				if(req == 1) {newRound(FILL_LEFT); done2 = true;
		std::cout << "Spitting out the current board state." << std::endl;
		GameB.printOut();
				}
				else if(req == 0) {newRound(FILL_RIGHT); done2 = true;
		std::cout << "Spitting out the current board state." << std::endl;
		GameB.printOut();
				}
				else {
					std::cout << "Bruh" << std::endl;
				}
			}
		}
		if(!winnerCheck()){
		declareTurn();
		declareMover();
		}

	}

	void play() {
		bool won = false;
		firstTurn();
		while(!won) {
			turn();
			if(winnerCheck()) {won = true;}
		}
		std::cout << "The game has finished." << std::endl;
	}
};
}

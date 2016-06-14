#include "Game.hpp"
#include <sstream>

namespace kamisadoCPP
{
class BasicGame: private Game {
	void declareWinner() {
		if(determineWinner() == 1) {std::cout << "Winner: Black" << std::endl;}
		if(determineWinner() == 2) {std::cout << "Winner: White" << std::endl;}
		else {
			std::cout << "Winner has yet to be determined" << std::endl;
		}
	}
	public:

	//UNTESTED
	void firstTurn() {
		bool doneW = false;
		bool doneP = false;
		std::string buf;
		int x;
		int y;
		blackTurn = BLACK_TURN;
		setScore();

		while(!doneW) {
		std::cout << "Win Threshold" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> winThreshold;
		if(winThreshold >= 0 && winThreshold < 120) {doneW = true;}
		else {std::cout << "Invalid response for win threshold" << std::endl;}
		if(winThreshold >= 15 && winThreshold < 120) {std::cout << "Nice job. This game is going to be very long." << std::endl;}
		}

		//CAN BE WHITE PIECE, BE CAREFUL
		while (!doneP) {
		std::cout << "Piece" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> BMove;
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
		char req;
		while (!done1) {
		std::string buf;
		int x;
		int y;
		std::cout << "x" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> x;

		std::cout << "y" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> y;
		if(GameB.canTakeTurn(BMove,x,y)) {
			GameB.move(BMove,x,y);
			done1 = true;
		}
		else {std::cout << "Move cannot be made." << std::endl;}
		deadlockCheck();
		turnSwitch();
		if(GameB.blackWin() || GameB.whiteWin()) {
			GameB.roundCheck();
			if(winnerCheck(winThreshold)) {
				declareWinner();
			}
			while(!done2) {
				std::cout << "Fill Left? (y/n)" << std::endl;
				getline(std::cin, buf);
				req = std::stringstream(buf);
				if(req == 'y') {newRound(FILL_LEFT); done2 = true;}
				if(req == 'n') {newRound(FILL_RIGHT); done2 = true;}
				else {
					std::cout << "Bruh" << std::endl;
					std::cout << req << std::endl;
				}
			}
		}
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

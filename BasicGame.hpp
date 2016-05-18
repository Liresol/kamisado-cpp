#include "Game.hpp"
#include <sstream>

//namespace kamisadoCPP
//{
class BasicGame: protected Game {
	public:

	//UNTESTED
	void firstTurn() {
		std::string buf;
		int x;
		int y;
		blackTurn = BLACK_TURN;
		setScore();
		std::cout << "Piece" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> BMove;

		std::cout << "x" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> x;

		std::cout << "y" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> y;
		if(GameB.canTakeTurn(BMove,x,y)) {
			GameB.move(BMove,x,y);
		}
		deadlockCheck();
		turnSwitch();
		winnerCheck();
	}
	//UNTESTED
	void turn() {
		std::string buf;
		int x;
		int y;
		std::cout << "x" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> x;

		std::cout << "y" << std::endl;
		getline(std::cin, buf);
		std::stringstream(buf) >> y;
	}

	void play() {
	}
}
//}

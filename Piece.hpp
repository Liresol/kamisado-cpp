#include <iostream>
#define BLACK true
#define WHITE false

namespace kamisadoCPP
{

enum color {
	brown, green, red, yellow, pink, purple, blue, orange, none
};

//Maps colors onto integers.
color cConvert(int i) {
	if(i == 0) {return brown;}
	else if(i == 1) {return green;}
	else if(i == 2) {return red;}
	else if(i == 3) {return yellow;}
	else if(i == 4) {return pink;}
	else if(i == 5) {return purple;}
	else if(i == 6) {return blue;}
	else if(i == 7) {return orange;}
	else {return none;}
}

//Maps integers onto colors.
int invConvert(color C) {
	if(C == brown) {return 0;}
	else if(C == green) {return 1;}
	else if(C == red) {return 2;}
	else if(C == yellow) {return 3;}
	else if(C == pink) {return 4;}
	else if(C == purple) {return 5;}
	else if(C == blue) {return 6;}
	else if(C == orange) {return 7;}
	else {return -1;}
}

//Defines each piece that will be used in the board.
class Piece {
	//Position is a matrix with 2 entries, which are effectively the x and y positions. White is on the bottom (low y) and Black is on the top (high y).
	int pos[2];
	int sumo;
	bool Black;
	color col;
	int moveRange;

	public:
	//Constructs a dummy Piece.
	Piece() {
		pos[0] = -1;
		pos[1] = -1;
		sumo = 0;
		col = none;
		Black = true;
		setMoveRange();
	}

	Piece(bool black, int h, int v, int sumoval, color colval) {
		pos[0] = h;
		pos[1] = v;
		sumo = sumoval;
		col = colval;
		Black = black;
		setMoveRange();
	}
	Piece(bool black, int sumoval, color colval) {
		Black = black;
		sumo = sumoval;
		col = colval;
		if(Black) {
			pos[1] = 8;
			if(colval == brown) {pos[0] = 8;}
			else if(colval == green) {pos[0] = 7;}
			else if(colval == red) {pos[0] = 6;}
			else if(colval == yellow) {pos[0] = 5;}
			else if(colval == pink) {pos[0] = 4;}
			else if(colval == purple) {pos[0] = 3;}
			else if(colval == blue) {pos[0] = 2;}
			else if(colval == orange) {pos[0] = 1;}
		}
		else {
			pos[1] = 1;
			if(colval == brown) {pos[0] = 1;}
			else if(colval == green) {pos[0] = 2;}
			else if(colval == red) {pos[0] = 3;}
			else if(colval == yellow) {pos[0] = 4;}
			else if(colval == pink) {pos[0] = 5;}
			else if(colval == purple) {pos[0] = 6;}
			else if(colval == blue) {pos[0] = 7;}
			else if(colval == orange) {pos[0] = 8;}
			else {pos[0] = -1;}
		}
		setMoveRange();
	}

	//Defines the assignment operator.
	Piece operator= (const Piece copyFrom) {
		pos[0] = copyFrom.pos[0];
		pos[1] = copyFrom.pos[1];
		sumo = copyFrom.sumo;
		Black = copyFrom.Black;
		col = copyFrom.col;
		moveRange = copyFrom.moveRange;
		return *this;

	}

	//Given no other pieces on the board, finds whether a move is possible.
	bool isMovePossible(int a, int b) {
		int bufh = pos[0];
		int bufv = pos[1];
		if(bufh == a && bufv == b) {return false;}
		if(Black) {
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufh--;
				bufv--;
				if(bufh == a && bufv == b) {return true;}
			}
			bufh = pos[0];
			bufv = pos[1];
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufv--;
				if(bufh == a && bufv == b) {return true;}
			}
			bufh = pos[0];
			bufv = pos[1];
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufh++;
				bufv--;
				if(bufh == a && bufv == b) {return true;}
			}
			return false;
		}
		else {
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufh++;
				bufv++;
				if(bufh == a && bufv == b) {return true;}
			}
			bufh = pos[0];
			bufv = pos[1];
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufv++;
				if(bufh == a && bufv == b) {return true;}
			}
			bufh = pos[0];
			bufv = pos[1];
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufh--;
				bufv++;
				if(bufh == a && bufv == b) {return true;}
			}
			return false;
		}
	}
//Finds which "path" a move would be on, if possible. A value of -1 means the move is not possible, a value of 3 means the main diagonal (like in a matrix), a value of 2 means a vertical move, and a value of 1 means the other diagonal.
	int onPath(int a, int b) {
		int bufh = pos[0];
		int bufv = pos[1];
		if(!isMovePossible(a,b)) {return -1;}
		if(Black) {
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufh--;
				bufv--;
				if(bufh == a && bufv == b) {return 1;}
			}
			bufh = pos[0];
			bufv = pos[1];
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufv--;
				if(bufh == a && bufv == b) {return 2;}
			}
			bufh = pos[0];
			bufv = pos[1];
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufh++;
				bufv--;
				if(bufh == a && bufv == b) {return 3;}
			}
		}
		else {
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufh++;
				bufv++;
				if(bufh == a && bufv == b) {return 1;}
			}
			bufh = pos[0];
			bufv = pos[1];
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufv++;
				if(bufh == a && bufv == b) {return 2;}
			}
			bufh = pos[0];
			bufv = pos[1];
			while(bufh >= 1 && bufv >= 1 && bufh <= 8 && bufv <= 8) {
				bufh--;
				bufv++;
				if(bufh == a && bufv == b) {return 3;}
			}

		}
		return -1;
	}

	//Finds the taxicab distance between two points.
	int dist(int h, int v) {
		if(pos[0] == h && pos[1] == v) {return 0;}
		if(!isMovePossible(h,v)) {return -1;}
		if(Black) {return pos[1]-v;}
		else {return v-pos[1];}
	}

	int getSumo() {return sumo;}
	int x() {return pos[0];}
	int y() {return pos[1];}
	bool isBlack() {return Black;}
	bool isWhite() {return !Black;}
	int range() {return moveRange;}

	//Moves a piece. Does not check whether the move is possible.
	void uMove(int x, int y) {
		pos[0] = x;
		pos[1] = y;
	}

	void promote() {
		sumo++;
		setMoveRange();
	}
	void setMoveRange() {
		if(sumo == 0) {moveRange = 8;}
		if(sumo == 1) {moveRange = 5;}
		if(sumo == 2) {moveRange = 3;}
		if(sumo == 3) {moveRange = 1;}
		if(sumo == 4) {moveRange = 0;}
	}

	int getMoveRange() {
		return moveRange;
	}

	color getColor() {
		return col;
	}

	bool isDummy() {
		if(col == none) {return true;}
		return false;
	}

	bool isNotDummy() {
		return !isDummy();
	}

	int score() {
		if(sumo == 0) {return 0;}
		if(sumo == 1) {return 1;}
		if(sumo == 2) {return 3;}
		if(sumo == 3) {return 7;}
		if(sumo == 4) {return 15;}
		return 0;
	}

//Prints out a string that corresponds to the piece's properties. Mainly for debugging right now.
	void printOut() {
		if(Black) {std::cout << "black and ";}
		else {std::cout << "white and ";}

		if(col == brown) {std::cout << "brown" << std::endl;}
		else if(col == green) {std::cout << "green" << std::endl;}
		else if(col == red) {std::cout << "red" << std::endl;}
		else if(col == yellow) {std::cout << "yellow" << std::endl;}
		else if(col == pink) {std::cout << "pink" << std::endl;}
		else if(col == purple) {std::cout << "purple" << std::endl;}
		else if(col == blue) {std::cout << "blue" << std::endl;}
		else if(col == orange) {std::cout << "orange" << std::endl;}
		else {std::cout << "is a dummy" << std::endl;}

		std::cout << pos[0] << ", " << pos[1] << std::endl;
		std::cout << sumo << std::endl;
	}
};




};

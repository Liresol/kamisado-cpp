#include "Piece.hpp"
#include <array>


//For future reference: n is Brown, g is Green, r is Red, y is Yellow, i is Pink, u is Purple, l is Blue, and o is Orange
enum id {
	Bn, Bg, Br, By, Bi, Bu, Bl, Bo,
	Wn, Wg, Wr, Wy, Wi, Wu, Wl, Wo
};

bool isBetweenExc(int i, int low, int high) {
	return (i > low && i < high);
}

bool isBetweenInc(int i, int low, int high) {
	return (i >= low && i <= high);
}

bool intIsWhite(int i) {
	return isBetweenInc(i, 8, 15);
}

bool intIsBlack(int i) {
	return isBetweenInc(i, 0, 7);
}
//BLACK IS ON TOP, MAY REQUIRE SERIOUS CHANGES

class Board {
	Piece WPieces[8];
	Piece BPieces[8];
	static const std::array<color, 64> field;

	public:
	Board() {
		for(int i=0;i<8;i++) {
			WPieces[i] = Piece(false,0,cConvert(i));
			BPieces[i] = Piece(true,0,cConvert(i));
		}
	}
	Board operator= (const Board copyFrom) {
		for(int i=0;i<7;i+=1) {
			BPieces[i] = copyFrom.BPieces[i];
			WPieces[i] = copyFrom.WPieces[i];
		}
		return *this;
	}
	//Does nothing, but may be used for mapping piece IDs onto pieces.
	Piece MapID(id i) {
		if(i == Bn) {return BPieces[0];}
		else if(i == Bg) {return BPieces[1];}
		else if(i == Br) {return BPieces[2];}
		else if(i == By) {return BPieces[3];}
		else if(i == Bi) {return BPieces[4];}
		else if(i == Bu) {return BPieces[5];}
		else if(i == Bl) {return BPieces[6];}
		else if(i == Bo) {return BPieces[7];}
		else if(i == Wn) {return WPieces[0];}
		else if(i == Wg) {return WPieces[1];}
		else if(i == Wr) {return WPieces[2];}
		else if(i == Wy) {return WPieces[3];}
		else if(i == Wi) {return WPieces[4];}
		else if(i == Wu) {return WPieces[5];}
		else if(i == Wl) {return WPieces[6];}
		else if(i == Wo) {return WPieces[7];}
		else {return Piece();}
	}
/*
 *Bn, Bg, Br, By, Bi, Bu, Bl, Bo,
	Wn, Wg, Wr, Wy, Wi, Wu, Wl, Wo

 */
	int intID(id I) {
		if (I == Bn) {return 0;}
		else if(I == Bg) {return 1;}
		else if(I == Br) {return 2;}
		else if(I == By) {return 3;}
		else if(I == Bi) {return 4;}
		else if(I == Bu) {return 5;}
		else if(I == Bl) {return 6;}
		else if(I == Bo) {return 7;}
		else if(I == Wn) {return 8;}
		else if(I == Wg) {return 9;}
		else if(I == Wr) {return 10;}
		else if(I == Wy) {return 11;}
		else if(I == Wi) {return 12;}
		else if(I == Wu) {return 13;}
		else if(I == Wl) {return 14;}
		else if(I == Wo) {return 15;}
		else {return -1;}
	}
	//CHANGE COORDINATES TO INCLUDE 8
	bool occupied(int x, int y) {
		for(int i=1;i<=8;i++) {
			if(BPieces[i].x() == x && BPieces[i].y() == y) {return true;}
			if(WPieces[i].x() == x && WPieces[i].y() == y) {return true;}
		}
		return false;
	}

	//Returns the color in the given coordinates (1 to 8)
	color colorIn(int x, int y) {
		if(!isBetweenInc(x,1,8) || !isBetweenInc(y,1,8)) {return none;}
		return field[8*y+x-9];
	}

	//Prints the color in the given coordinates (1 to 8)
	void printColor(int x, int y) {
		color buf = colorIn(x,y);
		if(buf == brown) {std::cout << "brown" << std::endl;}
		if(buf == green) {std::cout << "green" << std::endl;}
		if(buf == red) {std::cout << "red" << std::endl;}
		if(buf == yellow) {std::cout << "yellow" << std::endl;}
		if(buf == pink) {std::cout << "pink" << std::endl;}
		if(buf == purple) {std::cout << "purple" << std::endl;}
		if(buf == blue) {std::cout << "blue" << std::endl;}
		if(buf == orange) {std::cout << "orange" << std::endl;}
		if(buf == none) {std::cout << "none" << std::endl;}
	}

	//Returns a piece according to the following: 0-7 return the black pieces, 8-15 return the white pieces, and everything else returns a dummy.
	Piece mapPiece(int p) {
		if(0 <= p && p <= 7) {
			return BPieces[p];
		}
		if(8 <= p && p <= 15) {
			return WPieces[p-8];
		}
		return Piece();
	}

	Piece occPiece(int x, int y) {
		for(int i=0;i<8;i++) {
			if(BPieces[i].x() == x && BPieces[i].y() == y) {return WPieces[i];}
			if(WPieces[i].x() == x && WPieces[i].y() == y) {return WPieces[i];}
		}
		return Piece();
	}

		//Checks whether or not a piece can move to a certain position.
	bool canMove(Piece p, int h, int v) {
		if(!p.isMovePossible(h,v)) {return false;}
		if(p.getSumo() > 0 && p.dist(h,v) > p.range()) {return false;}
		if(p.isBlack()) {
			switch(p.onPath(h,v)) {
				case 1: for(int i=1;i<p.dist(h,v); i++) {
						if(occupied(p.x()-i, p.y()-i)) {return false;}
					}
					if(!occupied(p.x()-p.dist(h,v), p.y()-p.dist(h,v))) {return true;}
					else {return false;}
					break;
				case 2: for(int i=1;i<p.dist(h,v); i++) {
						if(occupied(p.x(), p.y()-i)) {return false;}
					}
					if(!occupied(p.x(), p.y()-p.dist(h,v))) {return true;}
					else {return false;}
					break;
				case 3: for(int i=1;i<p.dist(h,v); i++) {
						if(occupied(p.x()+i, p.y()-i)) {return false;}
					}
					if(!occupied(p.x()+p.dist(h,v), p.y()-p.dist(h,v))) {return true;}
					else {return false;}
					break;
				default: return false; break;

			}
		}
		else {
		switch(p.onPath(h,v)) {
				case 1: for(int i=1;i<p.dist(h,v); i++) {
						if(occupied(p.x()+i, p.y()+i)) {return false;}
					}
					if(!occupied(p.x()+p.dist(h,v), p.y()+p.dist(h,v))) {return true;}
					else {return false;}
					break;
				case 2: for(int i=1;i<p.dist(h,v); i++) {
						if(occupied(p.x(), p.y()+i)) {return false;}
					}
					if(!occupied(p.x(), p.y()+p.dist(h,v))) {return true;}
					else {return false;}
					break;
				case 3: for(int i=1;i<p.dist(h,v); i++) {
						if(occupied(p.x()-i, p.y()+i)) {return false;}
					}
					if(!occupied(p.x()-p.dist(h,v), p.y()+p.dist(h,v))) {return true;}
					else {return false;}
					break;
				default: return false; break;

			}

		}
		return false;
		
	}

	bool canMove(int id, int x, int y) {
		if(id >= 0 && id < 8) {return canMove(BPieces[id],x,y);}
		if(id >= 8 && id < 16) {return canMove(WPieces[id-8],x,y);}
		return false;
	}

	bool canSumoPush(Piece p, int x, int y) {
		int s = p.getSumo();
		int line = 0;
		if(s == 0) {return false;}
		if(p.onPath(x,y) != 2) {return false;}
		if(p.dist(x,y) >= p.getMoveRange()) {return false;}
		for(int i=1;i<=s;i++) {
			if(occupied(x,y+i)) {line += 1;}
			if(occPiece(x,y+i).getSumo() >= s) {return false;}
		}
		if(line > s) {return false;}
		if(line == s) {
			if(occupied(x,y+s+1)) {return false;}
		}
		return true;
	}

	bool canSumoPush(int id, int x, int y) {
		if(id >= 0 && id < 8) {return canSumoPush(BPieces[id],x,y);}
		if(id >= 8 && id < 16) {return canSumoPush(WPieces[id-8],x,y);}
		return false;
	}

	//Checks to see if the piece can move at all.
	bool locked(Piece p) {
		if(p.isBlack()) {
			return canMove(p,p.x()-1,p.y()+1) && canMove(p,p.x(),p.y()+1) && canMove(p,p.x()+1,p.y()+1) && canSumoPush(p,p.x(),p.y()+1);
		}
		else {
			return canMove(p,p.x()-1,p.y()-1) && canMove(p,p.x(),p.y()-1) && canMove(p,p.x()+1,p.y()-1) && canSumoPush(p,p.x(),p.y()-1);
		}
	}

	//Performs the move of a piece if possible.
	void move(Piece& p, int x, int y) {
		if(canMove(p,x,y) != canSumoPush(p,x,y)){
			p.uMove(x,y);
		}
		else {std::cout << "Debugging is good." << std::endl;}
	}

	void move(int id, int x, int y) {
		if(id < 8 && id >= 0) {
			move(BPieces[id],x,y);
		}
		else if(id >= 8 && id < 16) {
			move(WPieces[id-8],x,y);
		}
	}
	void move(id I, int x, int y) {
		if(!occupied(x,y)) {
			move(intID(I),x,y);
		}
	}


	//Teleports a piece to a position, given that it is not currently taken by another piece.
	void teleport(Piece& p, int x, int y) {
		if(!occupied(x,y) && isBetweenInc(x,1,8) && isBetweenInc(y,1,8)) {
			p.uMove(x,y);
		}
	}

	void teleport(int id, int x, int y) {
		if(id < 8 && id >= 0) {
			teleport(BPieces[id],x,y);
		}
		else if(id >= 8 && id < 16) {
			teleport(WPieces[id-8],x,y);
		}
	}

	void teleport(id I, int x, int y) {
		if(!occupied(x,y)) {
			teleport(intID(I),x,y);
		}
	}

	//Swaps the positions of two pieces.
	void swap(Piece& p, Piece& q) {
		int buf[2];
		buf[0] = p.x();
		buf[1] = p.y();
		p.uMove(q.x(),q.y());
		q.uMove(buf[0],buf[1]);
	}

	void swap(int i, int j) {
		if(intIsWhite(i) && intIsWhite(j)) {swap(WPieces[i-8],WPieces[j-8]);}
		else if(intIsWhite(i) && intIsBlack(j)) {swap(WPieces[i-8],BPieces[j]);}
		else if(intIsBlack(i) && intIsWhite(j)) {swap(BPieces[i], WPieces[j-8]);}
		else if(intIsBlack(i) && intIsBlack(j)) {swap(BPieces[i], BPieces[j]);}
	}

	//Checks the board to see if there are 8 white pieces and 8 black pieces, all on different positions.
	bool valid() {
		int nB = 0;
		int nW = 0;
		for(int y=0;y<8;y++) {
			for(int x=0;x<8;x++) {
				if(occupied(x,y)) {
					if(occPiece(x,y).isBlack()) {nB += 1;}
					if(occPiece(x,y).isBlack()) {nW += 1;}
					else {return false;}
				}
			}
		}
		if(nB == 8 && nW == 8) {return true;}
		return false;
	}

	bool invalid() {return !valid();}

	void toString(id I) {
		MapID(I).toString();
	}

	
};

const std::array<color,64> Board::field = {brown,green,red,yellow,pink,purple,blue,orange,purple,brown,yellow,blue,green,pink,orange,red,blue,yellow,brown,purple,red,orange,pink,green,yellow,red,green,brown,orange,blue,purple,pink,pink,purple,blue,orange,brown,green,red,yellow,green,pink,orange,red,purple,brown,yellow,blue,red,orange,pink,green,blue,yellow,brown,purple,orange,blue,purple,pink,yellow,red,green,brown};

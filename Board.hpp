#include "Piece.hpp"

//Effectively a "piece id". May not be useful at all.
enum id {
	Bn, Bg, Br, By, Bi, Bu, Bl, Bo,
	Wn, Wg, Wr, Wy, Wi, Wu, Wl, Wo
};
//BLACK IS ON TOP, MAY REQUIRE SERIOUS CHANGES

class Board {
	Piece WPieces[8];
	Piece BPieces[8];
	color field[8][8];

	public:
	Board() {
		initField();
		for(int i=0;i<8;i++) {
			WPieces[i] = Piece(false,0,cConvert(i));
			BPieces[i] = Piece(true,0,cConvert(i));
		}
	}

	//Does nothing, but may be used for mapping piece IDs onto pieces.
	Piece MapID(id i) {
		if(i == Bn) {return BPieces[0];}
		if(i == Bg) {return BPieces[1];}
		if(i == Br) {return BPieces[2];}
		if(i == By) {return BPieces[3];}
		if(i == Bi) {return BPieces[4];}
		if(i == Bu) {return BPieces[5];}
		if(i == Bl) {return BPieces[6];}
		if(i == Bo) {return BPieces[7];}
		if(i == Wn) {return WPieces[0];}
		if(i == Wg) {return WPieces[1];}
		if(i == Wr) {return WPieces[2];}
		if(i == Wy) {return WPieces[3];}
		if(i == Wi) {return WPieces[4];}
		if(i == Wu) {return WPieces[5];}
		if(i == Wl) {return WPieces[6];}
		if(i == Wo) {return WPieces[7];}
		else {return Piece();}
	}
	//COORDINATES START FROM 0 AND GO TO 7
	bool occupied(int x, int y) {
		for(int i=0;i<8;i++) {
			if(BPieces[i].x() == x && BPieces[i].y() == y) {return true;}
			if(WPieces[i].x() == x && WPieces[i].y() == y) {return true;}
		}
		return false;
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

	//Sets the colors for every square on the board.
	void initField() {
		field[0][0] = field[1][1] = field[2][2] = field[3][3] = field[4][4] = field[5][5] = field[6][6] = field[7][7] = brown;
		field[1][0] = field[4][1] = field[7][2] = field[2][3] = field[5][4] = field[0][5] = field[3][6] = field[6][7] = green;
		field[2][0] = field[7][1] = field[4][2] = field[1][3] = field[6][4] = field[3][5] = field[0][6] = field[5][7] = red;
		field[3][0] = field[2][1] = field[1][2] = field[0][3] = field[7][4] = field[6][5] = field[5][6] = field[4][7] = yellow;
		field[4][0] = field[5][1] = field[6][2] = field[7][3] = field[0][4] = field[1][5] = field[2][6] = field[3][7] = pink;
		field[5][0] = field[0][1] = field[3][2] = field[6][3] = field[1][4] = field[4][5] = field[7][6] = field[2][7] = purple;
		field[6][0] = field[3][1] = field[0][2] = field[5][3] = field[2][4] = field[7][5] = field[4][6] = field[1][7] = blue;
		field[7][0] = field[6][1] = field[5][2] = field[4][3] = field[3][4] = field[2][5] = field[1][6] = field[0][7] = orange;
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
	void move(Piece p, int x, int y) {
		if(canMove(p,x,y) != canSumoPush(p,x,y)){
			p.uMove(x,y);
		}
	}
	
	//Teleports a piece to a position, given that it is not currently taken by another piece.
	void teleport(Piece p, int x, int y) {
		if(!occupied(x,y)) {
			p.uMove(x,y);
		}
	}

	//Swaps the positions of two pieces.
	void swap(Piece p, Piece q) {
		int buf[2];
		buf[0] = p.x();
		buf[1] = p.y();
		p.uMove(q.x(),q.y());
		q.uMove(buf[0],buf[1]);
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

};

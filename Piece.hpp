enum color {
	brown, green, red, yellow, pink, purple, blue, orange, none
};

color cConvert(int i) {
	if(i == 0) {return brown;}
	if(i == 1) {return green;}
	if(i == 2) {return red;}
	if(i == 3) {return yellow;}
	if(i == 4) {return pink;}
	if(i == 5) {return purple;}
	if(i == 6) {return blue;}
	if(i == 7) {return orange;}
	else {return none;}
}

class Piece {
	//When initializing, set the sumo and moveRange things.
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
			if(colval == green) {pos[0] = 7;}
			if(colval == red) {pos[0] = 6;}
			if(colval == yellow) {pos[0] = 5;}
			if(colval == pink) {pos[0] = 4;}
			if(colval == purple) {pos[0] = 3;}
			if(colval == blue) {pos[0] = 2;}
			if(colval == orange) {pos[0] = 1;}
		}
		else {
			pos[1] = 1;
			if(colval == brown) {pos[0] = 1;}
			if(colval == green) {pos[0] = 2;}
			if(colval == red) {pos[0] = 3;}
			if(colval == yellow) {pos[0] = 4;}
			if(colval == pink) {pos[0] = 5;}
			if(colval == purple) {pos[0] = 6;}
			if(colval == blue) {pos[0] = 7;}
			if(colval == orange) {pos[0] = 8;}
		}
		setMoveRange();
	}

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
//Finds which "path" a move would be on, if possible. A value of -1 means the move is not possible, a value of 3 means the main diagonal, a value of 2 means a vertical move, and a value of 1 means the other diagonal.
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

	//Does not check whether the move is possible.
	void uMove(int x, int y) {
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
};

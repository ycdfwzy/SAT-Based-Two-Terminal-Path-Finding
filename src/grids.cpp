#include "grids.h"

using namespace std;

grids::grids(int row_, int col_){
	row = row_;
	col = col_;
	broken.assign( (row+2)*(col+2), false );
}

void grids::addbroken(int x, int y){
	if (x >= 1 && x <= row && y >= 1 && y <= col)
		broken[getindex(x, y)] = true;
}

void grids::addterminals(int sx, int sy, int tx, int ty){
	if (sx == tx && sx == ty) return;
	int s = getindex(sx, sy);
	int t = getindex(tx, ty);
	terminal.push_back(make_pair(s, t));
}

int grids::getrow(){
	return row;
}

int grids::getcol(){
	return col;
}

int grids::getindex(int x, int y){
	return x*(col+2)+y;
}

bool grids::isbroken(int index){
	if (index > (row+2)*(col+2))
		return false;
	return broken[index];
}

bool grids::isbroken(int x, int y){
	if (x < 0 || x > row+1 || y < 0 || y > col+1)
		return false;
	return isbroken(getindex(x, y));
}

int grids::getup(int index){
	int x = index/(col+2);
	int y = index%(col+2);
	if (x <= 0 || x > row+1)
	{
		cout << "error" << endl << endl;
		return -1;
	}
	return getindex(x-1, y);
}

int grids::getdown(int index){
	int x = index/(col+2);
	int y = index%(col+2);
	if (x < 0 || x >= row+1){
		cout << "error" << endl << endl;
		return -1;
	}
	return getindex(x+1, y);
}

int grids::getleft(int index){
	int x = index/(col+2);
	int y = index%(col+2);
	if (x < 0 || x > row+1 || y == 0){
		cout << "error" << endl << endl;
		return -1;
	}
	return getindex(x, y-1);
}

int grids::getright(int index){
	int x = index/(col+2);
	int y = index%(col+2);
	if (x < 0 || x > row+1 || y == col+1){
		cout << "error" << endl << endl;
		return -1;
	}
	return getindex(x, y+1);
}
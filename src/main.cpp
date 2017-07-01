#include "checker.h"
#include "visual.h"
#include "grids.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void test(const char* filename){
	//cout << "Z3:" << endl;
	clock_t start, finish;
	start = clock();
	int row, col, nb, nt;
	ifstream in(filename);
	in >> row >> col >> nb >> nt;
	grids Grid(row, col);
	//cout << row << endl;
	//cout << col << endl;
	for (int i = 0; i < nb; ++i){
		int x, y;
		in >> x >> y;
		Grid.addbroken(x, y);
	}
	for (int i = 0; i < nt; ++i){
		int sx, sy, tx, ty;
		in >> sx >> sy >> tx >> ty;
		Grid.addterminals(sx, sy, tx, ty);
	}
	in.close();
	checker C(Grid);
	C.mainwork();
	Visual* vis = new Visual();
	vis->Paint(C);
	delete vis;
	//cout << "OK" << endl;
	finish = clock();
	cout<< "Time: " << (finish-start)/CLOCKS_PER_SEC <<endl;
	/*
	cout << "costflow" << endl;
	start = clock();
	Graph G(filename);
	CostFlow 
	finish = clock();
	cout<< "Time: " << (finish-start)/CLOCKS_PER_SEC <<endl;*/
}

int main(int argc, char* args[]){
	test(args[1]);
	
	return 0;
}
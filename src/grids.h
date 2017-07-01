#ifndef GRIDS_H_
#define GRIDS_H_

#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

class grids{
	private:
		int row, col;
		vector<bool> broken;
		
	public:
		vector< pair<int, int> > terminal;
		grids(int, int);
		void addbroken(int, int);
		void addterminals(int, int, int, int);
		int getrow();
		int getcol();
		int getup(int);
		int getdown(int);
		int getleft(int);
		int getright(int);
		int getindex(int, int);
		bool isbroken(int, int);
		bool isbroken(int);
};


#endif
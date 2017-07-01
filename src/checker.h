#ifndef CHECKER_H_
#define CHECKER_H_

#include "grids.h"
#include <z3++.h>
#include <vector>

using namespace z3;
using namespace std;

class checker{
	public:
		checker(grids&);
		void mainwork();
		void add_limits(optimize&, context&, expr_vector&, expr_vector&, int&, int&);
		void print(int, int);
		
		int MAP[100][100];
		grids& m_grids;
		vector<bool> visited;
		vector<int> result;
};

#endif
#include <z3++.h>
#include "grids.h"
#include "checker.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
using namespace z3;

const int infinity = (1<<30);

checker::checker(grids& grids_):m_grids(grids_){}

void checker::mainwork(){
	int len = m_grids.terminal.size();
	int totalgrids = (m_grids.getrow()+2)*(m_grids.getcol()+2);
	
	context c;
	expr_vector x(c);
	optimize opt(c);
	for (int i = 0; i < totalgrids; ++i){
		stringstream x_name;
		int R = i/(m_grids.getcol()+2);
		int C = i%(m_grids.getcol()+2);
		//if (R >= 1 && R <= m_grids.getrow() && C >=1 && C <= m_grids.getcol()){
			x_name << "x_" << R << '_' << C;
			x.push_back(c.int_const(x_name.str().c_str()));
		//}
	}
	expr_vector exist(c);
	for (int i = 0; i < len; ++i){
		stringstream x_name;
		x_name << "exist_" << (i+1);
		exist.push_back(c.bool_const(x_name.str().c_str()));
	}
	add_limits(opt, c, x, exist, len, totalgrids);
	
	expr o = c.int_val(1);
	//expr oo = c.int_val(-1);
	expr z = c.int_val(0);
	expr_vector t1(c);
	expr_vector t2(c);
	for (int i = 0; i < len; ++i){
		int S = m_grids.terminal[i].first;
		//int T = m_grids.terminal[i].second;
		t1.push_back(ite(exist[i], o, z));
	}
	for (int i = 0; i < totalgrids; ++i){
		int R = i/(m_grids.getcol()+2);
		int C = i%(m_grids.getcol()+2);
		if (R >= 1 && R <= m_grids.getrow() && C >=1 && C <= m_grids.getcol())
		t2.push_back(ite(x[i] > 0, o, z));
	}
	
	optimize::handle h1 = opt.maximize(sum(t1));
	optimize::handle h2 = opt.minimize(sum(t2));
	
	//params p(c);
    //p.set("priority",c.str_symbol("pareto"));
    //opt.set(p);
	if (opt.check() == sat){
		cout << opt.lower(h1) << endl;
		cout << opt.upper(h2) << endl;
	}

	ofstream out("log.txt");
	out << opt.lower(h1) << endl;
	model m = opt.get_model();
	//cout << m << endl;
	for (int i = 0; i < totalgrids; ++i){
		int R = i/(m_grids.getcol()+2);
		int C = i%(m_grids.getcol()+2);
		if (R >= 1 && R <= m_grids.getrow() && C >=1 && C <= m_grids.getcol())
			out << m.eval(x[i]) << endl;
		else
			out << "0" << endl;
	}
	out.close();
	ifstream in("log.txt");
	int tot;
	in >> tot;
	for (int i = 0; i < totalgrids; ++i)
		in >> MAP[i/(m_grids.getcol()+2)][i%(m_grids.getcol()+2)];
	in.close();
	remove("log.txt");
	//if (tot == len){
		for (int i = 0; i < m_grids.getrow()+2; ++i){
			for (int j = 0; j < m_grids.getcol()+2; ++j){
				//cout << MAP[i][j];
				if (m_grids.isbroken(i,j))
					MAP[i][j] = -1;
			}
			//cout << endl;
		}
	//}
}

void checker::add_limits(optimize& opt, context& c, expr_vector& x, expr_vector& exist, int& len, int& totalgrids){
	expr o = c.int_val(1);
	expr z = c.int_val(0);
	
	for (int i = 0; i < totalgrids; ++i){
		int R = i/(m_grids.getcol()+2);
		int C = i%(m_grids.getcol()+2);
		if (R <= 0 || R > m_grids.getrow() || C <= 0 || C > m_grids.getcol()) continue;
		//if (R <= 0 || R > m_grids.getrow() || C <= 0 || C > m_grids.getcol() || m_grids.isbroken(i))
		if (m_grids.isbroken(i))
			opt.add(x[i] == 0);	// avoid obstacle
		else
		{
			expr_vector t(c);
			if (R > 1)
			t.push_back(ite(x[m_grids.getup(i)] == x[i], o, z));
			if (R < m_grids.getrow())
			t.push_back(ite(x[m_grids.getdown(i)] == x[i], o, z));
			if (C > 1)
			t.push_back(ite(x[m_grids.getleft(i)] == x[i], o, z));
			if (C < m_grids.getcol())
			t.push_back(ite(x[m_grids.getright(i)] == x[i], o, z));
			int kind = 0;
			for (int j = 0; j < len; ++j){
				int S = m_grids.terminal[j].first;
				int T = m_grids.terminal[j].second;
				if (i == S || i == T) kind = j+1;
			}
			if (kind > 0) 	// terminals
				opt.add((exist[kind-1] && x[i] == kind && sum(t) == 1) ||
					(!exist[kind-1] && (x[i]==0 || (x[i]>0 && x[i]<=len && sum(t)==2))) );
				//opt.add((x[i] == 0) || (x[i] > 0 && ((x[i] == kind && sum(t) == 1) || (x[i] != kind && sum(t) == 2))));
			else			// paths
				opt.add((x[i] == 0) || (x[i] > 0 && x[i]<=len && sum(t) == 2));
		}
	}
}

void checker::print(int route, int d){
	visited[d] = true;
	int R = d/(m_grids.getcol()+2);
	int C = d%(m_grids.getcol()+2);
	cout << R << ' ' << C << endl;
	if (d == m_grids.terminal[route].second)
		return;
	int up = m_grids.getup(d);
	int down = m_grids.getdown(d);
	int left = m_grids.getleft(d);
	int right = m_grids.getright(d);
	int len = m_grids.terminal.size();
	
	if (!visited[up] && result[up] == 1)
		print(route, up);
	
	if (!visited[down] && result[down] == 1)
		print(route, down);
	
	if (!visited[left] && result[left] == 1)
		print(route, left);
	
	if (!visited[right] && result[right] == 1)
		print(route, right);
}

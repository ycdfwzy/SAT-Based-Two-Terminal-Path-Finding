#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

pair<int, int> a[1000];
char mp[50][50];

int main(){
	srand(time(0));
	int n = 9;
	int m = 9;
	int nb = 22;
	int nt = 6;
	ofstream out("in10.txt");
	out << n << " " << m << " " << nb << " " << nt << endl;
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= m; ++j){
			a[(i-1)*m+j-1] = make_pair(i, j);
			mp[i][j] = '.';
		}
		mp[i][m+1] = '\0';
	}
	random_shuffle(a, a+(n*m));
	for (int i = 0; i < nb; i++){
		out << a[i].first << " " << a[i].second << endl;
		mp[a[i].first][a[i].second] = 'B';
	}
	for (int i = 0; i < nt; i++){
		out << a[nb+i*2].first << " " << a[nb+i*2].second << " " << a[nb+i*2+1].first << " " << a[nb+i*2+1].second << endl;
		mp[a[nb+i*2].first][a[nb+i*2].second] = i+'0';
		mp[a[nb+i*2+1].first][a[nb+i*2+1].second] = i+'0';
	}
	for (int i = 1; i <= n; i++)
		cout << mp[i]+1 << endl;
	return 0;
}

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
#include <map>
#include <cmath>
#include <queue>
using namespace std;
#pragma comment (linker, "/STACK:64000000")

typedef long long ll;
 
#if _DEBUG 
ifstream cin ("input.txt");
ofstream cout("output.txt");
#else
ifstream cin ("bridges.in");
ofstream cout("bridges.out");
#endif

const int maxx = 20000;

int t  = 0, tim[maxx + 2], up[maxx + 2];
bool used[maxx + 2];


struct str {
	int to, index;
};


vector< vector <str> > d;

vector <int> s;

void dfs(int v, int p) {
	used[v] = true;
	t++;
	tim[v] = t;
	up[v] = t;
	for(int j = 0; j < d[v].size(); j++) {
		int u = d[v][j].to;
		if(u == p)
			continue;
		if(used[u])
			up[v] = min(up[v], tim[u]);
		else{
			dfs(u, v);
			up[v] = min(up[v], up[u]);
			if(up[u] > tim[v]) {
				s.push_back(d[v][j].index);
			}
		}
	}
}


int main() {
	int n, m;
	cin >> n >> m;
	d.resize(n + 1);
	for(int i = 0; i < m; i++) {
		str x, y;
		cin >> x.to >> y.to;
		x.index = i + 1;
		y.index = i + 1;
		d[x.to].push_back(y);
		d[y.to].push_back(x);
	}
	for(int i = 1; i <= n; i++) {
		if(!used[i]) {
			dfs(i, -1);
		}
	}
	cout << s.size() << '\n';
	sort(s.begin(), s.end());
	for(int i = 0 ; i < s.size(); i++) {
		cout << s[i] << '\n';
	}
	

    return 0;
}
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

typedef long long ll;
 
#if _DEBUG 
ifstream cin("input.txt");
ofstream cout("output.txt");
#else
ifstream cin("flow.in");
ofstream cout("flow.out");
#endif

typedef long long ll;

struct go {
	int to, index;
	ll c, f;
	go() {}
	go(int to, ll c, ll f, int index) : to(to), index(index), c(c), f(f) {}
};

vector < vector <go> > vv;


void add_edge(int from, int to, ll c, ll f) {
	int v = vv[to].size();
	int u = vv[from].size();
	go to1 = go(to, c, f, v);
	go from1 = go(from, 0, -f, u);
	vv[from].push_back(to1);
	vv[to].push_back(from1);
}

bool used[1002];

int n, m;

ll ans = 0;



const ll INF = 1000000000000000000;

struct fromm {
	int x, y;
	fromm() {}
	fromm(int x, int y) : x(x), y(y) {}
};

fromm way[1002];


bool bfs(int v) {
	queue <int> q;
	fill_n(used, n + 1, false);
	used[v] = true;
	q.push(v);
	while(!q.empty()) {
		v = q.front();
		q.pop();
		for(int i = 0; i < (int)vv[v].size(); i++) {
			if(used[vv[v][i].to]) continue;
			if(vv[v][i].c > vv[v][i].f) {
				used[vv[v][i].to] = true;
				way[vv[v][i].to] = fromm(v, i);
				q.push(vv[v][i].to);
			}
		}
	}
	if(!used[n])
		return false;
	fromm w = way[n];
	ll mi = INF;
	while(w.x != -1) { 
		if(mi > vv[w.x][w.y].c - vv[w.x][w.y].f) {
			mi = vv[w.x][w.y].c - vv[w.x][w.y].f;
		}
		w = way[w.x];
	}
	w = way[n];
	while(w.x != -1) {
		vv[w.x][w.y].f += mi;
		int f3 = vv[w.x][w.y].index;
		int f2 = vv[w.x][w.y].to;
		vv[f2][f3].f -= mi;
		w = way[w.x];
	}
	ans += mi;
	return true;
}



int main() {
	cin >> n >> m;
	way[1] = fromm(-1, -1);
	vv.resize(n + 1);
	for(int i = 0; i < m; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		add_edge(from, to, weight, 0);
	}
	while(bfs(1)) {}
	cout << ans;
	return 0;
}
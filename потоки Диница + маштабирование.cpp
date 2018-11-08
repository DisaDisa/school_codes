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
 

struct edge {
	int to, index;
	ll capacity, flow;
	edge() {}
	edge(int to, ll capacity, ll flow, int index) : to(to),  index(index),
		capacity(capacity), flow(flow) {}
};

vector < vector <edge> > edges;


void add_edge(int from, int to, ll capacity, ll flow) {
	int v = edges[to].size();
	int u = edges[from].size();
	edge to1 = edge(to, capacity, flow, v);
	edge from1 = edge(from, 0, -flow, u);
	edges[from].push_back(to1);
	edges[to].push_back(from1);
}

bool used[502];

int n, m;

ll ans = 0;



const ll INF = 1000000000000000000;

ll dis[502];

int q[502], l = 0, r = 0;

void push(int v) {
	q[r] = v;
	r++;
}

void pop() {
	l++;
}

bool empty() {
	return l == r;
}

void clear() {
	l = 0;
	r = 0;
}

bool bfs(int v, ll max_dis) {
	clear();
	fill_n(used, n + 1, false);
	dis[v] = 0;
	used[v] = true;
	push(v);
	while (!empty()) {
		v = q[l];
		pop();
		for (int i = 0; i < (int)edges[v].size(); i++) {
			edge &e = edges[v][i];
			if (used[e.to] ||
				e.capacity - e.flow < max_dis)
				continue;
			used[e.to] = true;
			dis[e.to] = dis[v] + 1;
			push(e.to);
			if (e.to == n)
				break;
		}
		if (used[n])
			break;
	}
	if (used[n])
		return true;
	return false;
}

int head[502];

ll dfs(int v, int t, ll Cmin, ll max_dis) {
	if (v == t) 
		return Cmin;
	for (int i = head[v]; i < (int)edges[v].size(); i++, head[v]++) {
		int to = edges[v][i].to;
		edge &e = edges[v][i];
		if(dis[to] != dis[v] + 1 || e.capacity - e.flow < max_dis)
			continue;
		ll add = dfs(to, t, min(Cmin, e.capacity - e.flow), max_dis);
		if (add == 0)
			continue;
		e.flow += add;
		edges[to][e.index].flow -= add;
		return add;
	}
	return 0;
}



int main() {
	#if _DEBUG 
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	#else
	ifstream cin("flow2.in");
	ofstream cout("flow2.out");
	#endif
	cin >> n >> m;
	edges.resize(n + 1);
	for (int i = 0; i < m; i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		add_edge(from, to, weight, 0);
	}
	ll ans = 0;
	for (int k = 30; k >= 0; k--) {
		ll max_dis = 1 << k;
		while (bfs(1, max_dis)) {
			fill_n(head, n + 1, 0);
			while (true) {
				ll flow = dfs(1, n, INF, max_dis);
				if (flow == 0)
					break;
				ans += flow;
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
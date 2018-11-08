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
ifstream cin("input.txt");
ofstream cout("output.txt");
#else
ifstream cin("lca2.in");
ofstream cout("lca2.out");
#endif

const int maxx = 100002;

const int LOG = 20;

int timer = 1, in[maxx], out[maxx], d[maxx][21];

vector < vector <int> > vv;

ll a[maxx * 20];

void dfs(int v, int p) {
	in[v] = timer++;
	d[v][0] = p;
	for (int i = 1; i <= LOG; i++) {
		d[v][i] = d[d[v][i - 1]][i - 1];
	}
	for (int i = 0; i < vv[v].size(); i++) {
		int to = vv[v][i];
		if (to != p) {
			dfs(to, v);
		}
	}
	out[v] = timer;
}

bool upper(int f1, int f2) {
	return in[f2] <= in[f1] && out[f1] <= out[f2];
}

int lca(int a, int b) {
	if (upper(a, b)) return b;
	if (upper(b, a)) return a;
	for (int i = LOG; i >= 0; i--) {
		if (!upper(b, d[a][i])) {
			a = d[a][i];
		}
	}
	return d[a][0];
}


int main() {
	ll n, m;
	cin >> n >> m;
	vv.resize(n + 1);
	for (int i = 0; i < n - 1; i++) {
		int from;
		cin >> from;
		vv[from].push_back(i + 1);
	}
	dfs(0, 0);
	cin >> a[1] >> a[2];
	ll x, y, z;
	cin >> x >> y >> z;
	for (int i = 3; i <= 2 * m; i++) {
		a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;
	}
	ll ans = 0;
	ll u = 0;
	for (int i = 1; i <= m; i++) {
		u = lca((a[2 * i - 1] + u) % n, a[2 * i]);
		ans += u;
	}
	cout << ans;

	return 0;
}
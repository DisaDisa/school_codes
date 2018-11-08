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
ifstream cin ("oil.in");
ofstream cout("oil.out");
#endif


struct str {
	int from, to, w;
	bool operator < (const str x) const {
		if(w < x.w)
			return true;
		return false;
	}
};

vector <str> s;


const int maxx = 20000;

int parent[maxx + 2], size[maxx + 2];


int find_set(int v) {
	if(v == parent[v])
		return v;
	return parent[v] = find_set(parent[v]);
}

void make_set (int v) {
	parent[v] = v;
	size[v] = 1;
}

int ans = 0;


void union_set (int a,int b, int w) {
	a = find_set(a);
	b = find_set(b);
	if(a != b) {
		if(size[a] < size[b])
			swap(a, b);
		parent[b] = a;
		size[a] += size[b];
		ans = max(w, ans);
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		str q;
		q.from = x;
		q.to = y;
		q.w = z;
		s.push_back(q);
		q.from = y;
		q.to = x;
		s.push_back(q);
	}
	for(int i = 1; i <= n; i++) {
		make_set(i);
	}
	sort(s.begin(), s.end());
	for(int i = 0; i < s.size(); i++) {
		union_set(s[i].from, s[i].to, s[i].w);
	}
	cout << ans;

    return 0;
}
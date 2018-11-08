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
ifstream cin ("segment-tree.in");
ofstream cout("segment-tree.out");
#endif

const int maxx = 100000;

struct str {
	int  key, l, r, add;
};

str d[maxx * 4 + 3];

int a[maxx + 3], n;

void push(int i) {
	if(d[i].l + 1 != d[i].r) {
		d[i * 2].add += d[i].add;
		d[i * 2 + 1].add += d[i].add; 
	}
	d[i].key += d[i].add;
	d[i].add = 0;
}

void build (int i , int l, int r) {
	d[i].l = l;
	d[i].r = r;
	if(r - l == 1) {
		d[i].key = a[l];
		return ;
	}
	int m = (l + r) / 2;
	build(i * 2, l, m);
	build(i * 2 + 1, m, r);
	d[i].key = max(d[i * 2].key, d[i * 2 + 1].key);
}

ll get(int i, int l, int r, int x) {
	push(i);
	if(d[i].r <= l || d[i].l >= r) {
		return -(maxx + 2);
	}
	if(d[i].l >= l && d[i].r <= r) {
		return d[i].key;
	}
	ll ans1, ans2;
	ans1 = get(i * 2, l, r, x);
	ans2 = get(i * 2 + 1, l, r, x);
	return max(ans1, ans2);
}

void update (int i, int l, int r, int x) {
	push(i);
	if(d[i].r <= l || d[i].l >= r) {
		return ;
	}
	if(d[i].l >= l && d[i].r <= r) {
		d[i].add += x;
		return ;
	}
	update(i * 2, l, r , x);
	update(i * 2 + 1, l, r, x);
	d[i].key = max(d[i * 2].add + d[i * 2].key, d[i * 2 + 1].add + d[i * 2 + 1].key);
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	build(1, 1, n + 1);
	int k;
	cin >> k;
	for(int i = 0; i < k; i++) {
		char c;
		cin >> c;
		if(c == 'g') {
			int x;
			cin >> x;
			cout << get(1, x, x + 1, 0) << '\n';
		}else{
			int x, y, z;
			cin >> x >> y >> z;
			update(1, x, y + 1, z);
		}
	}


    return 0;
}
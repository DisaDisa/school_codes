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
ifstream cin ("input.txt");
ofstream cout("output.txt");
#else
ifstream cin ("bracelet.in");
ofstream cout("bracelet.out");
#endif

ll P = 137;

const int maxx = 100000;

const ll M = 1000000007;

struct str {
	int l, r;
	ll key, add;
};

ll p[maxx + 3];


str d[maxx * 4 + 3];

char a[maxx + 3];
int n;

void build (int i , int l, int r) {
	d[i].l = l;
	d[i].r = r;
	if(r - l == 1) {
		d[i].key = a[l];
		return;
	}
	int m = (l + r) / 2;
	build(i * 2, l, m);
	build(i * 2 + 1, m, r);
	int size = d[i * 2 + 1].r - d[i * 2 + 1].l;
	d[i].key = ((d[i * 2].key * p[size]) % M
	+ d[i * 2 + 1].key) % M;
}

ll get(int i, int l, int r) {
	if(d[i].r <= l || d[i].l >= r) {
		return 0;
	}
	if(d[i].l >= l && d[i].r <= r) {
		return d[i].key;
	}
	ll ans1, ans2;
	ans1 = get(i * 2, l, r);
	ans2 = get(i * 2 + 1, l, r);
	int size = min(r, d[i * 2 + 1].r) - d[i * 2 + 1].l;
	size = max(size, 0);
	return ((ans1 * p[size]) % M
		+ ans2) % M;
}

void update (int i, int l, int r, int x) {
	if(d[i].r <= l || d[i].l >= r) {
		return;
	}
	if(d[i].l >= l && d[i].r <= r) {
		d[i].key = x;
		return;
	}
	update(i * 2, l, r , x);
	update(i * 2 + 1, l, r, x);
	int size = d[i * 2 + 1].r - d[i * 2 + 1].l;
	d[i].key = ((d[i * 2].key * p[size]) % M
		+ d[i * 2 + 1].key) % M;
}


int main() {
	int m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	p[0] = 1;
	for (int i = 1; i <= n + 1; i++) {
		p[i] = (p[i - 1] * P) % M;
	}
	build(1, 1, n + 1);
	for(int i = 0; i < m; i++) {
		char question;
		cin >> question;
		if(question == '*') {
			int index;
			char f;
			cin >> index >> f;
			update(1, index, index + 1, f);
		}
		if(question == '?') {
			int from1, from2, len;
			cin >> from1 >> from2 >> len;
			ll ans1 = get(1, from1, from1 + len);
			ll ans2 = get(1, from2, from2 + len);
			if(ans1 == ans2) {
				cout << '+';
			} else {
				cout << '-';
			}
		}
	}

    return 0;
}
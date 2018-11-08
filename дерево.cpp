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
ifstream cin ("rvq.in");
ofstream cout("rvq.out");
#endif

const int maxx = 100000;

struct str {
	int  max, min, l, r;
};

struct answer {
	int max, min;
};


str d[maxx * 4 + 3];

int a[maxx + 3];

void build (int i , int l, int r) {
	d[i].l = l;
	d[i].r = r;
	if(r - l == 1) {
		d[i].max = d[i].min = a[l];
		return ;
	}
	int m = (l + r) / 2;
	build(i * 2, l, m);
	build(i * 2 + 1, m, r);
	d[i].max = max(d[i * 2].max, d[i * 2 + 1].max);
	d[i].min = min(d[i * 2].min, d[i * 2 + 1].min);
}

answer get(int i, int l, int r) {
	//cout << i << ' ' << l << ' ' << r << ' ' << d[i].l << ' ' << d[i].r << '\n';
	if(d[i].r <= l || d[i].l >= r) {
		answer ans;
		ans.max = -1 * (maxx + 1);
		ans.min = maxx + 1;
		//cout << ans.max << ' ' << ans.min << '\n';
		return ans;
	}
	if(d[i].l >= l && d[i].r <= r) {
		answer ans;
		ans.max = d[i].max;
		ans.min = d[i].min;
		//cout << ans.max << ' ' << ans.min << '\n';
		return ans;
	}
	answer ans1, ans2, ans3;
	ans1 = get(i * 2, l, r);
	ans2 = get(i * 2 + 1, l, r);
	ans3.max = max(ans2.max, ans1.max);
	ans3.min = min(ans2.min, ans1.min);
	//cout << ans3.max << ' ' << ans3.min << '\n';
	return ans3;
}

void update (int i, int x, int y) {
	//cout << i << ' ' << d[i].l << ' ' << d[i].r << '\n';
	if(d[i].l + 1 == d[i].r) {
		d[i].max = y;
		d[i].min = y;
		//cout << y << '\n';
		return ;
	}
	int m = (d[i].l + d[i].r) / 2;
	if(x < m)
		update(i * 2, x, y);
	else
		update(i * 2 + 1, x, y);
	d[i].max = max(d[i * 2].max, d[i * 2 + 1].max);
	d[i].min = min(d[i * 2].min, d[i * 2 + 1].min);
	//cout << d[i].max << ' ' << d[i].min << '\n';
}
int main() {
	const int div1 = 12345, div2 = 23456;
	int k;
	cin >> k;
	for(ll i = 1; i <= maxx; i++) {
		a[i] = ((i % div1) * (i % div1)) % div1 + ((i % div2 * i % div2) % div2 * (i % div2)) % div2;
	}
	build(1, 1, maxx + 1);
	for(int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		if(x > 0) {
			answer ans;
			ans = get(1, x, y + 1);
			cout << ans.max - ans.min << '\n';
		}else{
			update(1, -x, y);
		}
	}


    return 0;
}
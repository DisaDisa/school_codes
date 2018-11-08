#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <stack>
#include <queue>
#include <iomanip>
#include <cmath>
#include <map>

using namespace std;

int n, m, u, v, ans, lastU, lastV;
vector <int> nlog;
vector <vector <int> > a;

void calcLog () {
	int l = -1, s = 1;
	for (int i = 1; i <= n; i++) {
		if (s <= i) {
			l++;
			s *= 2;
		}
		nlog[i] = l;
	}
}

int power (int k) {
	int res = 1;
	for (int i = 1; i <= k; i++) {
		res *= 2;
	}
	return res;
}

int main () {
	//freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
	freopen("sparse.in", "r", stdin);freopen("sparse.out", "w", stdout);
	cin >> n >> m;
	nlog.resize(n + 1);
	calcLog();
	a.resize(nlog[n] + 1, vector <int> (n + 1));
	cin >> a[0][1];
	for (int i = 2; i <= n; i++) {
		a[0][i] = (a[0][i - 1] * 23 + 21563) % 16714589;
		//cin >> a[0][i];
	}
	for (int j = 1; j <= nlog[n]; j++) {
		int pow = power(j - 1);
		for (int i = 1; i <= n; i++) {
			if (i + pow > n) {
				break;
			}
			a[j][i] = min(a[j - 1][i], a[j - 1][i + pow]);
		}
	}
	cin >> u >> v;
	if (u > v) {
		swap(u, v); 
	}
	for (int i = 1; i <= m; i++) {
		int pow = nlog[max(v, u) - min(v, u) + 1];
		ans = min(a[pow][min(v, u)], a[pow][max(v, u) - power(pow) + 1]);
		//cout << u << " " << v << " " << ans <<endl;
		lastV = v;
		lastU = u;
		u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
		v = ((13 * v + 593 + ans + 5 * i) % n) + 1;		
		
	}
	cout << lastU << ' ' << lastV << ' ' << ans;
	return 0;
}
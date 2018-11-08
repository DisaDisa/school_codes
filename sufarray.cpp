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

const int maxx = 100002;
                                                         
int lcp[maxx], c[maxx], p[maxx], h[maxx], c2[maxx];
int cnt[maxx], np[maxx], rev[maxx];

int main() { 
#if _DEBUG
	ifstream cin("input.txt");
	ofstream cout("output.txt");
#else
	ifstream cin("kthsubstr.in");
	ofstream cout("kthsubstr.out");
#endif
	string s;
	ll need;
	cin >> s >> need;
	int n = (int)s.size();
	for(int i = 0; i < n; i++) {
		c[i] = s[i];
	}
	n++;
	int classcount = 256;
	for(int k = 1; k <= n; k *= 2) {
		fill(cnt, cnt + classcount, 0);
		for(int i = 0; i < n; i++)  {
			cnt[c[i]]++;
		}
		h[0] = 0;
		for(int i = 1; i <= classcount; i++) {
			h[i] = h[i - 1] + cnt[i - 1];
		}
		for(int i = 0; i < n; i++) {
			int d = c[(i + k) % n];
			p[h[d]] = i;
			h[d]++;
		}
		h[0] = 0;
		for(int i = 1; i <= classcount; i++) {
			h[i] = h[i - 1] + cnt[i - 1];
		}
		for(int i = 0; i < n; i++) {
			int d = c[(p[i] + k) % n];
			np[h[d]] = p[i];
			h[d]++;
		}
		c2[np[0]] = 0;
		for(int i = 1; i < n; i++) {
			if(c[np[i]] == c[np[i - 1]] 
			&& c[(np[i] + k) % n] == c[(np[i - 1] + k) % n])
				c2[np[i]] = c2[np[i - 1]];
			else
				c2[np[i]] = c2[np[i - 1]] + 1;
		}
		classcount = c2[np[n - 1]] + 1;
		for(int i = 0; i < n; i++) {
			c[i] = c2[i];
		}
	}
	for(int i = 0; i < n; i++) {
		cout << np[i] << ' ';
	}
	return 0;
	for(int i = 0; i < n; i++) {
		rev[np[i]] = i;
	}
	int k1 = 0;
	for(int i = 0; i < n; i++) {
		int t = rev[i] + 1;
		if(t >= n) {
			k1 = 0;
			continue;
		}
		int j = np[t];
		k1 = max(k1 - 1, 0);
		while(s[i + k1] == s[j + k1])
			k1++;
		lcp[rev[i] + 1] = k1;
	}
	ll now = 0;
	for(int i = 0; i < n; i++) {
		now += n - np[i] - lcp[i];
		if(now >= need) {
			for(int j = np[i]; j < n - (now - need); j++) {
				cout << s[j];
			}
			return 0;
		}
	}
	for(int i = np[n - 1]; i < n; i++) {
		cout << s[i];
	}
	return 0;
}
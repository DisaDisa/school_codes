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
ifstream cin ("unionday.in");
ofstream cout("unionday.out");
#endif

const int maxx = 5002;

const int INF = 2000000000;

double ans = 0;

struct str {
	int x, y;
	double key;
};


vector <str> s;

int n;

bool used[maxx];

double way (str x, str y) {
	return sqrt (double((y.x - x.x) * (y.x - x.x) + (y.y - x.y) * (y.y - x.y)));
}

void prima (int v) {
	for(int j = 0; j < n; j++) {
		int u = -1;
		for(int i = 0; i < n; i++) {
			if(!used[i] && (u == -1 || s[i].key < s[u].key )) {
				u = i;
			}
		}
		used[u] = true;
		ans += s[u].key;
		for(int i = 0; i < s.size(); i++) {
			double cost = way(s[u], s[i]);
			if(!used[i] && s[i].key > cost) {
				s[i].key = cost;
			}
		}
	}
}

int main() {
	cin >> n;
	for(int i = 0 ; i < n; i++) {
		int x, y;
		cin >> x >> y;
		str q;
		q.x = x;
		q.y = y;
		s.push_back(q);
	}
	for(int i = 1; i < s.size(); i++) {
		s[i].key = INF;
	}
	s[0].key = 0;
	prima(0);
	cout << fixed << setprecision(15) << ans;



		

    return 0;
}
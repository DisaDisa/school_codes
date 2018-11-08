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
#include <time.h>
using namespace std;
#pragma comment (linker, "/STACK:64000000")

typedef long long ll;

#if _DEBUG 
ifstream cin ("input.txt");
ofstream cout("output.txt");
#else
ifstream cin ("interview.in");
ofstream cout("interview.out");
#endif

int ans[2][10001];

int a[10001], b[10001];

int main() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1; i <= m; i++) {
		cin >> b[i];
	}
	int k;
	for(int i = 1; i <= n; i++) {
		k = 0;
		for(int j = 1; j <= m; j++) {
			if(b[j] < a[i] && ans[(i - 1) % 2][k] < ans[(i - 1) % 2][j])
				k = j;
			if(a[i] != b[j]) {
				ans[i % 2][j] = ans[(i - 1)% 2][j];
			}else{
				ans[i % 2][j] = ans[(i - 1) % 2][k] + 1;
			}
		}
	}
	int maxx = 0;
	for(int i = 1; i <= m; i++) {
		maxx = max(maxx, ans[n % 2][i]);
	}
	cout << maxx;



    return 0;
}
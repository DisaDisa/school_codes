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
int cmp(double, double); 
#if _DEBUG 
ifstream cin ("input.txt");
ofstream cout("output.txt");
#else
ifstream cin ("z-function.in");
ofstream cout("z-function.out");
#endif

int z[1000002];


int main() {
	string s;
	cin >> s;
	s = '!' + s;
	z[1] = 0;
	int x = 0;
	int maxx = 0;
	for(int  i = 2; i < s.size(); i++) {
		int j = i - x + 1;
		if(i >= x + z[x])
			z[i] = 0;
		else
			z[i] = min(z[j], x + z[x] - i);
		while(i + z[i] < s.size() && s[i + z[i]] == s[z[i] + 1])
			z[i]++;
		if(z[i] + i - 1 > maxx) {
			maxx = z[i] + i - 1;
			x = i;
		}
	}
	cout << s.size() - 1 << ' ';
	for(int i = 2; i < s.size(); i++) {
		cout << z[i] << ' ';
	}




    return 0;
}
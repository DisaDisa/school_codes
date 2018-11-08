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
ifstream cin ("prefix-function.in");
ofstream cout("prefix-function.out");
#endif

int p[1000002];

int main() {
	string s;
	cin >> s;
	p[0] = 0;
	for(int i = 1; i < s.size(); i++) {
		if(s[p[i - 1]] == s[i]) {
			if(p[i - 1] != i)
				p[i] = p[i - 1] + 1;
		}else{
			int j = p[i - 1];
			while(j != p[j - 1] && s[j] != s[i])
				j = p[j - 1];
			if(j != i && s[j] == s[i])
				p[i] = j + 1;
		}
	}
	for(int i = 0; i < s.size(); i++) {
		cout << p[i] << ' ';
	}


    return 0;
}
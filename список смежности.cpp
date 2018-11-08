#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;
ifstream cin ("collect.in");
ofstream cout("collect.out");
int he[100000],to[100000],ne[100000], cnt, deg[100000];
void add_edge(int q, int w) {
	ne[cnt] = he[q];
	to[cnt] = w;
	he[q] = cnt;
	cnt++;
}
int main() {
	int n , m;
	cin >> n >> m;
	fill_n(he, n, -1);
	for(int i = 0; i < m; i++) {
		int q, w;
		cin >> q >> w;
		deg[q - 1]++;
		add_edge(q - 1, w - 1);
	}
	for(int i = 0; i < n; i++) {
		int j=he[i];
		cout << deg[i] << '\n';
		while(j != -1) {
			cout << to[j] + 1 << ' ';
			j=ne[j];
		}
		cout << '\n';
	}
	return 0;
}

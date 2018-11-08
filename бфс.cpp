#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;
ifstream cin("bfs.in");
ofstream cout("bfs.out");
int d[103], q, n , s, f, e, a[103][103], r[100004];

void push (int v) {
	r[q]=v;
	q++;
}

void pop () {
	e++;
}

void bfs(int v) {
	d[v]=0;
	push(v);
	while (q > e){
		v = r[e];
		pop();
		for ( int i = 0; i < n; i++) {
			if(a[v][i] == 1) {
				if(d[i] == -1) {
					d[i] = d[v] + 1;
					push(i);
				}
			}
		}
	}
}

int main() {
	cin >> n >> s >> f;
	q = 0;
	e = 0;
	fill_n(d, n, -1);
	for(int i = 0; i < n; i++) {
		for ( int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	bfs(f - 1);
	if (d[s - 1] == -1)
		cout << 0;
	else
		cout << d[s - 1];
	return 0;
}

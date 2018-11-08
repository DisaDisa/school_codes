#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;
ifstream cin ("components.in");
ofstream cout("components.out");
int color[103],a[103][103],n,ans;
void dfs(int v) {
	color[v] = 1;
	for(int i = 0; i < n; i++) {
		if(color[i] == 0 && a[v][i] == 1)
			dfs(i);
	}
	color[v] = 2;
}
int main() {
	int i, j;
	cin >> n;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			cin >> a[i][j];
		}
	}
	for(i = 0; i < n; i++){
		if(color[i] == 0){
			dfs(i);
			ans++;
		}
	}
	cout << ans;
	return 0;
}

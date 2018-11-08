#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int K = 444;

int tn;
vector<long long> sum;
vector<int> a;
vector<int> b;

int main() {
  freopen("sum.in", "r", stdin);
  freopen("sum.out", "w", stdout);
  int n, m;
  cin >> n >> m;
  a.assign(n, 0);
  b.assign(n, 0);
  for (int i = 0; i < n; i++) b[i] = i / K;
  sum.assign(n / K + 1, 0);
  for (int i = 0; i < m; i++) {
    char c;
    cin >> c;
    if (c == 'A') {
      int id, x;
      cin >> id >> x;
      --id;
      a[id] = x;
      int block = b[id];
      sum[block] = 0;
      for (int j = block * K; j < n && b[j] == block; j++) sum[block] += a[j];
    } else {
      int l, r;
      cin >> l >> r;
      --l;
      --r;
      long long ans = 0;
      int b1 = b[l];
      int b2 = b[r];
      if (b1 == b2) {
        while (l <= r) ans += a[l++];
      } else {
        while (b[l] == b1) ans += a[l++];
        while (b[r] == b2) ans += a[r--];
        for (int j = b1 + 1; j < b2; j++) ans += sum[j];
      }
      cout << ans << '\n';
    }
  }
}
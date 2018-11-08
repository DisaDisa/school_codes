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
ifstream cin ("convex.in");
ofstream cout("convex.out");
#endif

const double EPS = 1e-9;

struct Point_ind {
	int x, y, i;
	Point_ind(int x, int y, int i) : x(x), y(y), i(i) {}
	Point_ind () {}
};

struct Point {
	double x, y;
	Point () {}
	Point(double x, double y) : x(x), y(y) {}
	bool operator == (Point p1) {
		if(cmp(p1.x, x) == 0 && cmp(p1.y, y) == 0)
			return true;
		return false;
	}

};

struct Vector {
	int x, y;
	Vector() {}
	Vector(int x, int y) : x(x), y(y) {}
	Vector(Point_ind p1, Point_ind p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}
	Vector operator * (int b) {
		return Vector(x * b, y * b);
	}
	Vector operator - (Vector v2) {
		return Vector(x - v2.x, y - v2.y);
	}
	Vector operator + (Vector v2) {
		return Vector(x + v2.x, y + v2.y);
	}
};

Point operator + (Point p, Vector a) {
	return Point(a.x + p.x, a.y + p.y);
}


struct line {
	double a, b, c;
	line(double a, double b, double c) : a(a), b(b), c(c) {}
	line() {}
};

double vectorlength(Vector a) {
	double dis = sqrt ((double) a.x * a.x + (double) a.y *a.y);
	return dis;
}

double dotproduct(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y;
}

ll crossproduct(Vector a, Vector b) {
	return (ll) a.x * b.y - (ll) a.y * b.x;
}


int cmp(double x, double y) {
	if(fabs(x - y) < EPS)
		return 0;
	if(x < y)
		return -1;
	return 1;
}

Point intersect(line l1, line l2) {
	double x, y, z;
	z = l1.a * l2.b - l2.a * l1.b;
	if (cmp(z, 0) == 0) 
	x = (-l1.c * l2.b - l1.b * -l2.c) / z;
	y = (-l2.c * l1.a - l2.a * -l1.c) / z;
	return Point(x, y);
}

Point_ind a[200001];

Point_ind from;

bool operator < (Point_ind y, Point_ind z) {
	Vector a = Vector(from, y);
	Vector b = Vector(from, z);
	ll p = crossproduct(a, b);
	if (p > 0) {
		return true;
	}
	if (p == 0) {
		return vectorlength(a) < vectorlength(b);
	}
	return false;
}

bool check(Vector a, Vector b) {
	if (crossproduct(a, b) > 0)
		return true;
	return false;
}


Point_ind ans[200001];

int cnt = 0;

void push(Point_ind x) {
	ans[cnt].x = x.x;
	ans[cnt].y = x.y;
	ans[cnt].i = x.i;
	cnt++;
}

void pop() {
	cnt--;
}

int main() {
	int n;
	cin >> n;
	const int maxx = 1000000002;
	from = Point_ind(maxx, maxx, 0);
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
		a[i].i = i;
		if (a[i].y < from.y || (a[i].y == from.y && a[i].x < from.x))
			from = a[i];
	}
	sort(a, a + n);
	push(a[0]);
	push(a[1]);
	for(int i = 2; i < n; i++) {
		Vector now = Vector(ans[cnt - 2], ans[cnt - 1]);
		Vector next = Vector(ans[cnt - 1], a[i]);
		while(!check(now, next)) {
			pop();
			if(cnt - 2 < 0)
				break;
			now = Vector(ans[cnt - 2], ans[cnt - 1]);
			next = Vector(ans[cnt - 1], a[i]);
		}
		push(a[i]);
	}
	cout << cnt << '\n';
	long double per = 0;
	ll area = 0;
	for(int i = 0; i < cnt; i++) {
		cout << ans[i].i  + 1 << ' ';
	}
	for(int i = 0; i < cnt - 1; i++) {
		area += abs(crossproduct(Vector(ans[0], ans[i]), Vector(ans[0], ans[i + 1])));
		per += vectorlength(Vector(ans[i], ans[i + 1]));
	}
	per += vectorlength(Vector(ans[cnt - 1], ans[0]));
	cout << fixed << setprecision(15) <<'\n';
	cout << per << '\n';
	cout << area / 2;
	if(area % 2 == 1) 
		cout << ".5";



    return 0;
}
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
ifstream cin ("piglet.in");
ofstream cout("piglet.out");
#endif

const double EPS = 1e-9;

const double PI = acos(-1.0);


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
	double x, y;
	Vector() {}
	Vector(double x, double y) : x(x), y(y) {}
	Vector(Point p1, Point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}
	
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

struct Circle {
	Point c;
	int r;
	Circle() {}
	Circle(Point c, int r) : c(c), r(r) {}
};

struct Triangle {
	Point a, b, c;
	Triangle () {}
	Triangle (Point a, Point b, Point c) : a(a), b(b), c(c) {}
};



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

double crossproduct(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}


int cmp(double x, double y) {
	if(fabs(x - y) < EPS)
		return 0;
	if(x < y)
		return -1;
	return 1;
}


double distance(Point p, Point p1, Point p2) {
	Vector v1 = Vector(p1, p);
	Vector v2 = Vector(p1, p2);
	Vector v3 = Vector(p2, p);
	Vector v4 = Vector(p2, p1);
	double minn = 0;
	if (cmp(dotproduct(v1, v2), 0) < 0 || cmp(dotproduct(v3, v4), 0) < 0) {
		minn = min(vectorlength(v1), vectorlength(v3));
	} else {
		if (p1 == p2) {
			minn = vectorlength(Vector(p, p1));
		} else {
			minn = fabs(crossproduct(v1, v3)) / vectorlength(Vector(p1, p2));
		}
	}
	return minn;
}

pair<Point, Point> ans(Point from, Circle circle) {
	Vector op = Vector(from, circle.c);
	double p1p_dis = sqrt(vectorlength(op) * vectorlength(op) - circle.r * circle.r);
	double pm_dis = p1p_dis * p1p_dis / vectorlength(op);
	Vector pm = Vector(op.x / vectorlength(op) * pm_dis, op.y / vectorlength(op) *pm_dis);	
	Point m = from + pm;
	Vector n1, n2;
	n1 = Vector(op.y, -op.x);
	n2 = Vector(-op.y, op.x);
	double mp1_dis = sqrt(circle.r * circle.r - vectorlength(Vector(m ,circle.c)) * vectorlength(Vector(m ,circle.c)));
	Vector mp1 = Vector(n1.x / vectorlength(n1) * mp1_dis, n1.y / vectorlength(n1) * mp1_dis);
	Vector mp2 = Vector(n2.x / vectorlength(n2) * mp1_dis, n2.y / vectorlength(n2) * mp1_dis);
	Point m1 = m + mp1;
	Point m2 = m + mp2;
	return make_pair(m1, m2);
}


int main() {
	Point from, to;
	Circle circle;
	cin >> from.x >> from.y >> to.x >> to.y;
	cin >> circle.c.x >> circle.c.y >> circle.r;
	cout << fixed << setprecision(15);

	if (cmp(distance(circle.c, from, to), circle.r) >= 0) {
		cout << vectorlength(Vector(from, to));
		return 0;
	}

	pair <Point, Point> q = ans(from, circle);
	pair <Point, Point> q2 = ans(to, circle);
	double ans = 1e100;
	for (auto i = q.first; ; i = q.second) {
		for (auto j = q2.first; ; j = q2.second) {
			Vector v1(circle.c, i);
			Vector v2(circle.c, j);
			double x = fabs(circle.r * atan2(crossproduct(v1, v2), dotproduct(v1, v2)));
			ans = min(ans, x + vectorlength(Vector(i, from)) + vectorlength(Vector(j, to)));
			if (j == q2.second) break;
		}
		if (i == q.second) break;
	}
	cout << ans << "\n";
    return 0;
}
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

typedef long long ll;

const double EPS = 1e-9;

struct Point
{
	double x, y;
	Point () {}
	Point(double x, double y) : x(x), y(y) {}
};

struct Vector
{
	double x, y;
	Vector () {}
	Vector (Point p1, Point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}
	Vector (double x, double y): x(x), y(y) {}
};


#if _DEBUG 
	ifstream cin("input.txt");
	ofstream cout("output.txt");
#else
	ifstream cin("circles.in");
	ofstream cout("circles.out");
#endif


double vector_length(Vector v) {
	return sqrt((double) v.x * v.x + v.y * v.y);
}

Point read_point () {
	Point p;
	cin >> p.x >> p.y;
	return p;
}

void print_point (Point p) {
	cout << p.x << ' ' << p.y;
}

struct segment {
	Point p1, p2;
	segment () {}
	segment (Point p1, Point p2) : p1(p1), p2(p2) {}
};

segment read_segment() {
	Point p1, p2;
	p1 = read_point();
	p2 = read_point();
	return segment(p1, p2);
}



double dis_point_point(Point p1, Point p2) {
	return sqrt((double)(p2.x - p1.x) * (p2.x - p1.x)
		+ (p2.y - p1.y) * (p2.y - p1.y));
}

struct Circle {
	Point p;
	int r;
	Circle () {}
	Circle(Point p, int r): p(p), r(r) {}
};

Circle read_circle() {
	Point p = read_point();
	int r;
	cin >> r;
	return Circle(p, r);
}


int main() {
	int n;
	cin >> n;
	cout << fixed << setprecision(15);
	for(int i = 0; i < n; i++) {
		Circle c1 = read_circle();
		Circle c2 = read_circle();
		if(c1.p.x == c2.p.x && c1.p.y == c2.p.y && c1.r == c2.r) {
			cout << "I can't count them - too many points :(\n\n";
			continue;
		}
		if(c1.r + c2.r - dis_point_point(c1.p, c2.p) < -EPS ||
			c1.r > dis_point_point(c1.p, c2.p) + c2.r ||
			c2.r > dis_point_point(c1.p, c2.p) + c1.r ) {
			cout << "There are no points!!!\n\n";
			continue;
		}
		double dis_c_c = dis_point_point(c1.p, c2.p);
		double dis_o_m = ((double)c1.r * c1.r + dis_c_c * dis_c_c - c2.r * c2.r) / (2 * dis_c_c);
		Vector v_o_o = Vector(c1.p, c2.p);
		Vector v_o_m;
		double dis_o_o = vector_length(v_o_o);
		v_o_m.x = v_o_o.x / dis_o_o * dis_o_m;
		v_o_m.y = v_o_o.y / dis_o_o * dis_o_m;
		Point m = Point(c1.p.x + v_o_m.x, c1.p.y + v_o_m.y);
		Vector v1 = Vector(-v_o_o.y, v_o_o.x); 
		Vector v2 = Vector(v_o_o.y, -v_o_o.x);
		double dis_p_m = sqrt(c1.r * c1.r - dis_o_m * dis_o_m);
		double dis_v1 = vector_length(v1), dis_v2 = vector_length(v2);
		v1.x = v1.x / dis_v1 * dis_p_m;
		v1.y = v1.y / dis_v1 * dis_p_m;
		v2.x = v2.x / dis_v2 * dis_p_m;
		v2.y = v2.y / dis_v2 * dis_p_m;
		Point p1 = Point(m.x + v1.x, m.y + v1.y);
		Point p2 = Point(m.x + v2.x, m.y + v2.y);
		if(p1.x > p2.x) {
			swap(p1, p2);
		} 
		if(p1.x == p2.x && p1.y > p2.y)
			swap(p1, p2);
		if(vector_length(v1) <= EPS && vector_length(v2) <= EPS) {
			cout << "There are only 1 of them....\n";
			print_point(p1);
			cout << "\n\n";
			continue;
		}
		cout << "There are only 2 of them....\n";
		print_point(p1);
		cout << "\n";
		print_point(p2);
		cout << "\n\n";
	}

	return 0;
}
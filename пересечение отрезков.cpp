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

struct Point
{
	int x, y;
	Point () {}
	Point(int x, int y) : x(x), y(y) {}
};

struct Vector
{
	int x, y;
	Vector () {}
	Vector (Point p1, Point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}
};

int crossproduct(Vector v1, Vector v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

#if _DEBUG 
	ifstream cin("input.txt");
	ofstream cout("output.txt");
#else
	ifstream cin("distance2.in");
	ofstream cout("distance2.out");
#endif

Point read_point ()
{
	Point p;
	cin >> p.x >> p.y;
	return p;
}

void print_point (Point p)
{
	cout << p.x << ' ' << p.y;
}

struct segment
{
	Point p1, p2;
	segment () {}
	segment (Point p1, Point p2) : p1(p1), p2(p2) {}
};

segment read_segment() 
{
	Point p1, p2;
	p1 = read_point();
	p2 = read_point();
	return segment(p1, p2);
}

bool left_right(segment s1, segment s2)
{
	Vector v1 = Vector(s1.p1, s1.p2);
	Vector v2 = Vector(s1.p1, s2.p1);
	bool first = crossproduct (v1, v2) > 0;
	Vector v3 = Vector(s1.p1, s2.p2);
	bool second = crossproduct (v1, v3) > 0;
	if(first == second)
		return false;
	return true;
}

bool cross_segment(segment s1, segment s2) 
{
	return left_right(s1, s2) && left_right(s2, s1);
}

double dis_point_point(Point p1, Point p2)
{
	return sqrt((double)(p2.x - p1.x) * (p2.x - p1.x)
		+ (p2.y - p1.y) * (p2.y - p1.y));
}

struct line 
{
	int a, b, c;
	line() {}
	line(Point p1, Point p2) {
		a = p2.y - p1.y;
		b = p1.x - p2.x;
		c = -a * p1.x - b * p1.y;
	}
};

double dis_point_line(Point p, line l)
{
	return fabs((double)l.a * p.x + l.b * p.y + l.c)
		/ sqrt((double)l.a * l.a + l.b * l.b);
}

double dis_point_segment(Point p, segment s)
{
	double c = dis_point_point(s.p1, s.p2);
	double a = dis_point_point(p, s.p1);
2	double b = dis_point_point(p, s.p2);
	if(a * a + c * c < b * b)
		return a;
	if(b * b + c * c < a * a) 
		return b;
	line l = line(s.p1, s.p2);
	return dis_point_line(p, l);
}




int main()
{
	segment s1 = read_segment();
	segment s2 = read_segment();
	if(cross_segment(s1, s2))
	{
		cout << 0;
		return 0;
	}
	double ans = 1000000000000000000;
	ans = min(dis_point_segment(s1.p1, s2), dis_point_segment(s1.p2, s2));
	ans = min(ans, dis_point_segment(s2.p1, s1));
	ans = min(ans, dis_point_segment(s2.p2, s1));
	cout << fixed << setprecision(17) << ans;
	return 0;
}
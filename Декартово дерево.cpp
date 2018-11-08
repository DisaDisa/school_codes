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
#include <time.h>
using namespace std;
#pragma comment (linker, "/STACK:64000000")

typedef long long ll;

#if _DEBUG 
ifstream cin ("input.txt");
ofstream cout("output.txt");
#else
ifstream cin ("bst2.in");
ofstream cout("bst2.out");
#endif


struct treap {
	int x, y, size;
	treap *l;
	treap *r;
	treap (int a) {
		x = a;
		y = rand();
		size = 0;
		l = r = NULL;
	}
};

typedef treap* pt;

int getsize(pt p) {
	if(p != NULL)
		return p ->size;
	return 0;
}

void recalc(pt p) {
	if(p != NULL) {
		p->size = getsize(p->l) + getsize(p->r) + 1;
	}
}

pt cur = NULL;
void kth(int k) {
	while(cur != NULL) {
		int ans = (cur->l == NULL ? 0 : cur->l->size);
		if(ans + 1 == k)
			break;
		else {
			if(k < ans + 1)
				cur = cur ->l;
			else {
				k -= ans + 1;
				cur = cur ->r;
			}
		}
	}
}


void merge(pt &t, pt pl, pt pr) {
	if (pl == NULL) {
		t = pr;
		recalc(t);
		return;
	}
	if (pr == NULL) {
		t = pl;
		recalc(t);
		return;
	}
	if (pl -> y >= pr -> y) {
		t = pl;
		merge(t -> r, pl -> r, pr);
	} else {
		t = pr;
		merge(t -> l, pl, pr -> l);
	}
	recalc(t);
}

void split(pt T,int x, pt &pl, pt &pr) {
	if (T == NULL) {
		pl = pr = NULL;
		recalc(T);
		return;
	}
	if (x >= T -> x) {
		pl = T;
		split(T -> r, x, pl -> r, pr);
	} else {
		pr = T;
		split(T -> l, x, pl, pr -> l );
	}
	recalc(T);
}


int main() {
	string s; 
	srand((int)time(0));
	pt root = NULL, tmp = NULL;
	while (cin >> s) { 
		int x;
		cin >> x;
		if(s == "insert") {
			pt p1, p2, p3, p4;
			pt new_elem = new treap(x);
			split(root, x, p1, p2);
			split(p1, x - 1, p3, p4);
			if (p4 != NULL) {
				merge(p1, p3, p4);
				merge(root, p1, p2);
			} else {
				merge(p1, p3, new_elem);
				merge(root, p1, p2);
			}
		}
		if (s == "delete") {
			pt p1, p2, p3, p4;
			split(root, x, p1, p2);
			split(p1, x - 1, p3, p4);
			merge(root, p3, p2);
		}
		if (s == "exists") {
			pt p1, p2, p3, p4;
			split(root, x, p1, p2);
			split(p1, x - 1, p3, p4);
			if (p4 != NULL)
				cout << "true" << '\n';
			else
				cout << "false" << '\n';
			merge(p1, p3, p4);
			merge(root, p1, p2);
		}
		if (s == "next") {
			pt p1, p2;
			split(root, x - 1, p1, p2);
			cur = p2;
			kth(1);
			if(cur == NULL)
				cout << "none" << '\n';
			else
				cout << cur->x << '\n';
			merge(root, p1, p2);
		}
		if(s == "prev") {  
			pt p1, p2;
			split(root, x - 1, p1, p2);
			cur = p1;
			kth(cur->size);
			if(cur == NULL)
				cout << "none" << '\n';
			else{
				cout << cur->x << '\n';
			}
			merge(root, p1, p2);
		}
		if(s == "kth") {  
			cur = root;
			kth(x);
			if(cur == NULL)
				cout << "none" << '\n';
			else
				cout << cur->x << '\n';
		}
	} 


    return 0;
}
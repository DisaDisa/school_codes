#include <iostream>
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
#include <ctype.h>   
 
 
using namespace std;
 
 
 
struct Node {
    Node *parent, *sufflink;
    Node *son[26], *go[26];
    char char_to_parent;
    bool leaf, used;
    vector <int> id;
 
    Node() {
        this->parent = nullptr;
        this->sufflink = nullptr;
        this->leaf = false;
        this->used = false;
        for (int i = 0; i < 26; i++) {
            son[i] = nullptr;
            go[i] = nullptr;
        }
    }
 
};
 
Node *root = new Node();
 
Node *get_link(Node *, char);
 
Node *get_sufflink(Node *v) {
    if (v->sufflink == nullptr) {
        if (v == root || v->parent == root) {
            v->sufflink = root;
        }
        else {
            v->sufflink = get_link(get_sufflink(v->parent), v->char_to_parent);
        }
    }
    return v->sufflink;
}
 
Node *get_link(Node *v, char c) {
    int c_id = c - 'a';
    if (v->go[c_id] == nullptr) {
        if (v->son[c_id]) {
            v->go[c_id] = v->son[c_id];
        }
        else if (v == root) {
            v->go[c_id] = root;
        }
        else {
            v->go[c_id] = get_link(get_sufflink(v), c);
        }
    }
    return v->go[c_id];
}
 
 
void add_string(Node *root, string &s, int id) {
    Node *cur = root;
    for (int i = 0; i < (int)s.size(); i++) {
        int c_id = s[i] - 'a';
        if (cur->son[c_id] == nullptr) {
            cur->son[c_id] = new Node();
            cur->son[c_id]->parent = cur;
            cur->son[c_id]->char_to_parent = char(c_id + 'a');
            cur->son[c_id]->leaf = false;
        }
        cur = cur->son[c_id];
    }
    cur->leaf = true;
    cur->id.push_back(id);
}
 
 
vector <string> ans;
 
void process_text(string &s) {
    Node *cur = root;
    for (int i = 0; i < (int)s.size(); i++) {
        cur = get_link(cur, s[i]);
        Node *now = cur;
        while (now != root && !now->used) {
            now->used = true;
            if (now->id.size() != 0) {
                for (auto j : now->id) {
                    ans[j] = "YES";
                }
            }
            now = get_sufflink(now);
        }
    }
}
 
 
 
 
int main() {
    freopen("search4.in", "r", stdin); freopen("search4.out", "w", stdout);
    int n;
    cin >> n;
    ans.resize(n, "NO");
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        add_string(root, s, i);
    }
    string s;
    cin >> s;
    process_text(s);
    for (auto i : ans) {
        cout << i << '\n';
    }
    //cin >> n;
    return 0;
}
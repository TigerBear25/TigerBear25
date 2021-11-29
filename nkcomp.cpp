#include<bits/stdc++.h>
#define FastIO ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define FOR(i,l,r) for(int i = l; i <= r; ++i)
#define FORD(i,l,r) for(int i = l; i >= r; --i)
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FORE(i, v) for(__typeof(v.begin()) i = v.begin(); i != v.end(); ++i)
#define ALL(v) v.begin(), v.end()
#define sz(v) (int)v.size()
#define fi first
#define se second
using namespace std;
using ii = pair<int, int>;

template<class X, class Y>
	bool minimize(X &x, const Y &y) {
		X eps = 1e-9;
		if(x > y + eps) {
			x = y;
			return true;
		}
		return false;
	}
template<class X, class Y>
	bool maximize(X &x, const Y &y) {
		X eps = 1e-9;
		if(x + eps < y) {
			x = y;
			return true;
		}
		return false;
	}
template<class T>
	T abs(const T &x){
		return (x < 0 ? -x : x);
	}
template <typename T>
	inline void read(T& x) {
	    bool Neg = false;	char c;
	    for (c = getchar(); c < '0' || c > '9'; c = getchar())
	        if (c == '-') Neg = true;

	    x = c - '0';
	    for (c = getchar(); c >= '0' && c <= '9'; c = getchar())
	        x = x * 10 + c - '0';
	    if (Neg) x = -x;
	}
template <typename T>
	inline void write(T x) {
	    if (x < 0) {
	        putchar('-'); 
	        x = -x;
	    }

	    T p = 1;
	    for (T temp = x / 10; temp > 0; temp /= 10) p *= 10;
	    for (; p > 0; x %= p, p /= 10) putchar(x / p + '0');
	}

/* Author: TigerBear(CQT_Trung) */

/** END OF TEMPLATE. CODE GOES HERE **/

struct FenTree {
	int n;
	vector<int> a, v;

	FenTree() {
		n = 0;
		a.clear();
		v.clear();
	}

	FenTree(vector<int> _a) {
		a = _a;	   n = sz(a);	
		v.assign(n + 4, 0);
	}

	void update(int x, int c) {
		for(; x <= n; x += x & -x) v[x] += c;
	}

	int get(int x) {
		int res = 0;
		x = lower_bound(ALL(a), x) - a.begin() + 1;
		for(; x; x -= x & -x) res += v[x];
		return res;
	}

	void update(int u, int v, int val) {
		u = lower_bound(ALL(a), u) - a.begin() + 1;
		v = upper_bound(ALL(a), v) - a.begin();

		if(u > v) return;
		update(u, val);		
		update(v + 1, -val);
	}
};

const int MAX = 1e5 + 9;
int n, m, cnt;
int high[MAX], fin[MAX], fout[MAX];
vector<int> adj[MAX], nodes[MAX];
FenTree BIT[MAX];

void load(){
	read(n);
	REP(i, n - 1) {
		int u, v;	read(u), read(v);
		adj[u].push_back(v);
	}
}

void dfs(int u) {
	fin[u] = ++cnt;
	nodes[high[u]].push_back(fin[u]);

	for(int v : adj[u]) {
		high[v] = high[u] + 1;
		dfs(v);
	} fout[u] = cnt;
}

void process(){
	dfs(1);
	REP(i, n) {
		if(nodes[i].empty()) break;
		BIT[i] = FenTree(nodes[i]);
	}

	read(m);
	while(m--) {
		int type;	read(type);
		if(type == 1) {
			int u, k, e;	read(u), read(k), read(e);
			k += high[u];	if(k >= n) continue;
			BIT[k].update(fin[u], fout[u], e);
		} else {
			int u;	read(u);
			printf("%d\n", BIT[high[u]].get(fin[u]));
		}
	}
}

int32_t main(){
	FastIO;
	load();
	process();
	return 0;
}

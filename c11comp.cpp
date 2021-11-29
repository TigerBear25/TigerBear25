/*--------------------------------
Coder: TigerBear(CQT_Trung)
Time: 14:12
Day: 29/11/2021
Inf: https://www.facebook.com/lehoangtrung.nguyen/
Problem: https://oj.vnoi.info/problem/c11comp
--------------------------------*/

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

/* Author: c11comp */

/** END OF TEMPLATE. CODE GOES HERE **/

const int MAX = 1e5 + 9;
const int block = 450;
int n, q, k, cnt;
int a[MAX], id[MAX], ans[MAX], f[MAX];
vector<int> adj[MAX];
ii nodes[MAX];

void load(){
	read(n), read(q), read(k);
	FOR(i, 2, n) {
		int u;	read(u);
		adj[u].push_back(i);
	} FOR(i, 1, n) read(a[i]);
}

void dfs(int u) {
	id[++cnt] = u;
	nodes[u].fi = cnt;	
	for(int v : adj[u]) dfs(v);
	nodes[u].se = cnt;
}

void process(){
	dfs(1);
	sort(nodes + 1, nodes + 1 + n, [](ii a, ii b) {
		if((a.fi / block) != (b.fi / block)) return a.fi < b.fi;
		return a.se < b.se;
	});

	f[0] = (int)1e9;
	int l = 1, r = 0, res = 0;
	FOR(i, 1, n) {
		int L = nodes[i].fi, R = nodes[i].se;
		while(r < R) {
			int itr = a[id[++r]];	++f[itr];
			res += (f[itr] == 1);
			res -= (f[itr] == (k + 1));
			
		}

		while(r > R) {
			int itr = a[id[r--]];	--f[itr];
			res -= (f[itr] == 0);
			res += (f[itr] == k);
		}

		while(l < L) {
			int itr = a[id[l++]];	--f[itr];
			res -= (f[itr] == 0);
			res += (f[itr] == k);
		}

		while(l > L) {
			int itr = a[id[--l]];	++f[itr];
			res += (f[itr] == 1);
			res -= (f[itr] == (k + 1));
		}
		ans[id[nodes[i].fi]] = res;
	}

	int q;	read(q);
	while(q--) {
		int u;	read(u);
		cout << ans[u] << "\n";
	}
}

int32_t main(){
	FastIO;
	load();
	process();
	return 0;
}

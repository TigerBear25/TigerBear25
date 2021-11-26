/*--------------------------------
Coder: TigerBear(CQT_Trung)
Time: 14:54
Day: 26/11/2021
Inf: https://www.facebook.com/lehoangtrung.nguyen/
Problem: https://oj.vnoi.info/problem/coci2021_r2_sjekira
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

/* Author: TigerBear(CQT_Trung)*/

/** END OF TEMPLATE. CODE GOES HERE **/

const int MAX = 1e5 + 9;
int n, a[MAX];
ii edges[MAX];

void load() {
	cin >> n;
	REP(i, n) cin >> a[i];
	REP(i, n - 1) {
		cin >> edges[i].fi >> edges[i].se;
		--edges[i].fi, --edges[i].se;
	}
}

struct DisjoinSet {
	vector<int> par, values;
	DisjoinSet(int n = 0) {
		par.assign(n, -1);
		values.assign(a, a + n);
	}

	int root(int v, int mem) {
		if(par[v] < 0) {
			maximize(values[v], mem);
			return v;
		} return par[v] = root(par[v], max(mem, values[v]));
	}

	int join(int u, int v) {
		if((u = root(u, 0)) == (v = root(v, 0))) return 0;
		if(v < u) swap(u, v);

		int tmp = values[u] + values[v];
		maximize(values[u], values[v]);

		par[u] += par[v];
		par[v] = u;
		return tmp;
	}
};

bool cmp(ii s1, ii s2) {
	int x = max(a[s1.fi], a[s1.se]);
	int y = max(a[s2.fi], a[s2.se]);
	return x < y;
}

long long res = 0;
void process(){
	DisjoinSet dsu(n);
	sort(edges, edges + n - 1, cmp);
	REP(i, n - 1) res += 1LL * dsu.join(edges[i].fi, edges[i].se);
	cout << res;
}

int32_t main(){
	FastIO;
	load();
	process();
	return 0;
}

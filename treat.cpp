/*--------------------------------
Coder: TigerBear(CQT_Trung)
Time: 21:36
Day: 25/11/2021
Inf: https://www.facebook.com/lehoangtrung.nguyen/
Problem: https://oj.vnoi.info/problem/treat
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
#define left _left
#define right _right
using namespace std;

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

const int MAX = 1e5 + 7;
int n, cnt, nComp, res[MAX];
int nxt[MAX], low[MAX], num[MAX], id[MAX], d[MAX];
stack<int> S;

void dfs(int u) {
	S.push(u);
	low[u] = num[u] = ++cnt;

	if(!num[nxt[u]]) {
		dfs(nxt[u]);
		minimize(low[u], low[nxt[u]]);
	} else minimize(low[u], num[nxt[u]]);

	if(low[u] == num[u]) {
		++nComp;
		while(true) {
			int v = S.top();	S.pop();
			id[v] = nComp;
			++d[nComp];
			if(u == v) break;
		}
	}
}

int cal(int u) {
	if(res[u]) return res[u];
	if(nxt[u] == u) {
		res[u] = 1;
		return 1;
	}

	if(d[id[u]] > 1) return res[u] = d[id[u]];
	return res[u] = cal(nxt[u]) + 1;
}

void load() {
	cin >> n;
	FOR(i, 1, n) cin >> nxt[i];
}

void process() {
	FOR(i, 1, n) if(!num[i]) dfs(i);
	FOR(i, 1, n) if(!res[i]) cal(i);
	FOR(i, 1, n) cout << res[i] << " ";
}

int32_t main() {
	FastIO;
	load();
	process();
	return 0;
}

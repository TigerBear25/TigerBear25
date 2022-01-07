#include<bits/stdc++.h>
#define ON(x, i) (x | (1 << i))
#define MASK(i) (1 << i)
#define int long long
#define NAME "palin"
using namespace std;

const int MAX = 1e4 + 7;
const int N = (1 << 13);
const int base = 29;
const int inf = 1e9;

string s;
int n, k, res = inf;
int a[13], dp[MAX][N];
int hashL[MAX], hashR[MAX], pw[MAX];

bool isPalin(int l, int r) {
	int hL = hashL[r] - hashL[l - 1] * pw[r - l + 1];
	int hR = hashR[l] - hashR[r + 1] * pw[r - l + 1];
	return (hL == hR);
}

void maximize(int &x, int y) { x = max(x, y); }
void minimize(int &x, int y) { x = min(x, y); }

void load() {
	cin >> s >> k;
	for(int i = 0; i < k; ++i) cin >> a[i];

	n = (int)s.size();
	s = " " + s;

	pw[0] = 1;
	for(int i = 1; i <= n; ++i) {
		pw[i] = pw[i - 1] * base;
		hashL[i] = hashL[i - 1] * base + s[i] - 96;
	} for(int i = n; i >= 1; --i)
		hashR[i] = hashR[i + 1] * base + s[i] - 96;
}

void process() {
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < k; ++j) 
			if(i >= a[j] && isPalin(i - a[j] + 1, i)) {
				dp[i][MASK(j)] = i - a[j] + 1;
				for(int mask = 0; mask < MASK(k); ++mask) 
					maximize(dp[i][ON(mask, j)], dp[i - a[j]][mask]); 
			}

		for(int mask = 0; mask < MASK(k); ++mask) 
			maximize(dp[i][mask], dp[i - 1][mask]);
		
		if(dp[i][MASK(k) - 1] > 0)
			minimize(res, i - dp[i][MASK(k) - 1] + 1);
	} cout << ((res == inf) ? (-1) : (res));
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);

	freopen(NAME".inp", "r", stdin);
	freopen(NAME".out", "w", stdout);

	load();
	process();

	return 0;
}
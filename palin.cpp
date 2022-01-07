#include<bits/stdc++.h>
#define int long long
#define NAME "palin"
using namespace std;

const int MAX = 1e18;
const int N = 1e5 + 7;

int n, k;
int mem[N][2][2];

string s;
int midOdd, midEven;
vector<int> Odd, Even;

int add(int x, int y) {
	if(max(x, y) > MAX) return MAX + 1;
	if((x += y) > MAX) return MAX;
	return x;
}
 
int dp(int i, bool palinOdd, bool palinEven) {
	if(i > n) return (palinOdd | palinEven);
	int &res = mem[i][palinOdd][palinEven];
	if(res != -1) return res;

	res = 0LL;
	int mid = (i & 1) ? midOdd : midEven;

	if(i <= mid) res = add(res, 2LL * dp(i + 1, palinOdd, palinEven));
	else {
		res = add(res, dp(i + 1, palinOdd, palinEven));
		if(i & 1) res = add(res, dp(i + 1, 0, palinEven));
		else res = add(res, dp(i + 1, palinOdd, 0));
	} return res;
}

void trace(int i, bool palinOdd, bool palinEven, int cnt) {
	if(i > n) return;

	int res = 0;
	int mid = (i & 1) ? midOdd : midEven;

	if(i <= mid) {
		if(add(res, dp(i + 1, palinOdd, palinEven)) >= cnt) {
			s[i] = '0';
			trace(i + 1, palinOdd, palinEven, cnt);
 		} else {
 			s[i] = '1';
 			res = add(res, dp(i + 1, palinOdd, palinEven));
 			trace(i + 1, palinOdd, palinEven, cnt - res);
 		}
	} else {
		char c;

		if(i & 1) {
			int p = (int)Odd.size() + 1 - (i + 1) / 2;
			c = s[Odd[--p]];
		} else {
			int p = (int)Even.size() + 1 - (i + 1) / 2;
			c = s[Even[--p]];
		}
		
		if(c == '0') {
			if(add(res, dp(i + 1, palinOdd, palinEven)) >= cnt) {
				s[i] = '0';
				trace(i + 1, palinOdd, palinEven, cnt);
			} else {
				s[i] = '1';
				res = add(res, dp(i + 1, palinOdd, palinEven));

				if(i & 1) trace(i + 1, 0, palinEven, cnt - res);
				else trace(i + 1, palinOdd, 0, cnt - res);
			}
		} else {
			if(i & 1) {
				if(add(res, dp(i + 1, 0, palinEven) >= cnt)) {
					s[i] = '0';
					trace(i + 1, 0, palinEven, cnt);
					return;
				} res = add(res, dp(i + 1, 0, palinEven));
			} else {
				if(add(res, dp(i + 1, palinOdd, 0) >= cnt)) {
					s[i] = '0';
					trace(i + 1, palinOdd, 0, cnt);
					return;
				} res = add(res, dp(i + 1, palinOdd, 0));
			} 

			if(add(res, dp(i + 1, palinOdd, palinEven)) >= cnt) {
				s[i] = '1';
				trace(i + 1, palinOdd, palinEven, cnt - res);
			}
		}
	}
}

void solve() {
	cin >> n >> k;
	if(n == 1) {
		if(k == 1) cout << "0\n";
		if(k == 2) cout << "1\n";
		if(k > 2) cout << "NOT FOUND!\n";
		return ;
	}

	memset(mem, -1LL, sizeof(mem));
	Odd.clear(), Even.clear();

	for(int i = 1; i <= n; i += 2) Odd.push_back(i);
	for(int i = 2; i <= n; i += 2) Even.push_back(i);

	midOdd = Odd[((int)Odd.size() - 1) / 2];
	midEven = Even[((int)Even.size() - 1) / 2];

	int ans = dp(1, 1, 1);
	if(k > ans) cout << "NOT FOUND!\n";
	else {
		s.assign(n + 1, '0');
		trace(1, 1, 1, k);

		for(int i = 1; i <= n; ++i) cout << s[i];
		cout << "\n";
	}
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);

    freopen(NAME".inp", "r", stdin);
    freopen(NAME".out", "w", stdout);

    int t;	cin >> t;
    while(t--) solve();

	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); ++i)
#define pb push_back
#define mp make_pair
#define sz(a) int(a.size())
#define all(a) a.begin(),a.end()

typedef pair<int,int> pt;
#define x first
#define y second

typedef long long li;
typedef long double ld;

using namespace std;

bool solve(int);

int main() {
#ifdef SU1
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif

	int test = 0;
	while (solve(test++));
	
	return 0;
}

const int N = 1000 * 1000 + 5;

int lp[N];

vector <pt> factorize(int n) {
	vector <pt> res;
	while (n > 1) {
		int p = lp[n];
		res.pb(mp(p, 0));
		while (n % p == 0) {
			res.back().y++;
			n /= p;
		}
	}
	return res;
}

li n;
map <int, int> ppw;
set <int> mustz;

li res;

bool rec(li a) {
	if (ppw.empty()) {
		res += a;
		return true;
	}

	int p = (--ppw.end())->x;
	int pw = (--ppw.end())->y;

	if (pw > 0 && mustz.count(p))
		return false;

	ppw.erase(--ppw.end());

	if (pw == 0 && !mustz.count(p))
		return rec(a);

	vector <pt> f = factorize(p - 1);

	bool z = (mustz.count(p) > 0);

	for (int npw = 0; a <= n; npw++, a *= p) {
		if ((max(2 * npw - 1, 0) + pw) % 3 != 0)
			continue;

		if (z && (npw == 0))
			continue;

		if (npw > 0)
			for (auto it : f)
				ppw[it.x] += it.y;
				
		if (!rec(a))
			return false;

		if (npw > 0)
			for (auto it : f)
				ppw[it.x] -= it.y;
	}

	ppw[p] = pw;
	return true;
}

bool solve(int) {
	if (!(cin >> n))
		return false;
	res = 0;

	for (int i = 2; i < N; ++i)
		if (lp[i] == 0) {
			for (int j = i; j < N; j += i)
				if (lp[j] == 0)
					lp[j] = i;
		}


	for (int i = 1; li(i) * i <= n; ++i) {
		vector <pt> f = factorize(i);
		bool b = true;
		forn(i, sz(f))
			if (f[i].y > 1)
				b = false;

		if (!b)
			continue;

		ppw.clear();
		mustz.clear();
		forn(i, sz(f)) {
			ppw[f[i].x] = 0;
			mustz.insert(f[i].x);
		}

		rec(1);
	}
	cerr << res << endl;
	return true;
}

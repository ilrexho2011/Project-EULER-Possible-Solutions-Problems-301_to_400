#include <stdio.h>
#include <algorithm>
#include <map>

// Defined externally:
#include "__bigint2.h"

typedef unsigned int uint;

static bool winning (uint n, uint r)
{
	if (n<=2*r)
		return true;

	typedef std::pair<uint,uint> NR;
	NR nr (n, r);
	static std::map<NR,bool> cache;
	if (cache.count (nr))
		return cache[nr];

	bool wins = false;
	for (uint r2=1; r2<=std::min (n-1, 2*r); r2++) {
		if (!winning (n-r2, r2)) {
			wins = true;
			break;
		}
	}
	return cache[nr] = wins;
}

static uint maxwin (uint n)
{
	uint rmax = 0;
	for (uint r=1; r<n; r++) {
		if (!winning (n-r, r))
			rmax = r;
	}
	return rmax;
}

static const BigInt nmax = 1e18;
#define Z BigIntZero

static const uint NMAX = 100;
static BigInt f[NMAX] = {Z, 1};
static BigInt a[NMAX] = {Z, Z};
static BigInt s[NMAX] = {Z, Z, Z, Z, Z, Z};

static void solve_actual_problem ()
{
	BigInt sum = Z;
	for (uint i=2; ; i++) {
		f[i] = f[i-1] + f[i-2];
		if (f[i]>nmax)
			break;
		a[i] = (f[i]-1)/2;
		bool done = false;
		if (f[i]+a[i]>nmax) {
			a[i] = nmax-f[i];
			done = true;
		}
		sum += a[i]*(a[i]+1)/2;
		if (done)
			break;
		BigInt b1 = Z;
		BigInt b2 = Z;
		if (i>5) {
			b1 = a[i-3]+1;
			b2 = a[i-2];
			s[i] = s[i-2] + b2*(b2+1)/2;
			if (b1>Z)
				s[i] -= (b1-1)*(b1-1+1)/2;
			sum += s[i];
		}
	}
	std::cout << sum << std::endl;
}

void main ()
{
	// Solve actual problem:
	solve_actual_problem ();

	// Original brute-force solution:
	printf ("\n");
	const uint nmax2 = 5000;
	printf ("Hit enter for brute-force of nmax=%d:\n", nmax2);
	getchar ();
	uint sum = 0;
	uint rmaxlast = 9999;
	for (uint n=1; n<=nmax2; n++) {
		uint rmax = maxwin (n);
		if (rmax==rmaxlast+1) {
			;
		} else {
			printf ("%d\n", rmaxlast);
			printf ("%d: %d-", n, rmax);
		}
		rmaxlast = rmax;
		sum += rmax;
	}
	printf ("\n");
	printf ("sum(%d) = %d\n", nmax2, sum);
}
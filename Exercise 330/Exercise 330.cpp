#include <stdio.h>
#include <time.h>

typedef unsigned int uint;
typedef unsigned long long ull;

// From external library (uint vs ull would be sufficient):
extern ull mulmod (ull a, ull b, ull mod);
extern ull CRT (uint len, ull *a, ull *mod);

// Allocate required memory:
static const uint NMAX = 9100;
static uint fac[NMAX+1];
static uint binom[NMAX+1][NMAX+1];
static uint AB[NMAX+1];

// Timer:
static uint start = time (NULL);

// Set factorials and binomial coefficients:
static void initialize (uint mod, uint nmax)
{
	fac[0] = 1;
	for (uint n=1; n<=nmax; n++)
		fac[n] = mulmod (n, fac[n-1], mod);

	for (uint n=0; n<=nmax; n++) {
		for (uint m=0; m<=n; m++) {
			if (m==0 || m==n)
				binom[n][m] = 1;
			else
				binom[n][m] = (binom[n-1][m-1] + binom[n-1][m])%mod;
		}
	}
}

void main ()
{
	// Loop over all prime factors:
	const uint NMOD = 5;
	ull pmod[NMOD] = {7, 11, 73, 101, 137};
	ull abmod[NMOD];
	for (uint imod=0; imod<NMOD; imod++) {

		// Set prime factor:
		uint p = pmod[imod];

		// Set period:
		uint period = p*(p-1);

		// Set nmax at which to compute AB:
		uint nmax = 1e9;
		nmax %= period;
		if (nmax<p)
			nmax += period;
		printf ("%d: %d\n", p, nmax);

		// Set factorials and binomial coefficients at this mod:
		initialize (p, nmax);

		// Apply recurrence to compute AB at nmax:
		AB[0] = 0;
		for (uint n=1; n<=nmax; n++) {
			AB[n] = 0;
			for (uint m=0; m<n; m++) {
				AB[n] += mulmod (binom[n][m], AB[m]+fac[m], p);
				AB[n] %= p;
			}
		}
		printf ("       AB = %d\n", AB[nmax]);

		// Store result for use by CRT:
		abmod[imod] = AB[nmax];
	}

	// Combine results using CRT and take complement:
	printf ("\n");
	printf ("CRT complement = %lld\n", 77777777 - CRT (NMOD, abmod, pmod));
			// 15955822
	printf ("Time = %d sec\n", time(NULL)-start);
			// 2 sec
}
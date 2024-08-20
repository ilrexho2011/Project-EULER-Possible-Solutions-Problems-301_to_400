#include <stdio.h>
#include <math.h>
#include <time.h>

typedef unsigned int uint;
typedef unsigned long long ull;

static const ull nmax = 1e9;

void main ()
{
	const uint NA = 100;
	ull ax[NA] = {8, 10, 22, 32};
	ull a[NA] = {36, 90, 594, 1296};
	ull sum = 2*(a[0]+a[1]+a[2]+a[3]);
	for (uint i=4; ; i++) {
		ax[i] = 4*ax[i-2] - ax[i-4];
		if (ax[i]>nmax)
			break;
		a[i] = 14*a[i-2] - a[i-4];
		sum += 2*a[i];
		printf ("ax[%d]=%lld, a[%d]=%lld, sum=%lld\n", i, ax[i], i, a[i], sum);
	}

	const uint NB = 100;
	ull b[NB] = {0, 234};
	sum += 4*b[1];
	for (uint i=2; ; i++) {
		b[i] = 14*b[i-1] - b[i-2];
		ull bx = (ull)(0.85*sqrt ((double)b[i]));
		if (bx>nmax)
			break;
		sum += 4*b[i];
		printf ("bx[%d]=%lld, b[%d]=%lld, sum=%lld\n", i, bx, i, b[i], sum);
		// sum=3776957309612153700
	}

	printf ("%d msec\n", clock ()); // 20 msec
}
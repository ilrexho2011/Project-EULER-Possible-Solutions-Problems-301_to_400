#include <stdio.h>
#include <string.h> // for memset
#include <math.h>
#include <time.h>

typedef unsigned int uint;
typedef unsigned long long ull;

// Dimensions of maze:
static const uint n = 4;
static const uint m = 3;

// Horizontal and vertical gates (open or closed):
static bool ver[n+1][m];
static bool hor[n][m+1];

// Number of to-be-set gates (edges excluded):
static const uint kmax = (n-1)*m + n*(m-1);

// Track usage:
static bool used[n][m];
static uint nused;
static uint nopen;

// Create the maze based on binary bitmask:
static void setmaze (ull mask)
{
	// Initialize all gates to closed (including edges):
	memset (ver, 0, sizeof (ver));
	memset (hor, 0, sizeof (hor));

	// Count open gates:
	nopen = 0;

	// Set ver gates:
	uint k = 0;
	for (uint i=1; i<n; i++) {
		for (uint j=0; j<m; j++) {
			if (mask & (1ULL<<k)) {
				ver[i][j] = true;
				nopen++;
			}
			k++;
		}
	}

	// Set hor gates:
	for (uint i=0; i<n; i++) {
		for (uint j=1; j<m; j++) {
			if (mask & (1ULL<<k)) {
				hor[i][j] = true;
				nopen++;
			}
			k++;
		}
	}

	// Initialize cell usage:
	memset (used, 0, sizeof (used));
	used[0][0] = true;
	nused = 1;
}

// Check if configuration is a valid maze:
static bool valid ()
{
REPEAT:
	uint nused_old = nused;

	for (uint i=0; i<n; i++) {
		for (uint j=0; j<m; j++) {
			if (!used[i][j])
				continue;

			// Step up (i,j)-->(i,j-1):
			if (j>0 && hor[i][j]) {
				if (used[i][j-1])
					return false;
				used[i][j-1] = true;
				hor[i][j] = false; // so we cannot go back
				nused++;
				nopen--;
			}

			// Step down (i,j)-->(i,j+1):
			if (j+1<m && hor[i][j+1]) {
				if (used[i][j+1])
					return false;
				used[i][j+1] = true;
				hor[i][j+1] = false;
				nused++;
				nopen--;
			}

			// Step left (i,j)-->(i-1,j):
			if (i>0 && ver[i][j]) {
				if (used[i-1][j])
					return false;
				used[i-1][j] = true;
				ver[i][j] = false;
				nused++;
				nopen--;
			}

			// Step right (i,j)-->(i+1,j):
			if (i+1<n && ver[i+1][j]) {
				if (used[i+1][j])
					return false;
				used[i+1][j] = true;
				ver[i+1][j] = false;
				nused++;
				nopen--;
			}
		}
	}

	// Completion or continue:
	if (nused==n*m && nopen==0)
		return true;
	else if (nused==nused_old)
		return false;
	else
		goto REPEAT;
}

// Formula from https://oeis.org/A116469:
static char *C (uint n, uint m)
{
	static const double pi = 4*atan(1.);
	double logprod = 0;
	for (uint k=1; k<n; k++) {
		double arg = k*pi/2/n;
		double s = 2*sin (arg);
		double kn = s*s;
		for (uint h=1; h<m; h++) {
			arg = h*pi/2/m;
			s = 2*sin (arg);
			double hm = s*s;
			logprod += log10 (hm+kn);
		}
	}
	static char buf[256];
	uint expo = (uint)logprod;
	double man = pow (10., logprod-expo);
	sprintf (buf, "%.4fe%d", man, expo);
	return buf;
}

void main ()
{
	// Brute force:
	ull num = 0;
	for (ull mask=0; mask<(1ULL<<kmax); mask++) {
		setmaze (mask);
		if (valid ())
			num++;
	}
	printf ("C(%d,%d)= %lld\n", m, n, num); // 2415 indeed

	// Sample value:
	char *C_9_12 = C (9, 12);
	printf ("C(9,12) = %s\n", C_9_12); // 2.5720e+46 indeed

	// Actual problem:
	char *ans = C (100, 500);
	printf ("C(100,500) = %s\n", ans); // 6.3202e25093

	// Timer:
	printf ("%d msec\n", clock ()); // 19 msec
}
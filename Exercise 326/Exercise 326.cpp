#include <stdio.h>
#include <time.h>
#include <vector>

// Defined externally:
#include "__bigint2.h"

typedef unsigned int uint;
typedef unsigned long long ull;

//#define SAMPLE
#ifdef SAMPLE
static const ull N = 1e4;
static const uint M = 1e3;
#else
static const ull N = 1e12;
static const uint M = 1e6;
#endif

// Period:
static const uint P = 6*M;
static uint aM[P];

void main ()
{
	uint time0 = time (NULL);

	// Compute a-mod-M terms within first period:
	printf ("P = %d\n", P);
	aM[0] = 0;
	aM[1] = 1;
	ull a = 1;
	BigInt s = BigIntZero;
	for (uint n=2; n<P; n++) {
		s += a*(n-1);
		a = to_ull (s%n);
		aM[n] = a%M;
		if (n%100000==0)
			std::cout << n << ": " << s << std::endl;
	}
	printf ("%d sec\n", (uint)time(NULL)-time0); // 104 sec

	// Closed sets:
	typedef std::vector<uint> LENS;
	static LENS lens[P];

	// Find closed sets over period:
	uint npreset = 0;
	for (uint start=0; start<P; start++) {
		if (start%1000==0) {
			uint sec = time(NULL)-time0;
			printf ("%d of %d (%d sec)\n", start, P, sec);
		}
		LENS &l = lens[start];
		if (!l.empty ()) {
			npreset++;
			continue;
		}
		LENS dif;
		uint sum = 0;
		l.push_back (0);
		uint last = 0;
		for (uint len=1; len<=P; len++) {
			sum += aM[(start+len)%P];
			sum %= M;
			if (sum==0) {
				l.push_back (len);
				dif.push_back (len-last);
				last = len;
			}
		}
		if (last!=P)
			Pause ("last=%d, P=%d", last, P);

		// Construct derivatives:
		for (uint off=1; off+1<l.size (); off++) {
			uint start2 = start + l[off];
			LENS &l2 = lens[start2];
			l2.push_back (0);
			for (uint i=0; i<dif.size (); i++) {
				uint len = l2[i] + dif[(off+i)%dif.size ()];
				l2.push_back (len);
			}
		}
	}
	printf ("npreset = %d of %d\n", npreset, P); // 5195824 of 6000000 (87%)

	// Sums within period:
	static ull nump[P];
	ull sumnump = 0;
	for (uint lenmax=0; lenmax<P; lenmax++) {
		const LENS &l = lens[(N-lenmax)%P];
		ull &num = nump[lenmax];
		num = 0;
		uint i = 0;
		while (lenmax >= l[i] && i+1<l.size ()) {
			num++;
			i++;
			if (i==l.size ())
				break;
		}
		num--; // not sure why needed (but it is--confirmed)
		sumnump += num;
	}

	// Compute desired number:
	ull NP = N/P;
	ull num = NP*sumnump;
	for (ull lenmax=1; lenmax<=(N%P); lenmax++)
		num += nump[lenmax];

	ull s1 = NP*(NP+1)/2;
	ull s2 = (NP-1)*NP/2;
	for (ull start=0; start<P; start++) {
		uint size = lens[start].size () - 1;
		if (start<=(N%P))
			num += s1*size;
		else
			num += s2*size;
	}
	printf ("num = %lld\n", num); // 1966666166408794329
	printf ("%d sec\n", (uint)time(NULL)-time0); // 16213 sec (4.5 hours)
}
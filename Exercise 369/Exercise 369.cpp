#include <stdio.h>
#include <time.h>
#include <vector>

typedef unsigned int uint;
typedef unsigned long long ull;

static uint nc = 13*4;
static const uint n = 13;

static bool forms_pair (uint a, uint b)
{
	return (a/4==b/4 || a%4==b%4);
}

typedef std::vector<uint> SEQ;

static bool badugi (const SEQ &seq)
{
	if (seq.size ()<4)
		return false;

#define P(i,j) forms_pair (seq[i], seq[j])

	uint i1 = seq.size ()-1;
	for (uint i2=0; i2<seq.size ()-1; i2++) {
		if (P(i2,i1))
			continue;
		for (uint i3=i2+1; i3<seq.size ()-1; i3++) {
			if (P(i3,i1) || P(i3,i2))
				continue;
			for (uint i4=i3+1; i4<seq.size ()-1; i4++) {
				if (P(i4,i1) || P(i4,i2) || P(i4,i3))
					continue;
				return true;
			}
		}
	}
	return false;
}

static ull sum = 0;
static uint start = time (NULL);

static void dfs (SEQ &seq)
{
	if (seq.size ()>=n)
		return;
	uint imin = seq.empty () ? 0 : seq.back ()+1;
	for (uint i=imin; i<nc; i++) {
		if (imin==0) {
			uint sec = time(NULL)-start;
			printf ("%d (%d sec) %lld (%lld)\n", i, sec, sum, sum%13);
		}
		seq.push_back (i);
		if (badugi (seq)) {
			sum++;
			ull d = nc-i-1;
			ull prod = 1;
			for (uint dn=0; seq.size ()+dn<n; dn++) {
				prod = prod*(d-dn)/(dn+1);
				sum += prod;
			}
		} else {
			dfs (seq);
		}
		seq.pop_back ();
	}
}

void main ()
{
	SEQ seq;
	dfs (seq);
	printf ("sum(%d) = %lld\n", n, sum); // 862400558448 (in my PC 4.5 hrs)
}
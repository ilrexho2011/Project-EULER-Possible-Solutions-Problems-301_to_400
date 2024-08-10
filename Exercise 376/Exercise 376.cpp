#include <stdio.h>
#include <time.h>
#include <vector>
#include <map> // for binom

typedef unsigned int uint;
typedef unsigned long long ull;

static const uint NFACE = 6; // 4; // 5;

typedef unsigned char WHICH;
static const WHICH A = 0;
static const WHICH B = 1;
static const WHICH C = 2;

struct NW {
	uint num; // 1 to 3*NFACE
	WHICH which; // A, B, or C
	NW (uint num, WHICH which) : num(num), which(which) {}
};

typedef std::vector<NW> NWS; // length 1-3
typedef std::vector<NWS> SIG; // signature
typedef std::vector<SIG> SIGS;

typedef std::vector<uint> DIE;
typedef std::vector<DIE> DIES;

static void dfs (SIG &sig2, const SIG &sig, const DIE &die,
		uint isig, uint idie, WHICH which, SIGS &sigs)
{
	if (idie==die.size ()) {
		// Append remaining:
		SIG sig2b = sig2;
		for (; isig<sig.size (); isig++)
			sig2b.push_back (sig[isig]);
		sigs.push_back (sig2b);
		return;
	}

	// Insert:
	sig2.push_back (NWS (1, NW (die[idie], which)));
	dfs (sig2, sig, die, isig, idie+1, which, sigs);
	sig2.pop_back ();

	// Merge:
	if (isig<sig.size ()) {
		NWS nws = sig[isig];
		nws.push_back (NW (die[idie], which));
		sig2.push_back (nws);
		dfs (sig2, sig, die, isig+1, idie+1, which, sigs);
		sig2.pop_back ();
	}

	// Skip:
	if (isig<sig.size ()) {
		const NWS &nws = sig[isig];
		sig2.push_back (nws);
		dfs (sig2, sig, die, isig+1, idie, which, sigs);
		sig2.pop_back ();
	}
}

static void merge (const SIG &sig, const DIE &die, WHICH which, SIGS &sigs)
{
	SIG sig2;
	dfs (sig2, sig, die, 0, 0, which, sigs);
}

static uint countlower (const SIG &sig, uint i, WHICH b)
{
	uint num = 0;
	for (uint j=0; j<i; j++) {
		const NWS &nws = sig[j];
		for (uint k=0; k<nws.size (); k++) {
			if (nws[k].which==b)
				num += nws[k].num;
		}
	}
	return num;
}

static bool iswin (const SIG &sig, WHICH a, WHICH b)
{
	uint num = 0;
	for (uint i=0; i<sig.size (); i++) {
		const NWS &nws = sig[i];
		for (uint j=0; j<nws.size (); j++) {
			const NW &nw = nws[j];
			if (nw.which==a)
				num += nw.num*countlower (sig, i, b);
		}
	}
	return num>NFACE*NFACE/2;
}

static bool nontransitive (const SIG &sig)
{
	if (!iswin (sig, B, C))
		return false;
	if (!iswin (sig, C, A))
		return false;
	return true;
}

static ull binom (uint n, uint m)
{
	if (m>n)
		return 0;
	if (m==0 || m==n)
		return 1;

	typedef std::pair<uint,uint> NM;
	NM nm (n, m);
	static std::map<NM,ull> cache;
	if (cache.count (nm))
		return cache[nm];
	else
		return cache[nm] = binom (n-1, m-1) + binom (n-1, m);
}

void main ()
{
	// Compute set of 1-die types:
	DIES dies;
	for (uint mask=0; mask<(1U<<(NFACE-1)); mask++) {
		DIE die;
		uint num = 1;
		for (uint i=0; i<NFACE-1; i++) {
			bool same = mask & (1U<<i);
			if (same) {
				num++;
			} else {
				die.push_back (num);
				num = 1;
			}
		}
		die.push_back (num);
		dies.push_back (die);
		printf ("die %d:", (uint)dies.size ());
		for (uint i=0; i<die.size (); i++)
			printf (" %d", die[i]);
		printf ("\n");
	}
	printf ("dies = %d\n", (uint)dies.size ());

	// Convert to 1-die signatures:
	SIGS sigs1;
	for (uint i=0; i<dies.size (); i++) {
		SIG sig;
		merge (sig, dies[i], A, sigs1);
	}
	printf ("sigs1.size = %d\n", (uint)sigs1.size ());

	// Compute all 2-die signatures:
	SIGS sigs2;
	for (auto it=sigs1.begin (); it!=sigs1.end (); it++) {
		for (uint i=0; i<dies.size (); i++) {
			merge (*it, dies[i], B, sigs2);
		}
	}
	printf ("sigs2.size = %d\n", (uint)sigs2.size ());

	// Compute number of winning combinations (for stats):
	uint numAB = 0;
	for (auto it=sigs2.begin (); it!=sigs2.end (); it++) {
		if (iswin (*it, A, B))
			numAB++;
	}
	printf ("numAB = %d\n", numAB);

	// Tally m values:
	uint ntrans[3*NFACE+1];
	memset (ntrans, 0, sizeof (ntrans));

	// Look at all combination of AB and C:
	uint i = 0;
	uint start = time (NULL);
	for (auto it=sigs2.begin (); it!=sigs2.end (); it++) {

		// Does A win over B:
		if (!iswin (*it, A, B))
			continue;

		// Progress indicator:
		if (i%10==0) {
			double pct = 100.*i/numAB;
			uint sec = time(NULL) - start;
			double hrs = sec/3600.;
			double tot = 100./pct*hrs;
			printf ("%.2f%%: %.2f/%.2f hrs\n", pct, hrs, tot);
			// 9.5 hours total
		}

		// Check all C vs selected AB:
		for (uint j=0; j<dies.size (); j++) {
			SIGS sigs3;
			merge (*it, dies[j], C, sigs3);
			for (auto it2=sigs3.begin (); it2!=sigs3.end (); it2++) {
				if (nontransitive (*it2)) {
					uint m = it2->size ();
					ntrans[m]++;
				}
			}
		}
		i++;
	}

	// Show distribution of m values:
	printf ("ntrans =");
	for (uint m=0; m<=3*NFACE; m++)
		printf (" %d", ntrans[m]);
	printf ("\n");

	// Now compute actual answers for different numbers of pips:
	for (uint N=6; N<=30; N++) {
		ull num = 0;
		for (uint m=0; m<=3*NFACE; m++) {
			num += ntrans[m] * binom (N, m);
		}
		printf ("%d: %lld\n", N, num/3); // 30: 973059630185670
	}
}
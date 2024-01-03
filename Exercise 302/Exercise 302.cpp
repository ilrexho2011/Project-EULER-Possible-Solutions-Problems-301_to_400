#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
/*
gcc -march=native -w -O3 --std=c99 -o euler302 euler302.c -lm
*/

/* Bitset from C FAQ */
#define BUCKET_BITS  (uint64_t) (sizeof(uint64_t)*8)
#define BITMASK(b) (1ul << ((b) % BUCKET_BITS))
#define BITSLOT(b) ((b) / BUCKET_BITS)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT((uint64_t) b)] & BITMASK((uint64_t) b))
#define BITNSLOTS(nb) ((nb + BUCKET_BITS - 1ul) / BUCKET_BITS)

#define N ((uint32_t) 630000) //2^2 * x^3 < 10^18 => x < 630000
#define PI_N 51341 // number of primes below 630000
#define MAXDEPTH 8 // (2*3*5*7*11*13*17)^2*19^3 < 10^18 < (2*3*5*7*11*13*17*19)^2*23^3
#define LIMIT ipow(10,18)

uint32_t primes[PI_N];
uint32_t factors[MAXDEPTH];
unsigned int exponents[MAXDEPTH];
uint64_t cnt = 0;
uint64_t K;

int gcd(int a, int b) {
	if (a == 0 || b == 0) {
		return a | b;
	}

	int k = ffs(a | b) - 1;
	a >>= ffs(a) - 1;
	
	while (b != 0) {
		b >>= ffs(b) - 1;
		if (a > b) {
			int temp = b;
			b = a;
			a = temp;
		}
		b -= a;
	}
	return a << k;
}

uint64_t ipow(uint64_t a, int b) {
	if (b == 0) {
		return 1;
	}
	uint64_t tmp = ipow(a, b >> 1);
	if ((b & 1) == 0) {
		return tmp * tmp;
	} else {
		return a * tmp * tmp;
	}
}

bool checkstrongachilles(unsigned int depth) {
	uint64_t n = factors[depth - 1] - 1;

	for (uint32_t* p = factors + depth - 2, *e = exponents + depth - 2; p >= factors; p--,e--) {
		n *= ipow(*p, *e - 1) * (*p - 1); // p > 2 && p prime => 2 | p-1 
	}
	
	unsigned int p2 = ffsll(n) - 1;
	n >>= p2;

	unsigned int lastgcd = gcd(p2, exponents[depth - 1] - 1);
	unsigned int k = 0;
	
	uint32_t* p = factors + (depth - 2);
	
	while (n > 1 && p >= factors) {
		if (n % *p == 0) {
			n /= *p;
			k++;
		} else {
			if (k > 0) {
				if (k < 2) {
					return false;
				} else if (lastgcd != 1) {
					lastgcd = gcd(lastgcd, k);
				}
				k = 0;
			}
			p--;
		}
	}
	if (k > 0) {
		if (k < 2) {
			return false;
		} else if (lastgcd > 1) {
			lastgcd = gcd(lastgcd, k);
		}
	}
	if (n > 1) {
		p = primes + 1; //3
		while (n > 1) {
			if (n % *p == 0) {
				n /= *p;
				k++;
			} else {
				if (k > 0) {
					if (k < 2) {
						return false;
					} else if (lastgcd != 1) {
						lastgcd = gcd(lastgcd, k);
					}
					k = 0;
				}
				p++;
			}
		}
		if (k > 0) {
			if (k < 2) {
				return false;
			} else if (lastgcd > 1) {
				lastgcd = gcd(lastgcd, k);
			}
		}
	}
	return lastgcd == 1;
}
//Checks exponents for a certain list of prime factors
void bte(unsigned int len, unsigned int depth, unsigned __int128 val) {
	if (len < depth) {	
		unsigned int lastgcd = exponents[depth - 1];
		for (uint32_t* e = exponents + depth - 2; e >= exponents; e--) {
			lastgcd = gcd(lastgcd, *e);
			if (lastgcd == 1) {
				break;
			}
		}
		if (lastgcd == 1 && checkstrongachilles(depth)) {
			cnt++;
		}
	} else {
		uint64_t p = factors[depth];
		
		if (len == depth) {
			val *= p * p * p; //N^3 < 2^64
			exponents[depth] = 3;
		} else {
			val *= p * p;
			exponents[depth] = 2;
		}
		for (; val < K ; exponents[depth]++, val *= p) {
			bte(len, depth + 1, val);
		}
	}
}
//Creates all single prime factor combination that are candidates
void bt(unsigned __int128 val, unsigned int depth, uint32_t* last) {
	for (last++; last < primes + PI_N; last++) {
		uint64_t p = *last;

		unsigned __int128 newval = val * (p * p);
		if (newval >= K / p) { //the biggest prime factor has to have at least an exponent greater than 3
			break;
		}
		factors[depth] = p;
		if (depth >= 1) {
			bte(depth, 0, 1);
		}

		bt(newval, depth + 1, last);
	}
}

int main() {
	K = LIMIT;
	uint64_t* sieve = (uint64_t*) calloc(BITNSLOTS(N+1), sizeof(uint64_t));
	
	if (!sieve) {
		fprintf(stderr, "memory allocation failed\d");
		exit(1);
	}

	BITSET(sieve, 0ul);
	BITSET(sieve, 1ul);
	for (uint64_t i = 2; i <= sqrt(N); i++) {
		if (!BITTEST(sieve, i)) {
			for (uint64_t j = i * i; j <= N; j += i) {
				BITSET(sieve, j);
			}
		}
	}
	uint32_t* ps = primes;
	for (int i = 2; i <= N; i++) {
		if (!BITTEST(sieve, i)) {
			*(ps++) = i;
		}
	}
	free(sieve);
	bt(1, 0, primes - 1);
	printf("Result: %lu\n", cnt);
}
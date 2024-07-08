#include <stdint.h>
#include <stdlib.h>
#include <stdio.h> 
#include <math.h> 
        
void get_primes (uint64_t n, uint64_t ** primes, uint64_t * n_primes) {
    char * sieve = malloc (sizeof (char) * n);
    for (uint64_t i=0; i<n; ++i)
        sieve[i] = i % 2 ? 1 : 0;
    sieve[0] = sieve[1] = 0; sieve[2] = 1;
    *n_primes = 1;
    for (uint64_t i=3; i<n; ++i)
        if (sieve[i]) {
            (*n_primes)++;
            for (uint64_t j=i*i; j<n; j+=i)
                sieve[j] = 0;
        }
    (*primes) = malloc (sizeof (uint64_t)*(*n_primes));
    *n_primes = 0;
    for (uint64_t i=0; i<n; ++i)
        if (sieve[i])
            (*primes)[(*n_primes)++] = i;
    free (sieve);
}   

uint64_t f (uint64_t a, uint64_t * primes, uint64_t n_primes) {
    a++;    
    uint64_t i = 0ULL;
    while (primes[i]*primes[i] <= a) {
        if (i > n_primes)
            printf ("%llu %llu ERROR", i, n_primes);
        while (a % primes[i] == 0ULL && a != primes[i])
            a /= primes[i];
        ++i;
    }
    return a - 1ULL;
}   
    
int main (void) {
    uint64_t n = 2000000ULL;
    uint64_t *primes, n_primes;
    get_primes ((uint64_t) powl ((long double) n, (long double) 1.51), &primes, &n_primes);
        
    uint64_t s = 0;
    for (int64_t i=1; i<=n; ++i) {
        uint64_t t = f (i*i*i, primes, n_primes);
        if (i % 10000 == 0)
            printf ("done %llu\n", i);
        s += t;
    }
    printf ("%llu\n", s);

    free (primes);
    return 0;
}
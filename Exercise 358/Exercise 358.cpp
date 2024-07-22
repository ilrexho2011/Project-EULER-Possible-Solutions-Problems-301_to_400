#include <iostream>
#include <vector>
#include <stdio.h>

#define SIEVE_RANGE (28000)
#define SEGMENTED_SIEVE_RANGE (5289326)
#define SEGMENTED_BEGIN (724637682)
#define SEGMENTED_END (729927007)
#define PRIME_COUNT (3055)

bool sieve_visited[SIEVE_RANGE] = {};
bool segmented_sieve_visited[SEGMENTED_SIEVE_RANGE] = {};
long long primes[PRIME_COUNT] = {};

void Sieve()
{
    sieve_visited[0] = sieve_visited[1] = true;
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve_visited[i])
        {
            primes[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve_visited[j] = true;
            }
            long long shift = SEGMENTED_BEGIN % i;
            long long k = SEGMENTED_BEGIN + ((shift > 0) ? i - shift : 0);
            for (; k <= SEGMENTED_END; k += i)
            {
                segmented_sieve_visited[k - SEGMENTED_BEGIN] = true;
            }
        }
    }
    std::cout << "Prime count: " << curr_pos << std::endl;
}

long long ExtendedEuclid(long long A, long long B, long long *X, long long *Y)
{
    long long x = 0;
    long long y = 1;
    long long u = 1;
    long long v = 0;
    long long m, n, a, b, q, r;
    for (a = A, b = B; 0 != a; b = a, a = r, x = u, y = v, u = m, v = n)
    {
        q = b / a;
        r = b % a;
        m = x - (u * q);
        n = y - (v * q); 
    }    
    *X = x; 
    *Y = y;
    return b;
}

long long GetInverse(long long a, long long n)
{
    long long x, y;
    ExtendedEuclid(a, n, &x, &y);
    return x;
}

bool Check(long long prime)
{
    long long x = (100000 - GetInverse(prime, 100000)) % 100000;
    return x == 56789;
}

void Solve()
{
    Sieve();
    for (long long i = 0; i < SEGMENTED_SIEVE_RANGE; i++)
    {
        if (segmented_sieve_visited[i]) 
        {
            continue;
        }
        long long prime = i + SEGMENTED_BEGIN;
        if (Check(prime))
        {
            long long digit_sum = 9 * (prime - 1) / 2;
            std::cout << prime << " => " << digit_sum << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    Solve();
    return 0;
}
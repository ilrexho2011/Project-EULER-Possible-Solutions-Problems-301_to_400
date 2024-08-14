#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cmath>
#include <set>
#include <map>
#include <vector>

using namespace std;

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned __int64 u64;
typedef signed __int64 s64;
typedef short int u8;

static void extended_GCD(uint a, uint b, s64 & resX, s64 & resY)
{// since b will always be a prime number the value in resX will be the modulo inverse of A mod B
    s64 x = 0;
    s64 lastX = 1;
    s64 y = 1;
    s64 lastY = 0;

    while(b > 0)
    {
        int quotient = a / b;
        int tmp = b;

        // a = b, b = a mod b
        b = a % b;
        a = tmp;

        s64 tmpB;

        // x = lastX - quotient*x, lastX = x
        tmpB = x;
        x = lastX - quotient*x;
        lastX = tmpB;

        // y = lastY - quotient*y, lastY = y
        tmpB = y;
        y = lastY - quotient*y;
        lastY = tmpB;
    }

    resX = lastX;
    resY = lastY;
}

//---------------------------------------------------------------------------------------------------------------------
// returns the number of primes, and the sieve containing a bit array filled with primes (bit=0) or composites(bit=1)
//---------------------------------------------------------------------------------------------------------------------
static int ErratSieve(uint * &sieve, const uint limit)
{
    uint prmcount = 0;

    uint arraylim = (limit + 31) >> 5;
    uint sqrlim = (int)(floor(sqrt(limit))+ 1);

    sieve = new uint[arraylim];

    uint i,j;

    for(i = 0;i < arraylim;++i)
        sieve[i] = 1431655765;//0101 0101 0101 0101 0101 0101 0101 0101 binary (sets all even numbers as composite)

    sieve[0] = 1431655763;//(fist 2 is not a prime)

    ++prmcount;//hardoce the 2 as a prime number

    for(i = 3;i < limit;i += 2)
    {
        if(0 != (sieve[i >> 5] & (1 << (i & 31))))
            continue;

        ++prmcount;
        if(i > sqrlim)//no more multiples of this prime in the range
            continue;

        for(j = i*i;j < limit;j += (i+i))
        {
            sieve[j >> 5] |= (1 << (j & 31));
        }
    }

    return prmcount;
}

int main(int argc, char ** argv)
{
    clock_t timeElapsed = clock();
//---------------------------------------------------------------------------------------------------------------------
    const uint numberLim = 100000000;
    uint i;
    uint * sieve;

    ErratSieve(sieve, numberLim);

    u64 answer = 0;

    for(i = 5;i < numberLim;++i)
    {
        if(0 != (sieve[i >> 5] & (1 << (i & 31))))
            continue;

        uint j;
        s64 mul = -1;
        s64 sum = - 1;

        for(j = 1;j < 5;++j)
        {
            s64 x, y;

            extended_GCD(i-j, i, x, y);

            mul *= x;

            mul %= i;

            sum += mul;
        }

        while(sum < 0) sum += i;

        sum %= i;

        answer += sum;
    }

    printf("%I64u\n", answer);

    delete[] sieve;
//---------------------------------------------------------------------------------------------------------------------
    timeElapsed = clock() - timeElapsed;
    double timeElapsedInSec = timeElapsed;
    timeElapsedInSec /= CLOCKS_PER_SEC;
    printf("Total Time Elapsed: %.3lf seconds\n", timeElapsedInSec);

    return 0;
}
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int prmlim = 1111112;
char * errat;

static void factorize(__int64 tgt, int * const fctrs, int * const fctpow, int & fcnt)
{
    int i;

    fcnt = 0;

    for(i = 0;i < prmlim;++i)
    {
        if(0 != errat[i])
            continue;

        fctrs[fcnt] = i;
        fctpow[fcnt] = 0;

        while(0 == (tgt % i))
        {
            tgt /= i;
            ++fctpow[fcnt];
        }

        if(0 != fctpow[fcnt])
        {
            ++fcnt;
        }
    }

    if(tgt > 1)
    {
        fctrs[fcnt] = (int)tgt;
        fctpow[fcnt] = 1;
        ++fcnt;
    }
    else
    {
        fctrs[fcnt] = 0;
        fctpow[fcnt] = 0;
    }
}

static __int64 FindGCD(__int64 x, __int64 y)
{
    if(x < y)
    {
        x ^= y;
        y ^= x;
        x ^= y;
    }

    while(0 != (x % y))
    {
        x = (x % y);

        x ^= y;
        y ^= x;
        x ^= y;
    }

    return y;
}

static void Heapify(__int64 * const array, int idx, const int cnt)
{
    int left, right;

    while(true)
    {
        left = (idx << 1) + 1;
        right = (idx << 1) + 2;

        if(cnt <= left)
        {//we have reached the end
            break;
        }

        if(cnt == right)
            right = left;

        if(array[left] < array[right])
            left = right;

        if(array[idx] >= array[left])
        {//everything is in order
            break;
        }

        array[idx] ^= array[left];
        array[left] ^= array[idx];
        array[idx] ^= array[left];

        idx = left;
    }
}

static void HeapSort(__int64 * const array, int cnt)
{
    int i;

    for(i = cnt-1;i >= 0;--i)
        Heapify(array, i, cnt);

    while(cnt > 1)
    {
        //swap first and last element (0 and cnt-1)
        array[0] ^= array[cnt-1];
        array[cnt-1] ^= array[0];
        array[0] ^= array[cnt-1];

        --cnt;
        Heapify(array, 0, cnt);
    }
}

//------------------- Miller-Rabin ------------------------------------------------------------------------------------
static __int64 AxBmodC(const __int64 a, const __int64 b, const __int64 c)
{//we scale down B to parts of <10000 to avoid overflow
    __int64 res = 0;
    __int64 remain = b;
    __int64 tmp;
    int i;
    int count = 0;

    while(remain > 0)
    {
        tmp = remain % 10000;
        remain /= 10000;

        tmp *= a;
        for(i = 0;i < count;++i)
        {
            tmp %= c;
            tmp *= 10000;
        }
        tmp %= c;

        res += tmp;
        res %= c;

        ++count;
    }

    return res;
}

static __int64 ApowBmodC(const __int64 a, const __int64 b, const __int64 c)
{
    if(1 == b)
        return (a % c);

    __int64 res = ApowBmodC(a, b >> 1, c);

    res = AxBmodC(res, res, c);

    if(0 != (b & 1))
    {
        res = AxBmodC(res, a, c);
    }

    return res;
}

const __int64 MRbounds[6] = { 1373653,
                              9080191,
                              4759123141,
                              2152302898747,
                              3474749660383,
                              341550071728321
                            };

const int MRListofA[6][8] = { { 2,  3,  0, 0,  0,  0,  0, 0},
                              {31, 73,  0, 0,  0,  0,  0, 0},
                              { 2,  7, 61, 0,  0,  0,  0, 0},
                              { 2,  3,  5, 7, 11,  0,  0, 0},
                              { 2,  3,  5 ,7, 11, 13,  0, 0},
                              { 2,  3,  5, 7, 11, 13, 17, 0}
                           };

static int MRProbabilityCheck(const __int64 num, const int a, const int s, const __int64 d)
{//Miller-Rabin test with given constant A
    //returns 0 if the number is composite, 1 if it is a probable prime
    //NOTE: s is a very small number (less than 60)
    __int64 tmp;
    int i;

    tmp = ApowBmodC(a, d, num);
    if(1 == tmp)
        return 1;//probable prime

    for(i = 0;(i+1) < s;++i)
    {
        if((tmp+1) == num)
            return 1;//probable prime

        tmp = AxBmodC(tmp, tmp, num);//(a^((2^i)*d) -> (a^((2^(i+1))*d)
    }

    if((tmp+1) == num)
        return 1;//probable prime

    return 0;//definately composite
}

static int MRIsPrime(const __int64 num)
{//Miller-Rabin Primality test (note: num is odd number)
    //returns 0 if the number is composite, 1 if it is a prime
    int res = 1;

    int idx = 0;
    while( (idx < 6) && (num >= MRbounds[idx]) )
    {//find the correct row of test constants a -> (a^((2^s)*d)
        ++idx;
    }

    int s;
    __int64 d;

    s = 0;
    d = num - 1;
    while(0 == (d & 1))
    {
        ++s;
        d >>= 1;
    }

    for(int i = 0;MRListofA[idx][i] != 0;++i)
    {//check with every a
        if(0 == MRProbabilityCheck(num, MRListofA[idx][i], s, d))
        {//there is one composite => the number is composite
            res = 0;
            break;
        }
    }

    return res;
}

static __int64 MRNextPrime(const __int64 num)
{//Generates the next prime number using the Miller-Rabin Primality test
    __int64 crnt;

    //crnt is the next odd number after num
    crnt = num + 1;
    crnt |= 1;

    while(0 == MRIsPrime(crnt))
    {
        crnt += 2;
    }

    return crnt;
}
//---------------------------------------------------------------------------------------------------------------------

int main(int argc, char ** argv)
{
    __int64 target = 1234567891011;

    errat = new char[prmlim];

    int i,j;

    for(i = 0;i < prmlim;++i)
        errat[i] = 0;

    errat[0] = errat[1] = 1;

    for(i = 0;i < prmlim;++i)
    {
        if(0 != errat[i])
            continue;

        for(j = i+i;j < prmlim; j += i)
            errat[j] = 1;
    }

    int factors[20];
    int factpow[20];
    int fcnt = 0;

    for(i = 0;i < 20;++i)
    {
        factors[i] = 0;
        factpow[i] = 0;
    }

    factorize(target, factors, factpow, fcnt);

    delete[] errat;

    int p[6] ;//Pisano periods for the factors (cheat! I know there are 6 prime factors of power 1)
    int x, y;

    for(i = 0;i < fcnt;++i)
    {
        j = 1;

        x = 0;
        y = 1;

        for(;(x != 1)||(y!=0);++j)
        {
            x += y;
            x = (x % factors[i]);

            x ^= y;
            y ^= x;
            x ^= y;
        }

        p[i] = j;
        printf("PI(%d) = %d\n", factors[i], p[i]);
    }

    __int64 PIn = p[0];
    __int64 locgcd;
    for(i = 1;i < 6;++i)
    {
        locgcd = FindGCD(PIn, p[i]);
        PIn *= p[i];
        PIn /= locgcd;
    }

    printf("PI(%I64d) = %I64d\n", target, PIn);


    int Nitms = 100000;
    __int64 * indices = new __int64[Nitms];

    __int64 worknum = 10000000;
    worknum *= worknum;

    printf("Generating Big Primes.\n");
    for(i = 0;i < Nitms;++i)
    {
        worknum = MRNextPrime(worknum);

        indices[i] = (worknum % PIn);
    }
    printf("Done generating Big Primes.\n");

    HeapSort(indices, Nitms);

    __int64 answer = 0;
    __int64 curr = 0;
    __int64 next = 1;
    __int64 fIdx = PIn;

    for(i = Nitms-1;i >= 0;--i)
    {
        while(fIdx > indices[i])
        {
            next -= curr;
            if(next < 0)
                next += target;

            next ^= curr;
            curr ^= next;
            next ^= curr;

            --fIdx;
        }

        answer += curr;
        answer %= target;
    }

    delete[] indices;

    printf("Answer to #304 %I64d\n", answer);

    return 0;
}
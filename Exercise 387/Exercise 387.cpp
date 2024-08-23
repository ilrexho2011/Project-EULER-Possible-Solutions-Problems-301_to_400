#include <iostream>
#include <stdio.h>

#define SIEVE_RANGE (10000000)
#define PRIME_COUNT (664579)
#define DIGIT_COUNT (14)
#define PROBLEM_RANGE (100000000000000)

bool visited[SIEVE_RANGE] = {};
long long prime[PRIME_COUNT] = {}; 

void InitPrimeTable() 
{
    int curr_pos = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++) 
    {
        if (!visited[i]) 
        {
            prime[curr_pos] = i;
            curr_pos++;
            for (long long j = i + i; j < SIEVE_RANGE; j += i) 
            {
                visited[j] = true;
            }
        }
    }
}

bool IsPrime(long long n)
{
    if (n == 1)
    {
        return false;
    }
    for (long long i = 0; i < PRIME_COUNT && (prime[i] * prime[i] <= n); i++)
    {
        if (n == prime[i])
        {
            return true;
        }
        if (n % prime[i] == 0)
        {
            return false;
        }
    }
    return true;
}

// -----------------------------------------------------------------------------

long long total_sum = 0;
int solution_vector[DIGIT_COUNT] = {};

void DebugSolutionVector(int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        std::cout << solution_vector[i];
    }
    std::cout << std::endl;
}

long long GetDigitSum(int dimension)
{
    int sum = 0;
    for (int i = 0; i < dimension; i++)
    {
        sum += solution_vector[i];
    }
    return sum;
}

bool IsHarshadNumber(int dimension)
{
    int sum = GetDigitSum(dimension);
    int r = 0;
    for (int i = 0; i < dimension; i++)
    {
        r = r * 10 + solution_vector[i];
        r %= sum;
    }
    return r == 0;
}

bool IsValid(int dimension)
{
    if (dimension > DIGIT_COUNT)
    {
        return false;
    }
    return IsHarshadNumber(dimension);
}

void Verify(int dimension)
{
    long long n = 0;
    int digit_sum = 0;
    for (int i = 0; i < dimension; i++)
    {
        n = n * 10 + solution_vector[i];
        digit_sum += solution_vector[i];
    }
    if (!IsPrime(n / digit_sum))
    {
        return;
    }
     
    for (long long i = 1; i <= 9; i++)
    {
        long long m = 10 * n + i;
        if (m < PROBLEM_RANGE && IsPrime(m))
        {
            total_sum += m;
        }
    }
}

void Backtrack(int dimension)
{
    if (!IsValid(dimension))
    {
        return;
    }
    Verify(dimension);
    for (int i = 0; i <= 9; i++)
    {
        solution_vector[dimension] = i;
        Backtrack(dimension + 1);
    }
}

void Solve()
{
    for (int i = 1; i <= 9; i++)
    {
        solution_vector[0] = i;
        Backtrack(1);
    }
}

int main(int argc, char* argv[])
{
    InitPrimeTable();
    Solve();
    std::cout << total_sum << std::endl;
    return 0;
}
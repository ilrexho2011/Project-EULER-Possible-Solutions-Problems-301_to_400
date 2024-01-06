#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

int n;
long long possible[21][21];
long long A[21][21] , b[21];

string first(string s , int w)
{
    string ret;
    for(int i = 0 ; i < w ; i++)
        ret += s[i];
    return ret;
}

int common(string a , string b)
{
    for(int d = 0 ; d < b.length() ; d++)
    {
        bool error = false;
        for(int i = 0 ; i + d < b.length() ; i++)
            if(a[i] != b[i + d])
                error = true;
        if(!error)
            return b.length() - d;
    }
    return 0;
}

long long gauss(int r)
{
    if(r == 0)
    {
        assert(b[0] % A[0][0] == 0);
        return b[0] / A[0][0];
    }
    for(int i = 0 ; i < r ; i++)
        if(A[i][r] != 0)
        {
            for(int j = 0 ; j <= r ; j++)
                swap(A[i][j] , A[r][j]);
            swap(b[i] , b[r]);
        }
    for(int i = 0 ; i < r ; i++)
        if(A[i][r] != 0)
        {
            long long t = A[i][r];
            for(int j = 0 ; j <= r ; j++)
                A[i][j] = A[i][j] * A[r][r] - t * A[r][j];
            b[i] = b[i] * A[r][r] - t * b[r];
        }
    return gauss(r - 1);
}

long long solve(long long x)
{
    string s;
    while(x)
        s = char(x % 10 + '0') + s , x /= 10;
    n = s.length();
    memset(possible , 0 , sizeof(possible));
    for(int i = n - 1 ; i >= 0 ; i--)
        for(char c = '0' ; c <= '9' ; c++)
            possible[i][common(s , first(s , i) + c)] += 1;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
            A[i][j] = possible[i][j];
        A[i][i] -= 10;
        b[i] = -10;
    }

    return gauss(n - 1) - s.length() + 1;
}

int main()
{
    long long cnt = 0;
    for(int i = 2 ; i <= 999999 ; i++)
    {
        long long t = solve(10000000000000000LL / i);
        cnt += t;
        if(i % 10000 == 0)
            cout<<i/10000<<"%.."<<endl;
    }
    cout<<cnt<<endl;
    return 0;
}
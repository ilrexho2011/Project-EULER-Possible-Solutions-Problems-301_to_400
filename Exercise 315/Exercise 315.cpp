#include<iostream>
#include<vector>
#include<string>
using namespace std;

int digi1[1<<7];
int mask[11];
int trans[11][11];

bool have[7][11] ={
{1,0,1,1,0,1,1,1,1,1,0},
{1,0,0,0,1,1,1,1,1,1,0},
{1,1,1,1,1,0,0,1,1,1,0},
{0,0,1,1,1,1,1,0,1,1,0},
{1,0,1,0,0,0,1,0,1,0,0},
{1,1,0,1,1,1,1,1,1,1,0},
{1,0,1,1,0,1,1,0,1,1,0}
};

long long calc(vector <int> L)
{
    long long ret = 0;
    for(int i = 1 ; i < L.size() ; i++)
        ret += trans[L[i-1]][L[i]];
    return ret;
}

long long solve(vector <int> L)
{
    int D = 8;
    vector <int> t[11];
    for(int i = 0 ; i < L.size() ; i++)
    {
        for(int j = 0 ; j < D ; j++)
        {
            if(L[i] == 0)
                t[j].push_back(10);
            else
                t[j].push_back(L[i] % 10);
            L[i] /= 10;
        }
    }
    long long ret = 0;
    for(int i = 0 ; i < D ; i++)
        ret += calc(t[i]);
    return ret;
}

int digi_root(int x)
{
    int ret = 0;
    while(x)
    {
        ret += x % 10;
        x /= 10;
    }
    return ret;
}

long long difference(int start)
{
    vector <int> t;
    t.push_back(start);
    while(start >= 10)
    {
        start = digi_root(start);
        t.push_back(start);
    }
    return 2 * solve(t);
}

bool isprime(int x)
{
    for(int i = 2 ; i * i <= x ; i++)
        if(x % i == 0)
            return false;
    return true;
}

int main()
{
    digi1[0] = 0;
    for(int i = 1 ; i < (1<<7) ; i++)
        digi1[i] = digi1[i>>1] + (i & 1);
    memset(mask , 0 , sizeof(mask));
    for(int i = 0 ; i <= 10 ; i++)
        for(int j = 0 ; j < 7 ; j++)
            mask[i] += (1<<j) * have[j][i];
    for(int i = 0 ; i <= 10 ; i++)
        for(int j = 0 ; j <= 10 ; j++)
            trans[i][j] = digi1[mask[i]&mask[j]];
    long long ans = 0;
    for(int i = 10000000 ; i <= 20000000 ; i++)
        if(isprime(i))
        ans += difference(i);
    cout<<ans<<endl;
    return 0;
}
#include<iostream>
using namespace std;

long long n , limit;
long long cost[32];

long long solve(int lim , int room)
{
    limit = lim;
    n = room;
    cost[0] = 0;
    for(int i = 1 ; i <= n + 1 ; i++)
    {
        long long sto = 0 , cnt = 0;
        // the folling 3 lines make the program fast, or it will be TLE.
        long long times = max(0LL , (cost[i-1] + 1 - limit - sto) / (limit - 2) - 3);
        sto += times * (limit - 2);
        cnt += times * limit;
        while(sto + limit - 1 < cost[i-1])
            cnt += limit , sto += limit - 2;
        cnt += cost[i-1] - sto + 1;
        cost[i] = cnt;
        if(cost[i-1] < limit)
            cost[i] = cost[i-1] + 1;
    }
    return cost[n + 1];
}

int main()
{
    int a , b;
    long long ans = 0;
    for(int i = 3 ; i <= 40 ; i++)
        ans += solve(i , 30);
    cout<<ans<<endl;
    return 0;
}
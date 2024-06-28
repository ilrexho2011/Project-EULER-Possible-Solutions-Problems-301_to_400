long long ret = 0;
    for(int i = 0 ; i < LimitP3 ; i++)
        if(lowbit(x) * p3[i] <= x)
            ret += way((x - lowbit(x) * p3[i]) >> 1 , i);
    if(ret > 2) ret = 2;
    mem[x][LimitP3] = ret;
    return ret;
}

bool isprime[1000001];

long long solve(long long x)
{
    long long ret = 0;
    for(int i = 1 ; i <= x ; i++)
        if(isprime[i])
            if(way(i , 20) == 1)
                ret += i;
    return ret;
}

int main()
{
    memset(mem , 0xff , sizeof(mem));
    memset(isprime , true , sizeof(isprime));
    isprime[1] = false;
    for(int i = 2 ; i <= 1000000 ; i++)
        if(isprime[i])
            for(int j = i + i ; j <= 1000000 ; j += i)
                isprime[j] = false;
    for(int i = 1 ; i <= 20 ; i++)
        p2[i] = p2[i-1] * 2 , p3[i] = p3[i-1] * 3;
    int n;
    cout << solve(1000000) << endl;
    system("pause");
    return 0;
}
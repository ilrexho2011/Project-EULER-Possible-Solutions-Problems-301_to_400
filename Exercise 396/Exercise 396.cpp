#include <stdio.h>
#include <math.h>
#include <map>
#include <stdlib.h>
#define ll long long
using namespace std;

ll digs[5];
int nd;
void recomputedigs(ll n,ll k)
{
    nd = 0;
    while(n)
    {
        digs[nd++]=(n%k);
        n/=k;
    }
    
}



#define MODD 1000000000

int twopowmod[MODD+1];


ll findit(ll x,ll k)
{
    // x*2^x*2^2^x*...
    ll twoexp = x%MODD;
    for(int j=1;j<=k;j++)
    {
        twoexp=(twoexp*twopowmod[twoexp])%MODD;
        //printf("%lld\n",twoexp);
    }
    return twoexp-3;
    
}

ll g(ll n)
{

    recomputedigs(n,2);
    //printdigs();
    ll base = 2;
    ll answer = 0;
    ll morestep=0;
    while(1)
    {
        if(nd==1)
            return answer+digs[0];
        
        if(nd==2)
        {
            ll x = digs[0];
            return answer+(x+1)*((1ll<<(x+1))-1)-1;
        }
        
        if(nd==3 && digs[0]==digs[1] && digs[1]==digs[2])
        {
            return findit(digs[0]+1,digs[0]+1);

        }
        
        ll step = digs[0];

        //printf("%d\n",step+1);
        base+=step+1;
        answer+=step+1;
        digs[0]=0;
        ll number = 0;
        for(int d=nd-1;d>=0;d--)
            number=number*(base)+digs[d];
        number--;
        recomputedigs(number,base);

    }
    return answer;
}



int main()
{
    twopowmod[0]=1;
    for(int i=1;i<=MODD;i++)
    {
        twopowmod[i]=(twopowmod[i-1]*2)%MODD;
    }

    
    ll summ = 4;

    for(ll n=3;n<16;n++)
    {
        int nz = 0;
        ll nn = n;
        ll currans=g(n);
        summ+=currans;
    }
    printf("%lld\n",summ);
    
}
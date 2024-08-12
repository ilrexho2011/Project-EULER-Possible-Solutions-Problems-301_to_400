#include<stdio.h>
#include<math.h>

#define M 1000005

long long mu[M+1];
long long phi[M+1];


void precalc()
{
    long long i,j;
    for(i=1;i<=M;i++)
    {
        mu[i]=1;
        phi[i]=i;
    }
    for(i=2;i<=M;i++)
        if(phi[i]==i)
        for(j=i;j<=M;j+=i)
        {

            phi[j]=(phi[j]/i)*(i-1);
            if(j/i%i==0)
                mu[j]=0;
            else
                mu[j]=-mu[j];
        }
}

long long F(long long N,long long n,long long m)
{
    long long i,m1,n1,s,t,ans=0;
    if(n>m||n>N)
        return 0;
    if(m>N)
        m=N;
    s = sqrt(N);
    t = N/(1+s);
    if(n<=t&&m<=t)
        {
            for(i=n;i<=m;i++)
                ans+=N/i;
            return ans;
        }
    m1 = N/m;
    if(n<=t&&m>t)
        {
            for(i=n;i<=t;i++)
                ans+=N/i;
            for(i=s;i!=m1;i--)
                ans+=i*(N/i-N/(i+1));
            ans+=m1*(m-N/(m1+1));
            return ans;
        }
    n1 = N/n;
    if(n1==m1)
        {
            ans+=n1*(m-n+1);
            return ans;
        }
    ans = n1*(N/n1-n+1)+ m1*(m-N/(1+m1));
    for(i=m1+1;i<n1;i++)
        ans+=i*(N/i-N/(i+1));
    return ans;
}

long long ans(long long m)
{
    long long a,i,n,result=0;
    a=sqrt(m);
    for(i=1;i<=a;i++)
        if(mu[i]!=0)
            for(n=i;n<=a;n+=i)
                result+=mu[i]*F(m/(n*i),1+n/i,m/(i*i));
    return result;
}

int main()
{
    precalc();
    printf("%lld\n",1000000000000LL+ans(1000000000000LL));
    return 0;
}

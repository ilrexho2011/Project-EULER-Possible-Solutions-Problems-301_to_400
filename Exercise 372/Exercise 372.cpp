#include <cstdio>
#include <cmath>
#include <ctime>
using namespace std;

typedef long long LL;
const double eps=1e-9;

LL sum(int n,double x) // accuracy issues
{
        if(n==0) return 0;
        if(x>=1-eps)
        {
                LL q=LL(x+eps);
                LL ans=LL(n)*(n+1)/2*q+sum(n,x-q);
                return ans;
        }
        int m=n*x+eps;
        LL ans=LL(n)*m-sum(m,1./x);
        return ans;
}

int gcd(int a,int b)
{
	int c;
	while(b) c=a%b,a=b,b=c;
	return a;
}

int d;

LL brute(int n,double a)
{
	LL ans=0;
	for(int x=1;x<=n;x++)
		ans+=LL(LL(x)*a+eps);
	return ans;
}

LL func(LL a,LL b,LL c)
{
	LL q=(a+b*sqrt(1.*d))/c+eps;
	return q;
	LL L=q-5;
	if(L<0) L=0;
	LL R=q+5;
	while(L+1<R)
	{
		LL M=(L+R)/2;
		LL e=c*M-a;
		if(b<=0 && e>=0) R=M; else
		if(b>0 && e<0) L=M; else
		if(b>=0 && e>=0)
		{
			if(b*b>=e*e/d) L=M; else R=M;
		}
		else
		{
			if(b*b*d<=e*e) L=M; else R=M;
		}
	}
	return L;
}

LL sumD(int n,int a,int b,int c)
{
	if(n<=10) return brute(n,(a+b*sqrt(d*1.))/c);
	if(c<0) a=-a,b=-b,c=-c;
	int g=gcd(gcd(a,b),c);
	if(g>1) a/=g,b/=g,c/=g;
	int q=int((a+b*sqrt(d*1.))/c+eps);
	if(q>0)
	{
		LL ans=LL(n)*(n+1)/2*q+sumD(n,a-q*c,b,c);
		return ans;
	}
	int m=int((a+b*sqrt(d*1.))/c*n+eps);
	LL ans=LL(n)*m-sumD(m,c*a,-c*b,a*a-b*b*d);
	return ans;
}

LL sum(int L,int R,int k)
{
	double x=sqrt(k+0.);
	int kx=x+eps;
	if(kx*kx==k) return LL(R-L)*(R+L+1)/2*kx;
	d=k;
	return sumD(R,0,1,1)-sumD(L,0,1,1)+R-L;
}

int main()
{
	LL M=2e6,N=1e9;
	int c=N/M;
	LL ans=0;
	for(int k=1;k<=c*c;k+=2)
	{
		int N0=N/sqrt(k+0.)+eps;
		int N1=N/sqrt(k+1.)+eps;
		ans+=sum(M,N1,k+1)+LL(N0-N1)*(N+1);
		ans-=sum(M,N0,k);
	}
	printf("%lld\n",ans);
	return 0;
}
#include <stdio.h>
#include <time.h>

#define inf 1000000000
typedef __int64 LL;

clock_t start=clock();

#define N 1010101
int minp[N];

LL deg(LL n,int p)
{
	LL s=0;
	for(;n;n/=p) s+=n/p;
	return s;
}

void update(int p,int d,LL &n)
{
	LL L=n-1;
	LL R=LL(inf)*inf;
	while(L+1<R)
	{
		LL M=(L+R)/2;
		LL dd=deg(M,p);
		if(dd>=LL(1234567890)*d) R=M; else L=M;
	};
	n=R;
}

LL MOD=LL(inf)*inf;

int main()
{
	//freopen("out.txt","w",stdout);
	int i,j;
	for(i=2;i<N;i++) if(!minp[i])
		for(j=i;j<N;j+=i) if(!minp[j]) minp[j]=i;
	LL n=1;
	LL ans=0;
	for(i=1;i<=1000000;i++)
	{
		for(j=i;;)
		{
			if(j==1) break;
			int q=minp[j];
			update(q,deg(i,q),n);
			for(;j%q==0;j/=q);
		}
		if(i>=10) ans=(ans+n)%MOD;
	}
	printf("%I64d\n",ans);
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	return 0;
}
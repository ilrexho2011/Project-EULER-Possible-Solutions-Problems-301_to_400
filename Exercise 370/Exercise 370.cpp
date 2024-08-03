#include <cstdio>
#include <cmath>

typedef long long LL;
const double eps=1e-9;
#define max(a,b) ((a)>(b)?(a):(b))

const int sqP = 5000000;
const LL P = LL(sqP)*sqP;
const int N = 1000;
const int NN = 6*N*N; // (3+sqrt(5.))*N*N;
int num[NN];
const int M = max(P/N/N/3,sqP)+5;
char a[M];
char mu[M];
const int NX = max(sqP/2,N)+5; // sqP/sqrt(3+sqrt(5));
LL sx[NX];

int main()
{
	double phi=(1+sqrt(5.))/2;
	int i,j;
	for(i=1;i<M;i++) mu[i]=1;
	for(i=2;i<M;i++) if(!a[i])
		for(j=i;j<M;j+=i)
		{
			a[j]=1;
			if(j/i%i) mu[j]=-mu[j]; else mu[j]=0;
		}
	int n,x;
	for(n=1;n<=N;n++)
	for(x=n;x<n*phi-eps;x++)
		num[n*n+n*x+x*x]++;
	LL ans=0;
	for(n=1;n<NN;n++)
		if(num[n])
		{
			LL p=P/n;
			LL sqp=sqrt(p+0.)+eps;
			LL cur=0;
			for(i=1;i<=sqp;i++) if(mu[i])
			{
				if(mu[i]>0)
					cur+=p/(LL(i)*i);
				else
					cur-=p/(LL(i)*i);
			}
			ans+=num[n]*cur;
		}
	sx[N]=0;
	for(n=N+1;n<NX;n++)
		sx[n]=sx[n-1]+int((sqrt(5.)-1)/2*n)+1;
	int maxs=P/3/(N+1)/(N+1);
	for(int s=1;s<=maxs;s++) if(mu[s])
	{
		LL Ps=P/s;
		int nx=max(sqrt(Ps/(3+sqrt(5.)))+eps,N)+1;
		for(;;)
		{
			int xx=nx*phi;
			if(LL(nx)*(nx+xx)+LL(xx)*xx>Ps) break;
			nx++;
		}
		ans+=sx[nx-1];
		int maxn=sqrt(Ps/3.)+eps;
		for(n=nx;n<=maxn;n++)
			ans+=int((sqrt(4*Ps-3*LL(n)*n+0.)-n)/2.+eps)-n+1;
	}
	printf("%lld\n",ans);
	return 0;
}
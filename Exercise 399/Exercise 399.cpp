#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAXP 165000000
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;

char sieve[MAXP];
int prime[10640000];
int primes;

void createsieve() {
	int i,j,q;
	memset(sieve,1,sizeof(sieve));
	q=sqrt(MAXP);
	for(sieve[0]=sieve[1]=0,i=2;i<=q;i++) if(sieve[i]) for(j=i*i;j<MAXP;j+=i) sieve[j]=0;
}

void genprimes() {
	int i;
	for(primes=i=0;i<MAXP;i++) if(sieve[i]) prime[primes++]=i;
}

#define MAX 165000000
#define FIND 100000000

/*#define MAX 50000
#define FIND 200*/

typedef unsigned char uchar;

uchar fibsieve[MAX];

ll M[2][2],Z[2][2];

ull ullmulmod(ull a,ull b,ull mod) {
	ull r=0,t;
	if(a>=mod) a%=mod;
	if(b>=mod) b%=mod;
	if(a>b) t=a,a=b,b=t;
	while(b) {
		if(b&1) {
			r+=a;
			if(r>=mod || r<a) r-=mod;
		}
		a=(a<<1)%mod;
		b>>=1;
	}
	return r;
}

void matrixmulmod(ll a[2][2],ll b[2][2],ll mod,ll r[2][2]) {
	ll x[2][2];
	int i,j,k;
	for(i=0;i<2;i++) for(j=0;j<2;j++) {
		x[i][j]=0;
		for(k=0;k<2;k++) {
			x[i][j]=x[i][j]+ullmulmod(a[i][k],b[k][j],mod);
			if(x[i][j]>=mod) x[i][j]-=mod;
		}
	}
	for(i=0;i<2;i++) for(j=0;j<2;j++) r[i][j]=x[i][j];
}

void matrixpowmod(ll a[2][2],int N,ll mod,ll r[2][2]) {
	int i,j;
	ll b[2][2],x[2][2];
	if(!N) {
		for(i=0;i<2;i++) for(j=0;j<2;j++) r[i][j]=(i==j);
		return;
	}
	for(i=0;i<2;i++) for(j=0;j<2;j++) x[i][j]=(i==j),b[i][j]=a[i][j];
	while(1) {
		if(N&1) matrixmulmod(x,b,mod,x);
		N>>=1;
		if(!N) break;
		matrixmulmod(b,b,mod,b);
	}
	for(i=0;i<2;i++) for(j=0;j<2;j++) r[i][j]=x[i][j];
}

int solve(int n) {
	ll MOD=10000000000000000LL,dig;
	double rot=(sqrt(5)+1)*.5,L;
	printf("found index %d\n",n);
	/* find last 16 digits */
	M[0][0]=0; M[0][1]=1;
	M[1][0]=1; M[1][1]=1;
	matrixpowmod(M,n-1,MOD,M);
	printf("%I64d,",M[1][1]%MOD);
	/* first first 2 digits + number of digits:
	   fib(n) approx = ((1+sqrt(5))/2)^n / sqrt(5)
		 log(fib(n)) = 1/sqrt(5) * n*log(1+sqrt(5))/log(10)
	*/
	L=n*log(rot)/log(10)-log(sqrt(5))/log(10);
	dig=ceil(L);
	L-=dig;
	printf("%.1fe%I64d\n",10*pow(10,L),dig-1);
	return 0;
}

int main() {
	int i,j,k,iter,count;
	int p;
	ll P;
	createsieve();
	genprimes();
	memset(fibsieve,1,MAX);
	for(i=0;i<primes;i++) if(prime[i]>=MAX) break;
	primes=i;
	#pragma omp parallel for private(p,P,M,j,k,Z,iter) schedule(static,1)
	for(i=0;i<primes;i++) {
		p=prime[i];
		if(i%50000==0) printf("%d ",p);
		P=(ll)p*p;
		/* find p-th power of matrix */
		M[0][0]=0; M[0][1]=M[1][0]=M[1][1]=1;
		matrixpowmod(M,p,P,M);
		/* Z is our running product */
		for(j=0;j<2;j++) for(k=0;k<2;k++) Z[j][k]=M[j][k];
		for(iter=p;iter<MAX;iter+=p) {
			if(Z[0][1]%P==0) {
				/* found our first match, cross out multiples */
				fibsieve[iter]=0;
				for(k=iter*2;k<MAX;k+=iter) fibsieve[k]=0;
				break;
			}
			matrixmulmod(M,Z,P,Z);
		}
	}
	printf("\n");
	/* find index of 100,000,000th squarefree fibonacci number */
	for(count=0,i=1;i<MAX;i++) {
		if(fibsieve[i]) {
			if(++count==FIND) return solve(i);
		}
	}
	printf("please increase MAX, found only %d squarefree\n",count);
	return 0;
}
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAXP 100000001
typedef long long ll;
int sieve2[MAXP];
void fsieve() {
  int q=sqrt(MAXP),i,j;
  memset(sieve2,0,sizeof(sieve2));
  sieve2[0]=sieve2[1]=0;
  for(i=2;i<=q;i++) if(sieve2[i]<1) for(j=i*i;j<MAXP;j+=i) if(!sieve2[j]) sieve2[j]=i;
}
void ffactor(int n,int *f,int *fc,int *fn) {
	*fn=0;
	while(sieve2[n]) {
		if(*fn && f[*fn-1]==sieve2[n]) fc[*fn-1]++,n/=sieve2[n];
		else f[*fn]=sieve2[n],fc[(*fn)++]=1,n/=sieve2[n];
	}
	if(n>1) {
		if(*fn && f[*fn-1]==n) fc[*fn-1]++;
		else f[*fn]=n,fc[(*fn)++]=1;
	}
}
#define MAXPR 100000
int plen[MAXPR];
int prof[MAXPR][32];
int pans[MAXPR];
int pn;
int compi(const void *A,const void *B) {
	const int *a=A,*b=B;
	if(*a>*b) return -1;
	if(*a<*b) return 1;
	return 0;
}
int solve(int n,int *fc,int fn) {
	int i,j,k;
	int dp[32][32];
	if(fn==1) return 1;
	for(i=0;i<pn;i++) if(plen[i]==fn) {
		for(j=0;j<fn;j++) if(prof[i][j]!=fc[j]) goto fail;
		return pans[i];
	fail:;
	}
	/*	pick objects from multiset fc[] */
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(i=0;i<fn;i++) {
		for(j=0;j<32;j++) if(dp[i][j]) {
			if(i==fn) continue;
			/*	pick k */
			for(k=0;k<=fc[i];k++) dp[i+1][j+k]+=dp[i][j];
		}
	}
	j=0;
	for(i=0;i<32;i++) if(j<dp[fn][i]) j=dp[fn][i];
	plen[pn]=fn;
	pans[pn]=j;
	for(i=0;i<fn;i++) prof[pn][i]=fc[i];
	pn++;
	return j;
}

int main() {
	int i,v;
	int f[32],fc[32],fn;
	ll sum=0;
	pn=0;
	fsieve();
	for(i=1;i<=100000000;i++) {
		if(i==1) { sum++; continue; }
		ffactor(i,f,fc,&fn);
		qsort(fc,fn,sizeof(int),compi);
		v=solve(i,fc,fn);
		sum+=v;
	}
	printf("%I64d\n",sum);
	return 0;
}
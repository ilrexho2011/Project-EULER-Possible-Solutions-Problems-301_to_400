#include <iostream>
#include <stdio.h>
using namespace std;
#define max 10000000
int c[max];
int p[max], pcount;
int d[max+10];
typedef unsigned long long ULL;
void isprime(int n)
{
	int i;

	for(i=0;(i<pcount)&&(p[i]*p[i]<=n);i++)
		if(n%p[i]==0) return;
	p[pcount++]=n;
	return;
}

int devides(int n, int p, int q)
{
	
	while(n%p==0) n/=p;
	while(n%q==0) n/=q;
	if(n!=1) return 0;
	return 1;
}

int main()
{
	register int i, j;
	p[pcount++]=2;
	for(i=3;i<max;i+=2)
		isprime(i);
	ULL sum=0, n;
	cout<<" pcount "<<pcount<<endl;
	for(i=0;p[i]*2<=max;i++){
		for(j=i+1;p[i]*p[j]<=max;j++){
			for(n=(max/(p[i]*p[j]))*p[i]*p[j];n>=p[i]*p[j];n-=p[i]*p[j]){
				if(devides(n, p[i], p[j])){
					sum+=n;
					break;
				}
			}
		}
	}
	cout<<" final sum "<<sum<<endl;
	
	return 0;
}
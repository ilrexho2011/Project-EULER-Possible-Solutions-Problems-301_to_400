#include <iostream>
#include <cstdlib>
#include <cmath>
#include<time.h>
using namespace std;

int i,WN,W2N;				
long long int GR=10000000000,WGR,N,M,MOD=1000000000,IA,IS[100010],IR[100010];
double start,DA,DS[100010],DR[100010];
/*
based on the formula:  
R[N]= F[N] - som(d=2 t/m d=floor(SQRT(N)), R[N/d])  - som(m=1 t/m m=floor(N/floor(SQRT[N]))-1,  R[m]*(floor(N/m) - floor(N/(m+1)))
*/
int main()
{
cout.precision(15);
start=clock();
WGR=ceil(sqrt((double)GR));
IR[1]=7;DR[1]=7.0;
for(N=2;N<=WGR;N++){
	DA=pow((N+1),3.0)-1.0;
	IA=(N+1)*(N+1);IA%=MOD;IA*=(N+1);IA--;IA%=MOD;if(IA<0)IA+=MOD;
	WN=floor(sqrt((double)N));
	if(WN>=2){
		for(i=2;i<=WN;i++){
			DA-=DR[N/i];
			IA-=IR[N/i];
		}
		while(IA<0)IA+=MOD;
	}
	W2N=N/WN-1;
	for(i=1;i<=W2N;i++){
		DA-=DR[i]*(double)(N/i-N/(i+1));
		IA-=IR[i]*(N/i-N/(i+1));
	}
	while(IA<0)IA+=MOD;
	DR[N]=DA;
	IR[N]=IA;
}

for(M=WGR;M>=1;M--){
	N=GR/M;
	DA=pow((double)(N+1),3.0)-1.0;
	IA=(N+1);IA%=MOD;IA*=(N+1);IA%=MOD;IA*=(N+1);IA--;IA%=MOD;if(IA<0)IA+=MOD;
	WN=floor(sqrt((double)N));
	for(i=2;i<=WN;i++){
		if(N/i>WGR){
			DA-=DS[i*M];
			IA-=IS[i*M];
		}
		else{
			DA-=DR[N/i];
			IA-=IR[N/i];
		}
	}
	while(IA<0)IA+=MOD;
	W2N=N/WN-1;
	for(i=1;i<=W2N;i++){
		DA-=DR[i]*(double)(N/i-N/(i+1));
		IA-=IR[i]*(N/i-N/(i+1));
	}
	while(IA<0)IA+=MOD;
	DS[M]=DA;
	IS[M]=IA;
}
cout<<"DS[1] = "<<DS[1]<<" IS[1] = "<<IS[1]<<"\n";

cout<<clock()-start;
return 0;
}
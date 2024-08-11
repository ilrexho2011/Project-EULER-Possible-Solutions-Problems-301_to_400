#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ll long long

inline int MIN(int x1, int y1) { return x1 <= y1 ? x1 : y1; }

int *tdv0(int N1) {
	int N2=N1+1, N0, n1, n2, i1, *lr1, *lr2;
	N0=sqrt(N2);
	lr1=(int *)calloc(N2+1,sizeof(int));lr1[1]=1; for(i1=2;i1<N2+1;i1++) lr1[i1]=2;
	for (n1=2;n1<N0+1;n1++) {
		for(n2=n1*2;n2<MIN(n1*N0+1,N2+1);n2+=n1) lr1[n2]++;
		for(n1*N0+n1;n2<N2+1;n2+=n1) lr1[n2]+=2;
	}
	lr2=(int *)calloc(N1+1,sizeof(int));lr1[1]=1;
	for(n1=1;n1<N1/2+1;n1++) {
		n2=2*n1; lr2[n2-1]=lr1[n2-1]*lr1[n1]; lr2[n2]=lr1[n1]*lr1[n2+1];
	}
	free(lr1);
	return lr2;
}

int rft1(int i1, int *ft1) {
	int sm1=0;
	while (i1) {
		sm1+=ft1[i1];
		i1-=i1&(-i1);
	}
	return sm1;
}

void uft1(int i1, int *ft1, int N1) {
	while (i1<N1) {ft1[i1]++; i1+=i1&(-i1);}
}


ll p378(int N1, ll M1)	{
	int i1, n1, *ft1, *lr1, *lr2, *lt1;
	ll cn1=0, n2;
	lt1=tdv0(N1);
	ft1=(int *)calloc(N1+1,sizeof(int)); lr1=(int *)calloc(N1+1,sizeof(int));
	for (i1=N1;i1>0;i1--) { lr1[i1]=rft1(lt1[i1]-1,ft1); uft1(lt1[i1],ft1, N1); }
	ft1=(int *)calloc(N1+1,sizeof(int)); 
	for (i1=1;i1<N1+1;i1++) { n1=i1-rft1(lt1[i1],ft1)-1;  if (n1) {n2=n1; n2*=lr1[i1]; cn1=(cn1+n2)%M1; } uft1(lt1[i1],ft1, N1);  }
	return cn1%M1;
}

int main() {
	clock_t	sttm;
	int N1=60000000;
	ll cn1=0, M1=1000000;

	sttm=clock();
	M1*=M1; M1*=1000000;
	cn1=p378(N1,M1);

	printf("\nThe count is %lld\n",cn1);
	printf("\nTime taken %.4f seconds\n",(float)((clock()-sttm)/1000.0));
}
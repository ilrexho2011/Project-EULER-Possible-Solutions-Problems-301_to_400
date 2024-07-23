
#include <cstdio>
typedef unsigned long long ull;
#include "divisors_of.h"

ull const N=71328803586048llu;
size_t const L=1e8;


size_t P(ull f, ull r)
{
	size_t n=0;

	if(f==2 && r==1)
		n=2;
	else if(f==1)
	{
		if(r%2==0)
			n=r/2%L*((r+1)%L)%L;
		else n=r%L*(((r+1)/2)%L)%L;
	}
	else if((f%2==1) && (r==1))
	{
		ull d=(f/2)%L;
		n=(2*d*(d+1))%L;
	}
	else if((f%2==0) && (r==1))
		n=(P(f-1, 1)+ f%L)%L;
	else if((f%2==1) && (r==2))
		n=(P(f, r-1)+1)%L;
	else if((f==2) && (r%2==0))
		n=(P(f+1, r)+ 2)%L;

	else if((f%2==0) && (r%2==0))
	{
		ull d=((f-2)/2)%L;
		n=(P(2, r+(f-2))+ d)%L;
	}
	else if((f%2==1) && (r%2==0))
	{
		ull d=((r-2)/2)%L;
		n=(P(f+(r-2), 2)+ d)%L;
	}
	else if((f%2==0) && (r%2==1))
	{
		ull d=((r-1)/2)%L;
		n=(P(f+r-1, 1)+ d)%L;
	}
	else if((f%2==1) && (r%2==1))
		n=(P(f-1, r)+ (f-1)%L)%L;

	return n;
}


int main()
{
	size_t a=0;
	divisors<ull> D(N);
	for(size_t i=0; i<D.size(); ++i)
	{
		ull f=D[i];
		ull r=N/f;
		size_t p=P(f, r);
		a=(a+p)%L;
	}

	printf("N=%llu, r=%zu\n", N, a);
	return 0;
}

#include<stdio.h>
#include<primes.h>

int p=1,pc=10001,b,blast=1;
long long int steps=0;

// sum(d=b..n-1, floor(n/d)), (global) b is set to largest divisor of n
/*
long long int g(int n){
  long long int s=0; 
  int x;
  b=n;while(--b){s+=x=n/b;if(x*b==n)break;}
  return s;
}
*/
long long int g(int n){
  int x,b0,p=is_prime(n);
  long long int s=p?n:0;
  b0=n-1;
  for(x=2;;x++,b0=b) {
    b=n/x;
    s+=(b0-b)*(x-1);
    if(p) {
      if(b>=x) s+=b;
      if(b<=x) {b=1;return s;}
    }
    else 
      if(b*x==n) return s+x;
  }
}

void next(int n) {
  steps+=2*g(n)+n-2+(6*n+2ll)*(n-b)+blast;
  blast=b;
  // up to prime positions sum(blast)=sum(b)
  // so for PE 308 we could simply write b instead of blast
}

int main() {
  alloc_sieve(200000);
  sieve_primes();

  while(pc--)
    do next(++p); while(!is_prime(p));
 
  printf("\n%lld\n",steps);
}
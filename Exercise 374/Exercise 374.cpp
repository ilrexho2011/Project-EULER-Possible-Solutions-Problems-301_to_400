#include <iostream>
#include <cmath>
#include <map>
#include <ctime>
using namespace std;

long long mod = 982451653;
long long limit=100000000000000LL;
map<long long,long long> fact;


long long powMOD(long long a, long long b, long long MOD) {
     long long x = 1, y = a;
	while(b > 0) {
		if(b%2 == 1) {
			x=(x*y);
			if(x>MOD) x%=MOD;
		}
		y = (y*y);
		if(y>MOD) y%=MOD;
		b /= 2;
	}
	return x;
}

long long factMOD(long long n, long long MOD){
    long long orig = n;
    if (n==0) return 1;
    if ( fact.find(n-1) == fact.end() ) {
       long long res = 1;
       while (n > 1)
       {
          res = (res * powMOD(MOD - 1, n/MOD, MOD)) % MOD;
          for (int i=2, j=n%MOD; i<=j; i++)
             res = (res * i) % MOD;
          n/=MOD;
       }
       fact[orig] = res;
       return fact[orig];
    }
    else {
         fact[n] = (fact[n-1]*n)%MOD;
         return fact[n];
    }
}

long long modInverse(long long a, long long m) {
    return powMOD(a,m-2,m);
}

long long a(long long n){
     long long m = (long long)(sqrt(8*n+1)-1)/2;
     long long T = m*(m+1)/2;
     long long l = n - T;

     if (0<=l && l<=(m-2))
          return (factMOD(m+1,mod)*modInverse(m-l,mod) % mod)*(m-1) % mod;
     else if (l==(m-1))
          return (factMOD(m,mod)*modInverse(2,mod) % mod)*(m+2)*(m-1) % mod;
     else if (l==m)
          return (factMOD(m+1,mod) % mod)*m % mod;
}


int main(){          
    clock_t startT, endT;
    startT = clock();
    
    long long sum=0, g=1, finalTermN=3, finalTermBase=1,n=4,step=3;
    long long stirling=1, stirlingN=2, stirlingFactorial=1, finalTerm;

    //greedy algorithm
    while (n<=limit){
          stirlingFactorial =(stirlingFactorial*stirlingN % mod) % mod;
          stirling =(stirling*(stirlingN+1)+stirlingFactorial % mod) % mod;
          finalTermBase = finalTermBase % mod;
          finalTerm = finalTermBase*(finalTermN+1) % mod;
          sum += g*(stirling+finalTerm) % mod;
          finalTermBase*=finalTermN % mod;
          step+=1, n+=step, g+=1, finalTermN+=1, stirlingN+=1;
    }
    
    n-=step;

    //manually calculate the final straggler values
    while (n < limit){
          n+=1;
          sum+=a(n)%mod;   
    }

    //add one to compensate for n=1 edge case
    
    endT = clock();   
    double diff = 0.001*((double)endT-(double)startT);
    cout << (sum+1) % mod << endl;
    cout << diff << endl;

    return 0;
}

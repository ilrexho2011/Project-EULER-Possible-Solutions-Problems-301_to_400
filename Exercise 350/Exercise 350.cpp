#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define LL long long
const LL G = 1000000;
const LL L = G*G;
const LL N = L*G;
const LL modulo = 101*101*101*101;
int tot;

LL Pow(LL a,LL b,LL c)
{
	if (b==0) return 1;
	if (b==1) return a%c;
	LL res = Pow(a,b/2,c);
	res=res*res % modulo;
	if (b%2==1) res=res*(a%c)%c;
	return res;
}

LL rec[1000];
LL PPow(LL a,LL b,LL c)
{
	return rec[a];
}
LL Calc(LL a,LL n)
{
	LL t=a,tp=0;
	LL res = 1;
	for (int i=2;i*i<=t;i++)
	if (t%i==0)
	{
		int k=0;
		tp++;
		while(t%i==0) {t/=i;k++;}
		LL temp = PPow(k+1,n,modulo);
		temp -= PPow(k,n,modulo)*2;		
		temp += PPow(k-1,n,modulo);
		temp = (temp%modulo+modulo)%modulo;
		res = res * temp % modulo;
		if (t==1) break;
	}
	if (t>1) 
	{
		tp++;
		LL temp = PPow(2,n,modulo);
		temp -= 2;
		temp = (temp%modulo+modulo)%modulo;		
		res = res * temp % modulo;
	}
	return res;
}
LL S[G+5];
int main()
{
	for (int i=1;i<1000;i++) rec[i]=Pow(i,N,modulo);
	S[0]=0;
	for (int i=1;i<G+5;i++)
	{
		S[i] = Calc(i,N);
	//	cout << i << " " << S[i] << endl;
		S[i] += S[i-1];
		S[i] %= modulo;
	}
	LL ans=0;
//	for (LL i=G;i<=L;i++)
	for (LL s=1;s<=G;s++)
	{
		//s<=L/i<(s+1)
		LL si = L/(s+1);
		LL ti = L/s;
		ans += S[s]*((ti-si)%modulo);
	//	cout << L/i << ":" << S[L/i] << endl;
		ans %= modulo;
	}
	cout << ans << endl;
	return 0;
}
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef vector<int> VI;

const int MOD = 1000000000;

LL pow2(int n)
{
	LL p=1;
	LL a=2;
	for(;n;)
	{
		if(n%2) p=LL(p)*a%MOD;
		if(n/=2) a=LL(a)*a%MOD;
	}
	return p;
}

const int P = 33;
LL prf[2][P];

LL pref(int n,int j)
{
	if(n==0) return 0;
	int k=0;
	for(int m=n;m>1;m/=2) k++;
	n-=1<<k;
	return (prf[j][k]*pow2(n)+pref(n,!j))%MOD;
}

LL substr(int L,int R,int j)
{
	LL ans=(pref(R,j)-pref(L,j)*pow2(R-L))%MOD;
	if(ans<0) ans+=MOD;
	return ans;
}

const int H = 26;
int f[1<<H];

int rec(int i,int h)
{
	if(h<=H)
		return f[i]>>(H-h);
	if(i<(1<<(h-1))) return 2*rec(i,h-1);
	return 2*rec((1<<h)-1-i,h-1)-1;
}

int solve(int k,int n)
{
	int p=1,h=0;
	for(;p<k/2;p*=2) h++;
	for(int i=0;i<p;i++)
	{
		int x=rec(i,h);
		int cnt=3-(x>=k-p)-(x>=k-p/2);
		if(n>cnt) n-=cnt; else
		{
			vector<string> ss;
			int mrs=0;
			for(int m=p-x;m;m-=m&-m) mrs^=1;
			if(mrs)
			{
				if(x+p<k) {
					ss.push_back("001");
					ss.push_back("010");
					ss.push_back("011");
				} else {
					ss.push_back("00");
					ss.push_back("01");
				}
			}
			else
			{
				if(x+p<k) {
					ss.push_back("100");
					ss.push_back("101");
					ss.push_back("110");
				} else {
					ss.push_back("10");
					ss.push_back("11");
				}
			}
			int L=0,R=ss.size();
			if(x>=k-p/2)
			{
				if(i>0 && rec(i-1,h)==x-p/2) L++; else R--;
			}
			string need=ss[L+n-1];
			LL ans=LL(substr(p-x,p,need[0]-'0'))*pow2(k-x)%MOD;
			int z;
			if(x+p<k)
			{
				ans+=prf[need[1]-'0'][h]*pow2(k-p-x)%MOD;
				z=k-p-x;
			}
			else z=k-x;
			ans+=pref(z,need[need.size()-1]-'0');
			ans%=MOD;
			return ans;
		}
	}
	return -1;
}

int solve(LL n)
{
	n-=1+2+3;
	for(int k=2;;k++)
	{
		LL p=1LL<<(k-2);
		LL cur=(4*p+1)*p;
		if(n>cur) n-=cur; else
		{
			LL L=0;
			LL R=p;
			while(L+1<R)
			{
				LL t=(L+R)/2;
				LL s=(3*p+t+1)*t;
				if(s<n) L=t; else R=t;
			}
			n-=(3*p+L+1)*L;
			return solve(2*p+R+1,n);
		}

		cur=(11*p+1)*p/2;
		if(n>cur) n-=cur; else
		{
			LL L=0;
			LL R=p;
			while(L+1<R)
			{
				LL t=(L+R)/2;
				LL s=5*p*t+(t+1)*t/2;
				if(s<n) L=t; else R=t;
			}
			n-=5*p*L+L*(L+1)/2;
			return solve(3*p+R+1,n);
		}
	}
	return -1;
}

int main()
{
	for(int j=0;j<2;j++) prf[j][0]=j;
	LL pw2=2;
	for(int k=1;k<P;k++)
	{
		for(int j=0;j<2;j++)
			prf[j][k]=(LL(prf[j][k-1])*pw2+prf[!j][k-1])%MOD;
		pw2=pw2*pw2%MOD;
	}

	f[0]=1;
	for(int h=0;h<H;h++)
	{
		int p=1<<h;
		for(int i=0;i<p;i++)
		{
			f[i]*=2;
			f[2*p-1-i]=f[i]-1;
		}
	}

	LL ans=0;
	LL p=1;
	for(int k=1;k<=18;k++)
	{
		p*=10;
		ans=(ans+solve(p))%MOD;
	}
	printf("%lld\n",ans%MOD);
	return 0;
}
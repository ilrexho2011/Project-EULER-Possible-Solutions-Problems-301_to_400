#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;

#define N 10000000000LL
#define N2 100000

int count_prime[N2+1];
long long mul_prime[N2+1];
int miu[N2+1];

void cal_Mobius_Function()
{
	miu[1] = 1;
	for(int i=1;i<=N2;i++)
	{
		count_prime[i] = 0;
		mul_prime[i] = 1;
	}
	for(int i=2;i<=N2;i++)
	{
		if(count_prime[i]==0)
		{
			for(int j=i;j<=N2;j+=i)
			{
				count_prime[j]++;
				mul_prime[j]*=i;
			}
		}
	}
	for(int i=2;i<=N2;i++)
	{
		if(mul_prime[i]==i)
		{
			miu[i] = count_prime[i]&1?-1:1;
		}
		else
			miu[i] = 0;
	}
	cout<< "cal_Mobius_Function over.\n";
}


long long count_SquareFreeNumber(long long left,long long right)
{
	if( left>right ) return 0;
	long long ans = 0;
	long long n2 = sqrt(right+0.0);
	long long n1 = sqrt(left-1+0.0);
	long long v2 = 0,v1 = 0;
	for(long long i=1;i<=n1;i++)
	{
		v1 += miu[i]*(left-1)/(i*i);
	}
	for(long long i=1;i<=n2;i++)
	{
		v2 += miu[i]*right/(i*i);
	}
	//cout << left << " " << v1 << " " << right << " " << v2 <<" " << v2-v1 << endl; 
	return v2-v1;
}

long long rec(long long mul,long long prev)
{
	long long left = prev;
	long long right = N/mul;
	long long ans = count_SquareFreeNumber(left,right);
	//cout << mul <<" "<<prev<< " " <<left<<" "<<right<<" "<< ans << endl;
	if(ans) for(long long i=prev;i<=N2;i++)
	{
		if( mul*i*i>N ) break;
		if( miu[i]!=0 )
		{
			long long t= rec(mul*i,i);
			ans += t;
		}
	}
	return ans;
}

void solve()
{
	long long ans = count_SquareFreeNumber(1,N);
	//cout << ans << endl;
	for(int i=2;i<=N2;i++)
	{
		if(miu[i]!=0)
		{
			cout << i << endl;
			ans += rec(i,i);
		}
	}
	cout << ans << endl;
}


int main()
{
	long long s = clock();
	cal_Mobius_Function();
	solve();
	long long e = clock();
	cout << "time: " << (e-s)/1000.0 << endl;
	system("pause");
	return 0;
}
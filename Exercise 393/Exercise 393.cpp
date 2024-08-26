#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
ll f[1<<20],g[1<<20];
int main()
{
	int n=10;
	f[0]=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			memset(g,0,sizeof g);
			for(int k=0;k<(1<<n*2);k++)
			{
				if(!f[k])continue;
				ll c=f[k];
				int le,ri=(k>>j*2)&3;
				if(j==0)le=0;else le=(k>>j*2-2)&3;
				int z=k;
				if(j)z^=(le<<j*2-2);
				z^=(ri<<j*2);
				if(ri==3)continue;
				if(ri==2)
				{
					g[k]+=c;
					if(le==1)g[z]+=c;
					if(le==3)g[z^(2<<j*2-2)]+=c;
				}else
				if(ri==1)
				{
					g[k]+=c;
					if(le==2)g[z]+=c;
					if(le==3)g[z^(1<<j*2-2)]+=c;
				}else
				if(ri==0)
				{
					g[k^(3<<j*2)]+=c;
					if(le==1)g[z^(1<<j*2)]+=c;
					if(le==2)g[z^(2<<j*2)]+=c;
					if(le==3)
						g[z^(1<<j*2)^(2<<j*2-2)]+=c,
						g[z^(2<<j*2)^(1<<j*2-2)]+=c;
				}
			}
			memcpy(f,g,sizeof g);
		}
	cout<<f[0]<<endl;
	return 0;
}
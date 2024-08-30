#include <cstdio>

typedef long long LL;

LL min(LL a,LL b){return a<b?a:b;}
LL max(LL a,LL b){return a>b?a:b;}
LL abs(LL a){return a<0?-a:a;}
LL down(LL a,int b){return a<0 && a%b ? a/b-1 : a/b;}

const int N = 1000000+1;
const int maxX = 1000000000;
int minp[N];
LL d[101010];

int check2(LL x,LL y, LL p,LL q)
{
	if(q==0 || p%q) return 0;
	LL a=p/q;
	LL b=x-a,c=y-a;
	return a!=b && a!=c && abs(a)<=maxX && abs(b)<=maxX && abs(c)<=maxX;
}

int calc(int k,LL x,LL y)
{
	if(x>=y) return 0;
	LL mina=max(-maxX,y-maxX);
	LL maxa=min(maxX,x+maxX);
	if(LL(k)*k+x*y<0) {
		LL mina1=max(mina,down(x,2)+1);
		LL maxa1=min(maxa,down(y-1,2));
		return max(maxa1-mina1+1,0); 
	} else {
		LL mina1=max(mina,down(x+1,2));
		LL maxa1=min(maxa,down(y,2));
		return max(maxa-mina+1,0)-max(maxa1-mina1+1,0);
	}
}

int main()
{
	int i,j;
	for(i=2;i<N;i++) if(!minp[i])
		for(j=i;j<N;j+=i) if(!minp[j]) minp[j]=i;
	LL cnt=0;
	LL cnt2=0;
	for(int k=1;k<N;k++)
	{
		int len=0;
		d[len++]=1;
		for(int x=k;x>1;)
		{
			j=0;
			int p=minp[x];
			for(;x%p==0;x/=p) j++;
			for(i=len;i--;)
			{
				LL q=1;
				for(int h=0;h<2*j;h++)
				{
					q*=p;
					d[len++]=d[i]*q;
				}
			}
		}
		for(i=0;i<len;i++)
		{
			LL x=d[i];
			LL y=-LL(k)*k/x;
			cnt2+=check2(x,y,k*y-LL(x)*x,2*(k-x));
			cnt2+=check2(x,y,k*y+LL(x)*x,2*(k+x));
		}
		for(i=len;i--;)
			if(LL(k)*k/d[i]%2) d[len++]=2*d[i];
		for(i=len;i--;)
			d[len++]=-d[i];
		for(i=0;i<len;i++)
		{
			LL y=d[i]-k;
			LL x=k*(y-k)/(y+k);
			cnt+=calc(k,x,y);

			y=d[i]+k;
			x=k*(y+k)/(k-y);
			cnt+=calc(k,x,y);
		}
	}
	LL ans=cnt-cnt2;
	printf("%lld\n",ans);
	return 0;
}
#include <cmath>
#include <ctime>
#include <algorithm>
using namespace std;

const double eps=1e-9;
const double PI=2*acos(0.0);

inline void MIN(double &a,double b) {if((a)>(b)) (a)=(b);}

#define N 55555
int r;
double coef;
int n;
int xx[N],yy[N],zz[N];
double d[N];
int mark[N];

void add(int x,int y,int z)
{
	xx[n]=x,yy[n]=y,zz[n++]=z;
	if(x>0)
		xx[n]=-x,yy[n]=y,zz[n++]=z;
}

double dist(int i,int j)
{
	int scal=xx[i]*xx[j]+max(yy[i]*yy[j]+zz[i]*zz[j],yy[i]*zz[j]+zz[i]*yy[j]);
	double d=acos(coef*scal);
	return d*d;
}

int main()
{
	clock_t start=clock();
	freopen("out.txt","w",stdout);
	double ans=0;
	for(int h=1;h<=15;h++)
	{
		r=(1<<h)-1;
		coef=1./r/r;
		n=0;
		int x,y,z;
		for(x=0;3*x*x<=r*r;x++)
			for(y=x;2*y*y+x*x<=r*r;y++)
			{
				z=sqrt(1.*r*r-x*x-y*y)+eps;
				if(z*z+x*x+y*y==r*r)
				{
					add(x,y,z);
					if(x!=y) add(y,x,z);
					if(y!=z) add(z,x,y);
				}
			}
		printf("r=%d n=%d ",r,n);
		int i,j;
		memset(mark,0,sizeof mark);
		for(i=0;i<n;i++) d[i]=xx[i]==-r?0:1e20;
		for(;;)
		{
			i=-1;
			for(j=0;j<n;j++)
				if(!mark[j] && (i<0 || d[i]>d[j])) i=j;
			if(xx[i]==r) break;
			mark[i]=1;
			for(j=0;j<n;j++)
				if(!mark[j])
					MIN(d[j],d[i]+dist(i,j));
		}
		double cur=d[i]/PI/PI;
		ans+=cur;
		printf("%.12lf\n",cur);
		fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	}
	printf("%.10lf\n",ans);
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
	return 0;
}

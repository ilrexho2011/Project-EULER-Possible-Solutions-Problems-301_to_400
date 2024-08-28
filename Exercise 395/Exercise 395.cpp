#include <cstdio>

inline void MIN(double &a,double b) { if(a>b) a=b; }
inline void MAX(double &a,double b) { if(a<b) a=b; }

double mx_res=0,Mx_res=1,my_res=-1,My_res=0;

struct segm
{
	double x1,y1,x2,y2;
	double mx,Mx,my,My;
	segm(){}
	segm(double x1_,double y1_,double x2_,double y2_,
		double mx_,double Mx_,double my_,double My_) {
			x1=x1_;y1=y1_;x2=x2_;y2=y2_;
			mx=mx_;Mx=Mx_;my=my_;My=My_;
	}
	segm left()
	{
		return segm(
			( 37 * x1 - 12 * x2 + 16 * y1 - 16 * y2) / 25,
			(-16 * x1 + 16 * x2 + 37 * y1 - 12 * y2) / 25,
			( 21 * x1 +  4 * x2 + 28 * y1 - 28 * y2) / 25,
			(-28 * x1 + 28 * x2 + 21 * y1 +  4 * y2) / 25,
			mx,Mx,my,My
			);
	}
	segm right()
	{
		return segm(
			(- 3 * x1 + 28 * x2 + 21 * y1 - 21 * y2) / 25,
			(-21 * x1 + 21 * x2 -  3 * y1 + 28 * y2) / 25,
			(-12 * x1 + 37 * x2 +  9 * y1 -  9 * y2) / 25,
			(- 9 * x1 +  9 * x2 - 12 * y1 + 37 * y2) / 25,
			mx,Mx,my,My
			);
	}
	void update()
	{
		MIN(mx_res,x1+mx);
		MIN(mx_res,x2+mx);
		MAX(Mx_res,x1+Mx);
		MAX(Mx_res,x2+Mx);
		MIN(my_res,y1+my);
		MIN(my_res,y2+my);
		MAX(My_res,y1+My);
		MAX(My_res,y2+My);
	}
};

const int N = 100;
segm a[N];

int main()
{
	a[0]=segm(0,0,1,0,0,0,0,0);
	for(int n=1;n<N;n++)
	{
		a[n]=a[n-1].right();
		for(int k=n-1;k>0;k--)
		{
			segm r=a[k-1].right();
			segm l=a[k].left();
			double dx=-r.x1+l.x1;
			double dy=-r.y1+l.y1;
			MIN(r.mx,l.mx+dx);
			MAX(r.Mx,l.Mx+dx);
			MIN(r.my,l.my+dy);
			MAX(r.My,l.My+dy);
			a[k]=r;
		}
		a[0]=a[0].left();
		for(int k=0;k<=n;k++)
			a[k].update();
	}
	double res=(Mx_res - mx_res) * (My_res - my_res);
	printf("%.10lf\n",res);
	return 0;
}
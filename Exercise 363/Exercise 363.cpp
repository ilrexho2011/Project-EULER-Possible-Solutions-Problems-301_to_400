#include <cmath>
#include <cstdio>
size_t const D=20;


void bezier(double &dA, double &dL, double v, size_t depth=0, double t0=0.0, double t1=1.0, double p0x=1.0, double p0y=0.0, double p1x=0.0, double p1y=1.0)
{
	if(depth<D)
	{
		double tm=0.5*(t0+t1);
		double a1=tm;
		double a0=1.0-tm;

		double q0x=1.0;
		double q0y=a1*v;
		double q1x=a0*1.0+a1*v;
		double q1y=a1*1.0+a0*v;
		double q2x=a0*v;
		double q2y=1.0;

		double r0x=a0*q0x+a1*q1x;
		double r0y=a0*q0y+a1*q1y;
		double r1x=a0*q1x+a1*q2x;
		double r1y=a0*q1y+a1*q2y;

		double x=a0*r0x+a1*r1x;
		double y=a0*r0y+a1*r1y;

		double dA1, dA2;
		double dL1, dL2;
		bezier(dA1, dL1, v, depth+1, t0, tm, p0x, p0y, x, y);
		bezier(dA2, dL2, v, depth+1, tm, t1, x, y, p1x, p1y);
		dA=dA1+dA2;
		dL=dL1+dL2;
	}
	else
	{
		dL=hypot(p0x-p1x, p0y-p1y);
		dA=0.5*fabs(p0x*p1y-p0y*p1x);
	}
}


int main()
{
	double vl=0.0, vh=2.0, v;
	double A0=M_PI/4.0, L0=M_PI/2.0, A, L;
	double r=0;
	while(vl+1e-13<vh)
	{
		v=0.5*(vl+vh);
		bezier(A, L, v);
		r=100.0*(L-L0)/L0;
		//printf("v=%.10f, A=%.10f, L=%.10f, e=%.10f\n", v, A, L, r);
		(A<A0?vl:vh)=v;
	}

	printf("r=%.10f\n", r);
	return 0;
}

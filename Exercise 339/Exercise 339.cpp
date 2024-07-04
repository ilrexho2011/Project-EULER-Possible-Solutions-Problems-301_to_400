#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define MAXN 10000

//double E[2*MAXN+5][2*MAXN+5];
double P[2*MAXN];


int main()
{
  int T=1;
  P[0]=0;
  P[1]=1;
  for(int x=2;x<=MAXN;x++)
    {
      int y=x-1;
      //(x,x-1) is the maximum
      double C1=1;
      double C2=0;
      double B1=0;
      double B2=1;
      for(int d=1;y-d>=1;d++)
	{
	  //(x+d,y-d) as a function of (x+d-1,y-d+1) and (x+d+1,y-d-1)
	  double alph=(y-d+0.0)/(x+y);
	  //(x+d+1,y-d-1)=(x+d,y-d)/(1-alph)-(x+d-1,y-d+1)*alph/(1-alph)
	  double C1next=C1/(1-alph)-B1*alph/(1-alph);
	  double C2next=C2/(1-alph)-B2*alph/(1-alph);
	  B1=C1;
	  B2=C2;
	  C1=C1next;
	  C2=C2next;
	}
      P[x]=(x*(x+y)+C1*y*P[x-1])/(C1*(x+y)+C2*x);
    }

  
  double A2=1;
  double B2=0;
  
  //E[MAXN+1,MAXN-1]=(MAXN+1)/(2*MAXN)*E[MAXN+2,MAXN-2]+(MAXN-1)/(2*MAXN)*P[MAXN]
  double A1=2*MAXN/(MAXN+1.0);
  double B1=-(MAXN-1)/(MAXN+1.0)*P[MAXN];

  int c=MAXN-2;
  for(int t=MAXN+2;t<=2*MAXN;t++,c--)
    {
      double newA1=(t+c+0.0)/t*A1-c/(t+0.0)*A2;
      double newB1=(t+c+0.0)/t*B1-c/(t+0.0)*B2;
      A2=A1;B2=B1;
      A1=newA1;B1=newB1;
    }
  //2*MAXN=A1*E[MAXN+1],MAXN-1]+B1
  double other=(2*MAXN-B1)/A1;
  double answer=0.5*P[MAXN-1]+0.5*other;
  printf("%lf\n",answer);
  
  return(0);



}
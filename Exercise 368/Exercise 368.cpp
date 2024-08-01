#include <map>
#include <string>
#include <vector>
#include <math.h>
#include <set>
#include <algorithm>
#include <list>
#include <iostream>
#define ll long long
#define MAXP 40
using namespace std;
int digs[20];
int nd;

double binomial[3*MAXP][3*MAXP];

double f1[2][10][MAXP+1];
double f2[2][10][MAXP+1];




int main()
{
    for(int i=0;i<3*MAXP;i++)
        for(int j=0;j<=i;j++)
        {
            if(j==0)
                binomial[i][j]=1;
            else
                binomial[i][j]=binomial[i-1][j]+binomial[i-1][j-1];
        }
    double initsum=0;
    for(int i=1;i<=99;i++)
        initsum+=1.0/i;
    
    for(int d=0;d<=9;d++)
    {
        for(int j=1;j<=MAXP;j++)
        {
            f1[1][d][j]=f2[1][d][j]=0;
            for(int pref=10;pref<=99;pref++)
            {
                int dp=pref%10;
                int dpp=pref/10;
                if(d==dp && dp==dpp)
                    continue;
                if(dp!=d)
                    f1[1][d][j]+=1.0/pow(10*pref+d,j);
                else
                    f2[1][d][j]+=1.0/pow(10*pref+d,j);
            }
        
        }
        initsum+=f1[1][d][1]+f2[1][d][1];
    }
    printf("%1.12f\n",initsum);
    for(int numdigs=4;numdigs<=10000;numdigs++)
    {
        printf("%d\n",numdigs);
        for(int d=0;d<=9;d++)
        {
            for(int j=1;j<=MAXP;j++)
            {
                f1[numdigs&1][d][j]=0;
                f2[numdigs&1][d][j]=0;
                double pref=1;
                for(int t=0;t<=MAXP;t++)
                {
                    double mult=pref*binomial[t+j-1][j-1]/pow(10.0,j);
                    f2[numdigs&1][d][j]+=mult*(j+t<=MAXP?f1[(numdigs-1)&1][d][j+t]:0);
                    for(int dp=0;dp<=9;dp++)
                        if(d!=dp)
                            f1[numdigs&1][d][j]+=mult*(j+t<=MAXP?f1[(numdigs-1)&1][dp][j+t]+f2[(numdigs-1)&1][dp][j+t]:0);
                    pref*=-d/10.0;
                }
                
            }
            initsum+=f1[numdigs&1][d][1]+f2[numdigs&1][d][1];
        }
        printf("%1.10f\n",initsum);
    }

}
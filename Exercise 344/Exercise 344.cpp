#include <stdio.h>
#define N 1000000
#define C 100
#define X N+1
#define Y C+2
#define Binlen 25
#include<time.h>

long long SP;
long long Choose[X][Y];
long long pow[Binlen];
long long q[N-C+1];
long long p[N-C+1];
int k= C/2+1;

void Prepare_q()
{
    for(int i=0;i<=N-C;i++)
    {
        q[i]=Choose[i+C/2][C/2];
        p[i]=q[i];
    }
    for(int j=1;j<Binlen;j++)
    {
        for(int n=N-C; n>=0 ;n--)
        {  
            for(int i=2,l=n-pow[j];i<=k && l>=0;i+=2)
            {
                q[n]+=(q[l]*Choose[k][i]);
                p[n]+=(p[l]*Choose[k-1][i]);
                l-=pow[j];
            }
            q[n]%=SP;
            p[n]%=SP;
        }
    }
}

void Prepare_Table()
{
    Choose[0][0]=1;
    for(int i=1;i<=X;i++)
  {
          Choose[i][0]=1;
        for(int j=1;j<=i && j<= Y;j++)
        {
            Choose[i][j]=(Choose[i-1][j-1]+Choose[i-1][j])%SP;
        }
    }
    pow[0]=1;        
    for(int i=1;i<Binlen;i++)
    {
        pow[i]=2*pow[i-1];
    }
}


long long Nim_Conf(int n,int k)
{
    long long ans= 0;
    long long bns=0;
        Prepare_q();
    ans=q[n];
    bns=q[n+1]-p[n+1];
    ans+=(C-1)*bns;
    return ans%SP;
}  
long long Do_for(long long x)   
{
    SP=x;
    Prepare_Table();
    long long ans =(C+1)*Choose[N][C+1];
    printf("****Table Done******\n");   
    ans-=Nim_Conf(N-C-1,C/2+1);
    ans%=SP;
    printf ("%lld\n",ans);
    return ans;
}                    
	 				 							                                                       
int main()
{
   	clock_t start=clock();
    long long a=Do_for(1000003LL);
    for(long long b=Do_for(1000033LL);b<1000036000099LL;b+=1000033LL)
    {
        if(b%1000003LL==a)
            printf("%lld\n",b);    
    }
	fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
    getchar();
    return 0;
}
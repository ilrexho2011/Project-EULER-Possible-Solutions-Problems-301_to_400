#define N 2000
const double pi=3.14159265358979323846;

const double M=40;
const double lim=(1-1/M);
double pdf[2][N+1];

int main()
{
    int i, j, k, idx=0;
    double in=lim*lim;
    double exp=1-in;
    pdf[idx][1]=1;
    for(i=2;i<=20;i++)
    {
        idx=1-idx;
        for(j=0;j<=N;j++)
        {
            pdf[idx][j]=0;
        }
        double f[N+1]={0};
        double s[N+1]={0};
        for(j=1;j<=N;j++)
        {
            for(k=j;k<N-1;k++)
            {
                f[k]+=pdf[1-idx][j]*(k-j+1);
                s[k+1]+=pdf[1-idx][j]*(k-j+1);
            }
        }
        for(j=2;j<=N;j++)
        {
            pdf[idx][j]=f[j-2]/(j-1)-s[j-1]/j;
        }
        double lowlen=0, power=lim;
        double a=0, b=0;
        for(j=1;j<=N;j++)
        {
            power*=lim;
            lowlen+=pdf[idx][j]*power/(j+1);
            a+=f[j]*power/(j+1);
            b+=s[j]*power/(j+1);
        }
        
        double hilen=0.5*a*(1-lim*lim)-b*(1-lim);
        double prob=lowlen/(lowlen+hilen);
        exp+=in*(1.0-prob)*i;
        in*=prob;
    }
    printf("exp=%.10f\n", exp);
    return 0;
}
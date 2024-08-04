#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

const long long int NN = 500LL;

const int N = 1000;

int main()
{

    vector<long double> v(N+1,0.0);
    v[0]=1.0;

    long double sum = 0.0;
    for(long long int i=1;i<NN;i++){
        cout<<i<<": "<<setprecision(20)<<setw(16)<<sum<<endl;
        vector<long double> vv(N+1,0.0);
        for(int o=0;o<N;o++){
            if (v[o]==0.0) continue;
            if (o<N/2) {
                long double p=1.0;
                vv[o+N/2]+=v[o]*1.0L/N;
                p-=1.0L/N;
                vv[o]+=v[o]*1.0L/N*(o+1);
                p-=1.0L/N*(o+1);
                if (o<N/2-1) {
                    vv[o+1]+=v[o]*1.0L/N*(N-2-2*o);
                    p-=1.0L/N*(N-2-2*o);
                }
                vv[N]+=v[o]*p;
            } else {
                long double p=1.0;
                vv[o]+=v[o]*1.0L/N*(o-N/2+1);
                p-=1.0L/N*(o-N/2+1);
                if (o<N-1) {
                    vv[o+1]+=v[o]*1.0L/N*(N-2-2*(o-N/2));
                    p-=1.0L/N*(N-2-2*(o-N/2));
                }
                vv[N]+=v[o]*p;
            }
        }
        sum+=vv[N]*i;
        vv[N]+=v[N];
        v=vv;
    }
    return 0;
}

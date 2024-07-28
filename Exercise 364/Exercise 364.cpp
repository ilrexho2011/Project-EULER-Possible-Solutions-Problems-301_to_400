#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define DIM 1000000
#define mod 100000007
#define M(a,b,c,d,e) (((((((a*b)%mod)*c)%mod)*d)%mod)*e)%mod
#define ll __int64


vector<int> vec;
ll f[DIM], pwr[DIM], sum = 0;
int in[DIM+1][20];

void init(){
    f[0] = pwr[0] = 1;
    for (int i=1; i<DIM; i++) f[i] = f[i-1]*i % mod, pwr[i] = pwr[i-1]*2 % mod, in[i][0] = i;
    for (int j=1; j<20; j++)
        for (int i=1; i<=DIM; i++)
            if (i+pwr[j-1]<=DIM) in[i][j] = ((ll)in[i][j-1]*in[i+pwr[j-1]][j-1]) % mod;
}

void binary(int n){
	if(n<=1) {vec.push_back(n); return;}
    int b;
	b = n % 2;
	binary(n >> 1);
	vec.push_back(b);
}

int interval(int a, int b){
    if (a>b) return 1;
    vec.clear();
    binary(b-a+1);
    ll p = 1, k = a;
    for (int i=0; i<vec.size(); i++){
        if (vec[i]) p = (p*in[k][vec.size()-1-i]) % mod;
        if (vec[i]) k+=pwr[vec.size()-1-i];
    }
    return p;
}

int main(){
    init();
    for (int a=1; a<3; a++)
        for (int b=1; b<3; b++){
            int n = DIM - a - b + 1, d = n/2 - n%2, t = (n - 2*d)/3, p = d + t - 1;
            int extra = a + b - 2;
            for (; d>=0; d-=3, t+=2, p--){
                if (!d || !t) sum = (sum + M(f[p+2],1,pwr[t],f[t+extra],f[d+t])) % mod;
                else sum = (sum + M(f[p+2],interval(t+1,d+t),pwr[t],f[t+extra],interval(d+1,d+t))) % mod;
            }
        }
    cout<<sum<<endl;
    return 0;
}
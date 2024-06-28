#include <iostream>
#include <cmath>

using namespace std;

long long int getn(long long int n){
    long long int res = 0LL;
    long long int evens = 0LL;
    long long int odds = 0LL;
    long long int arcevens = 0LL;
    long long int arcodds = 0LL;

    {
        long long int last = -1LL;
        long long int k=0LL;
        long long int km=0LL;
        long double kk=0LL;
        long long int kkk=0LL;
        long double kk0;
        long long int kkk0;
        long double kk2;
        long long int kkk2;
        long long int d;

        for(long long int i=1LL;n-i>=kkk;i++){
            kk0  = 2LL*n*i-2LL*n-i*i+1LL;
            kkk0 = sqrt(kk0);
            if ((kkk0)*(kkk0)!=kk0) kkk0++;

            kk   = 2LL*i*n-i*i;
            kkk  = sqrt(kk);
            if ((kkk)*(kkk)==kk) kkk--;

            kk2  = 2LL*n*(i+1LL)-2LL*n-(i+1LL)*(i+1LL)+1LL;
            kkk2 = sqrt(kk2);
            if ((kkk2)*(kkk2)!=kk2) kkk2++;

            k    = kkk-kkk0+1LL;

            if (n-i<kkk0) break;

            if (k==2 && n-i<kkk) {
                evens++;
                arcevens++;
                break;
            }

            if (last==kkk0) {
                evens++;
            }

            if (k%2LL==0LL) evens++;


            km=k;
            if (last==kkk0) {
                km--;
                if (k%2==1){
                    arcodds+=2;
                } else {
                    arcevens+=2;
                }
            }
            if (kkk==kkk2) {
                km--;

                d=2LL;
                if (kkk==n-i) d=1LL;
                if (k%2==1){
                    arcodds+=d;
                } else {
                    arcevens+=d;
                }
            }
            d=2LL;
            if (k==1 && kkk==n-i) d=1LL;
            if (k%2==0){
                arcodds+=d*km;
            } else {
                arcevens+=d*km;
            }

if (last>kkk) {
    cout<<"ERR: ";
    cout<<i<<","<<kkk0<<"-"<<kkk<<","<<k<<"("<<evens<<")"<<endl;
}

//cout<<i<<","<<kkk0<<"-"<<kkk<<","<<k<<"("<<evens<<")"<<endl;

            last = kkk;
        }
    }


    odds=n-evens;
//cout<<evens<<","<<odds<<","<<arcevens<<","<<arcodds<<endl;

    res = 2*evens*odds+arcevens-arcodds;
    cout<<res<<endl;
    return res;
}

int main() {

    getn(10);
    getn(1000);

    long long int res = 3LL;
    long long int i=4LL;
    long long int i2=16LL;
    for(;i<=31LL;i++,i2*=2LL){
        if (i%2LL==0LL) {
cout<<i<<":";
            res+=getn(i2-i);
cout<<res<<endl;
        }
    }
    cout<<"Res.:"<<res<<endl;
}
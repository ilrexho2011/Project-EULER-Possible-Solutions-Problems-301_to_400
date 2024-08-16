#include <iostream>
#include <vector>

using namespace std;

long long int N = 1000000000000000000LL;

vector<long long int> a5;
vector<long long int> e5;
vector<long long int> bl;

long long int rec(long long int n, int exp5){
    if (n<=2) {
        return n;
    } else if (n<5) {
        return 2;
    } else if (n==5) {
        return 3;
    }

    while(e5[exp5]>n){
        exp5--;
    }

    if (n==e5[exp5]){
        return a5[exp5];
    }

    long long int res = a5[exp5];
    if (n<=2*e5[exp5]) {
        res+=rec(n-e5[exp5],exp5);
        return res;
    }
    res+=a5[exp5];
    if (n<=bl[exp5]){
        res+=rec(n-2*e5[exp5],exp5);
        return res;
    }
    res+=rec(bl[exp5]-2*e5[exp5],exp5);

    if (n<=3*e5[exp5]) {
        res+=rec( (n-2*e5[exp5])/5,exp5);
        res-=rec( (bl[exp5]-2*e5[exp5])/5,exp5);
        return res;
    }
    res+=rec( (3*e5[exp5]-2*e5[exp5])/5,exp5);
    res-=rec( (bl[exp5]-2*e5[exp5])/5,exp5);

    if (n<=4*e5[exp5]){
        res+=rec((n-3*e5[exp5])/5,exp5);
        return res;
    }
    res+=a5[exp5-1];
    res+=rec((n-4*e5[exp5])/5,exp5);
    return res;
}

int main(){

    e5.push_back(1);
    e5.push_back(5);
    bl.push_back(2);
    bl.push_back(12);
    for(;e5.back()<=N/5;){
        e5.push_back(e5.back()*5);
        bl.push_back(2*e5.back()+bl.back());
    }

    a5.push_back(1);
    a5.push_back(3);
    for(int i=0;i<34;i++){
        long long int nw = 2*a5.back()+5*a5[a5.size()-2];
        a5.push_back(nw);
    }
    cout<<rec(N/5,e5.size()-1)<<endl;
}

//////////////////////////////////////////////////////////////
// This part was for quickly generate small examples
// so that I could notice the recursive rule.

/*
int s5(long long int n){
    int res = 0;
    while(n>0){
        res+=n%5;
        n/=5;
    }
    return res;
}

int main()
{
    int nr=0;
    for(int i=1;i<=200*5;i++){
        if (2*s5(i)-s5(2*i-1)<=0) {
//            cout<<i<<","<<2*i-1<<" - "<<s5(i)<<","<<s5(2*i-1)<<" - "<<2*s5(i)-s5(2*i-1)<<endl;
            nr++;
            cout<<i/5<<","<<nr<<endl;
        }

    }

    cout<<nr<<endl;
    return 0;
}
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>

using namespace std;

//const long long int N = 10;
//const long long int N = 100;
//const long long int N = 10000;
const long long int N = 20000000;

const long long int MOD = 100000000;

vector<long long int> primes;
vector<bool> isprime(N+1,true);

void setprimes(){
    isprime[0]=isprime[1]=false;
    for(long long int i=0;i<=N;i++){
        if (isprime[i]){
            primes.push_back(i);
            for(long long int j=2;j*i<=N;j++){
                isprime[j*i]=false;
            }
        }
    }
}

vector<long long int> phi(N+1,1);

void seteulerphis(long long int n,long long int v,long long int ind){
    phi[n]=v;
    for(long long int i=ind;i<primes.size() && n*primes[i]<=N;i++){
        long long int p = primes[i];
        int e = 1;
        for(;n*p<=N;e++,p*=primes[i]){
            seteulerphis(n*p,v*(primes[i]-1)*p/primes[i],i+1);
        }
    }
}

long long int BIT_readsum(vector<int> &BIT, int idx){
    if (idx<0) {
        return 0;
    }
    if (idx>=BIT.size()){
        idx=BIT.size()-1;
    }
	long long int sum = 0;
	while (idx > 0){
		sum += BIT[idx];
		sum %= MOD;
		idx -= (idx & -idx);
	}
	return sum;
}

void BIT_update(vector<int> &BIT, int idx ,int val){
	while (idx < BIT.size()){
		BIT[idx] += val;
		BIT[idx] %= MOD;
		idx += (idx & -idx);
	}
}

int main() {
    setprimes();
    cout<<"Primes done."<<endl;

    seteulerphis(1,1,0);
    cout<<"Phis done."<<endl;

    set<int> s;
    for(int i=0;i<=N;i++){
        s.insert(phi[i]);
    }

    vector<int> map_phival( N+1,-1);
    vector<int> phival;
    phival.push_back(0); //first phi-value is indexed by 1, instead 0 (due to BIT implementation)
    for(set<int>::iterator it=s.begin();it!=s.end();it++){
        phival.push_back(*it);
        map_phival[*it]=phival.size()-1;
    }
    //For those number, which are not phi(x) for any x, we set the index of the next phi-value
    int last = phival.size();
    for(int i=map_phival.size()-1;i>=0;i--){
        if (map_phival[i]==-1) {
            map_phival[i]=last;
        } else {
            last = map_phival[i];
        }
    }
    cout<<"Phi-values done."<<endl;


    vector<int> BIT(phival.size(),0);
    long long int res = 0;
    for(int n=N;n>=6;n--){
if (n%200000==0) cout<<n<<endl;
        int pn = phi[n];
        int idx1 = map_phival[pn];
        int idx2 = map_phival[n]-1;
        long long int sum = 1;
        if (idx1<idx2) {
            long long int sum1 = BIT_readsum(BIT,idx1);
            long long int sum2 = BIT_readsum(BIT,idx2);
            sum += sum2 - sum1 + MOD;
            sum %= MOD;
        }
        BIT_update(BIT,idx1,sum);
        res = sum; //last
    }
    cout<<"Res.:"<<res<<endl;
    return 0;
}
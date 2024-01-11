#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

typedef long long int ll;

const ll N = (ll)pow(10, 10) + 1;
const ll SN = (ll)pow(10, 5);
const ll M = (ll)pow(10, 9) * 4 + 1;
const ll C = (ll)pow(10, 8);
const ll Q = (ll)pow(10, 9);

vector<bool> z(M, false);
vector<bool> m(M, false);
vector<bool> p(M, true);
vector<ll> prime;


ll powMod(ll a, ll n, ll p) {
  if (n == 0) return 1;
  if (n % 2 == 0) return powMod((a * a) % p, n / 2, p);
  return (a * powMod(a, n - 1, p)) % p;
}

inline ll sum_g(ll t) {
    ll x3 = (powMod(3, t+1, 2*Q) - 1) / 2;
    ll x2 = (powMod(2, t+1, Q) - 1);
    return x3 - x2 - t;
}

inline ll mobius(ll n) {
    if (n < M) {
        if (z[n]) return 0;
        if (m[n]) return -1;
        return 1;
    }
    ll factors = 0;
    for (ll i = 0; prime[i] < SN; ++i) {
        if (n % prime[i] == 0) {
            if (n % (prime[i]*prime[i]) == 0) return 0;
            n /= prime[i];
            factors++;
            if (n < M) {
                if (factors % 2 == 0) return mobius(n);
                else return -mobius(n);
            }
        }
    }
    factors ++;
    if (factors % 2 == 0) return 1;
    else return -1;
}

int main() {
    for (ll i = 2; i < M; ++i) {
        if (p[i]) {
            if (i < 3*SN)
                prime.push_back(i);
            m[i] = true;
            ll i2 = i*i;
            for (ll j = i+i; j < M; j+=i){
                p[j] = false;
                if (j % i2 == 0)
                    z[j] = true;
                else
                    m[j] = !m[j];
            }
        }
    }
    
    cout << "start" << endl;
    
    ll t = 1;
    for (ll i = 1; i < N; ++i) {
        if (i % C == 0)
            cout << "t:" << i << endl;
        ll k = (N-1) / i;
        if (k == 1) continue;
        ll mob = mobius(i);
        if (mob == 0) continue;
        t += sum_g(k) * mob;
        t %= Q;
    }
    if (t < 0) t += Q;
    cout << t << endl;
}
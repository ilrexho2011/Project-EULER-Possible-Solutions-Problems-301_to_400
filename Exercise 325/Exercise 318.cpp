
#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;
typedef double ld;

bool valid(ll p, ll q) {
  ld x = sqrt(q) - sqrt(p);
  return x < 1.0;
}

ll C(ll p, ll q, ll n) {
  ld x = log10(sqrt(q)-sqrt(p));
  x *= 2*n;
  return floor(-x);
}

ll N(ll p, ll q) {
  ld x = log10(sqrt(q) - sqrt(p));
  return ceil(-2011.0/(2.0*x));
}

int main() {
  ll ans = 0;
  for(ll q=1; 1+q<=2011; q++) {
    for(ll p=1; p<q && p+q<=2011; p++) {
      if(!valid(p, q)) { continue; }
      ans += N(p, q);
    }
  }
  cout << ans << endl;
}
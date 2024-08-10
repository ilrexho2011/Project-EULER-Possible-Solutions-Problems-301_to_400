#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<vector<ll>> mat;

ll MOD = 1000*1000*1000;
ll ADD(ll x, ll y) { return (x+y)%MOD; }
ll M(ll x, ll y) { return (x*y)%MOD; }

ll slow_f(ll n) {
  if(n == 0) { return 1; }
  if(n < 0) { return 0; }

  ll ans = 0;
  for(ll d=1; d<=9; d++) {
    ans = ADD(ans, slow_f(n-d));
  }
  return ans;
}

ll sod(ll x) {
  ll ans = 0;
  while(x > 0) {
    ans += x%10;
    x/=10;
  }
  return ans;
}

mat mat_mult(mat A, mat B) {
  mat C(A.size(), vector<ll>(B[0].size(), 0));
  for(ll i=0; i<A.size(); i++) {
    for(ll k=0; k<A[i].size(); k++) {
      for(ll j=0; j<B[k].size(); j++) {
        C[i][j] = ADD(C[i][j], M(A[i][k], B[k][j]));
      }
    }
  }
  return C;
}
mat mat_pow(mat A, ll e) {
  if(e==1) { return A; }
  else if(e%2==0) { return mat_pow(mat_mult(A, A), e/2); }
  else { return mat_mult(A, mat_pow(A, e-1)); }
}

ll f_count(ll n) {
  if(n == 0) { return 1; }
  if(n < 0) { return 0; }

  mat M = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0},
  };
  mat V = {{1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
  mat M2 = mat_pow(M, n);
  mat V2 = mat_mult(M2, V);
  return V2[0][0];
}

ll N;
vector<ll> DP;
vector<int> DP_S;
ll dp(ll i, ll p10, ll sd) {
  if(p10==MOD) { return 0; }
  ll key = sd*10 + i;
  if(DP_S[key]) { return DP[key]; }

  ll ans = 0;
  for(ll d=1; d<=9; d++) {
    ans = ADD(ans, M(p10, M(d, f_count(N-sd-d))));
    ans = ADD(ans, dp(i+1, p10*10, sd+d));
  }
  DP[key] = ans;
  DP_S[key] = true;
  return ans;
}

ll f(ll n) {
  N = n;
  DP.clear(); DP.resize(1000);
  DP_S.clear(); DP_S.resize(1000);

  return dp(0, 1, 0);
  /*
  ll ans = 0;
  for(ll x=1; x<1000; x++) {
    ans = ADD(ans, M(x, f_count(n - sod(x))));
  }
  return ans;
  */
}

int main() {
  printf("%lld\n", f(5));
  ll ans = 0;
  for(ll i=1; i<=17; i++) {
    ll p13 = 1;
    for(ll j=0; j<i; j++) {
      p13 *= 13;
    }
    ll val = f(p13);
    printf("%lld %lld\n", p13, val);
    ans = ADD(ans, val);
  }
  printf("%lld\n", ans);
}
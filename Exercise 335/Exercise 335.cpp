
#include <stdlib.h>
#include <stdio.h>

typedef long long ll;

int main(int argc,char *argv[]) {
  ll maxk = atoll(argv[1]);
  int mod = 7*7*7*7*7*7*7*7*7;
  int period = 6*mod/7;
  int rem = (maxk%period);
  int s = 2;
  int ss = 2;
  int ssr = 2;
  int twop = 1;
  int threep = 1;
  for(int i=1;i<period;i++) {
    s = 2*s + twop;
    ll t = twop*2;
    t *= (twop-1);
    t -= (threep-twop);
    t %= mod;
    s += t;
    s %= mod;
    ss += s;
    ss %= mod;
    if(i <= rem) {
      ssr += s;
      ssr %= mod;
    }
    twop *= 2;
    twop %= mod;
    threep *= 3;
    threep %= mod;
  }
  ll ans = ((maxk-rem)/period) * ss + ssr;
  ans %= mod;
  printf("%lld\n",ans);
}
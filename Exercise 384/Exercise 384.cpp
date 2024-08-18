#include <stdio.h>
#include <math.h>
#include <map>
using namespace std;
#define ll long long

map<pair<ll,ll>, ll> hashed;
ll findtotal(int x)
{
    return (1ll<<((x+1)/2));
}



ll findnumnumbers(ll upper_bound, ll required, int max_bit)
{
  if(required<0)
    return 0;
  if(sqrt((3*upper_bound)/5) >=required)
    return required;
  if(sqrt(6*upper_bound)+1 < required)
    return 0;
  ll retval = 0;
  int numconsec = 0;
  int prevbit = 0;
  ll cumulative = 0;
  //printf("%lld %lld %d\n",upper_bound, required, max_bit);
  if(hashed.find(make_pair(upper_bound, required)) != hashed.end())
    return hashed[make_pair(upper_bound, required)];
  for(int j=max_bit;j>=0;j--)
  {
    if((upper_bound>>j)&1ll)
    {
      retval += findnumnumbers((1ll<<j)-1, (numconsec&1?-required+cumulative:-cumulative+required), j-1);
      cumulative += (numconsec&1?-findtotal(j):findtotal(j));
      numconsec+=prevbit;
    }
    prevbit = (upper_bound>>j)&1;
  }
  cumulative += (numconsec&1?-1:1);
  if(cumulative == required)
    retval++;
  //printf("%lld %lld\n",upper_bound, cumulative);
  hashed[make_pair(upper_bound, required)] = retval;
  return retval;

}

ll g(ll t, ll c)
{
  ll low=1;
  ll high = (1ll<<62);
  while(low<high)
  {
    ll mid = (low+high)/2;
    if(findnumnumbers(mid, t, 62) >= c)
      high = mid;
    else
      low=mid+1;
  }
  return low;
}
ll F[50];

int main()
{
  F[0]=F[1]=1;
  ll answer=0;
  for(int n=2;n<=45;n++)
  {
    F[n]=F[n-1]+F[n-2];
    answer+=g(F[n],F[n-1]);
  }
  printf("%lld\n",answer);
}
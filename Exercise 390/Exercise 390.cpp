#include <cstdio>
#include <set>
#include <cmath>
#include <algorithm>

typedef unsigned long long ull;

const ull N = 10000000000LL;

struct triple
{
  triple() : x(0), y(0), z(0) {}
  triple(ull x, ull y, ull z) : x(x), y(y), z(z) {}
  ull x,y,z;
  bool operator< (const triple& o) const
      { return x<o.x || (x==o.x &&
              (y<o.y || (y==o.y && z<o.z))); }
};

ull check(const triple& input, std::set<triple>& set)
{
  ull result = 0;
  triple t = input;
  for (unsigned i = 0; i < 2; i++)  // x,y,z vs. y,x,z
  {
    for (int s = 1; s >= -1; s -= 2)  // x,y,z vs. x,y,-z
    {
      ull y = std::abs<long long>((2*t.x*t.x+1)*t.y + 2*t.x*t.z*s);
      ull z = std::abs<long long>(2*t.x*(t.x*t.x+1)*t.y + (2*t.x*t.x+1)*t.z*s);
      triple candidate(t.x, y, z);
      if (candidate.x > candidate.y) std::swap(candidate.x, candidate.y);
      if (candidate.x && candidate.z <= N*2 && !set.count(candidate))
      {
        result += candidate.z/2;
        set.insert(candidate);
        result += check(candidate, set);
      }
    }
    std::swap(t.x, t.y);
  }
  return result;
}

int main(int argc, char* argv[])
{
  ull result = 0;
  std::set<triple> triples;
  unsigned max_n = std::pow(N, 1/3.0L);
  for (unsigned n = 2; n <= max_n; n += 2)
  {
    ull x = n;
    // apply first iteration here (all four variants lead to the same)
    ull y = 2*n*n;
    ull z = (y+1)*n;
    if (z <= 2*N)
    {
      result += z/2;
      triples.clear();
      triple t(x,y,z);
      triples.insert(t);
      result += check(t, triples);
    }
  }

  printf("%lld\n", result);
  return 0;
}
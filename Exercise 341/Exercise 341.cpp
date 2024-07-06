#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include <boost/multiprecision/gmp.hpp> 

using boost::multiprecision::mpz_int;
using namespace std;
typedef unsigned long long int ll;

// checkpoints
struct Node {
  mpz_int value; // cumulative value
  ll times; // repetition times
  mpz_int start; // starting index
};

bool operator<(const Node &lhs, const Node &rhs) {
  return lhs.start < rhs.start;
}

vector<Node> f;

mpz_int F(mpz_int n) { // find F(n) from f(n)
  ll idx = upper_bound(f.begin(), f.end(), Node{0,0,n}) - f.begin() - 1;
  return f[idx].value + idx*(n-f[idx].start);
}

mpz_int G(mpz_int n) { // find G(n) from F(n)
  mpz_int lo = 1, hi = n;
  while (lo != hi) {
    mpz_int mi = lo + (hi-lo+1)/2; //(lo + hi + 1)/2;
    if (n < F(mi)) {
      hi = mi - 1;
    } else { // F(mi) <= n
      lo = mi;
    }
  }
  return lo;
}

int main() {
  ll prevbest = 1, N = 1E7 + 1E6;
  f.reserve(N + 1);
  f.push_back(Node{0,0,0});
  f.push_back(Node{1,1,1});
  f.push_back(Node{2,2,2});
  for (ll d = 3; d <= N; d++) { // compute the checkpoint for differences = d
    Node temp;
    temp.value = f.back().value + f.back().times*(d-1);
    temp.start = f.back().start + f.back().times;
    ll idx = upper_bound(f.begin(), f.end(), Node{temp.start,0,0},
			 [](const Node &lhs, const Node &rhs) { return lhs.value < rhs.value; }) - f.begin() - 1;
    temp.times = idx;
    f.push_back(temp);
    if (f.back().value > prevbest*10) {
      prevbest *= 10;
      cout << "at d: " << setw(10) << d << " exceeded " << setw(20) << prevbest << "\n";
    }
  }

  cout << "Last checkpoint:\n"
       << "Starting index :" << f.back().start << "\n"
       << "Value          :" << f.back().value << "\n"
       << "Times repeated :" << f.back().times << "\n"
       << "Differences    :" << f.size() - 1 << "\n";

  mpz_int s = 0;
  for (ll i = 1; i < 1000000; i++)
    s += G(i*i*i);
  cout << s << endl;

  return 0;
}
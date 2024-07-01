#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> vi;

const int N = 11;
const int TH = 2011;

int dist(const vi& v) {
  int cur = 0;
  int num_mv = 0;
  vi a(v);
  while(cur < N)
    {
      if(a[cur] == cur)
        {
          ++cur;
          continue;
        }
      int j = cur;
      while(a[j] != cur)
        ++j;
      if(j < N-1)
        {
          ++num_mv;
          reverse(a.begin()+j, a.end());
        }
      ++num_mv;
      reverse(a.begin()+cur, a.end());
    }
  return num_mv;
}

int main() {
  vi v(N);
  vector<vi> maxi;
  int m = 0;
  for(int i = 0; i < N; ++i)
    v[i] = i;
  do {
    int t = dist(v);
    if(t > m)
      {
        maxi.clear();
        m = t;
      }
    if(t == m && int(maxi.size()) < TH)
      maxi.push_back(v);
  } while(next_permutation(v.begin(), v.end()));

  for(int i = 0; i < N; ++i)
    cout << char(maxi[TH-1][i]+'A');
  cout << endl;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10000000

char s[N+1];
long long t[N+1];
int w[11*4*3*2*2];
int m[] = {0, 11, 4, 3, 2, 2};
int mm[5], sm[5];
int p[] = {5, 13, 17, 29, 37, 41, 0};
long long A[500];
long long res;

__int128 diff(__int128 t, int a, int b, int c) {
  __int128 s = a + b + c;
  return t*t - s*(s - 2*a)*(s - 2*b)*(s - 2*c);
}

void compose(long long c, int s) {
  int n = 0;
  long long a = c - 1;
  long long b = 1;
  int i, j, k;
  while (a > 0) {
    while (a*a + b*b < c*c) b++;
    if (a*a + b*b == c*c) A[n++] = a;
    a--;
  }
  int cnt = 0;
  for (i = 0; i < n; i++) {
    for (j = i; j < n; j++)
      for (k = j; k < n; k++) {
        if (!diff(A[i]*A[n-1-i] + A[j]*A[n-1-j] + A[k]*A[n-1-k], A[i], A[j], A[k])) cnt++;
        else if (!diff(A[i]*A[n-1-i] + A[j]*A[n-1-j] - A[k]*A[n-1-k], A[i], A[j], A[k])) cnt++;
        else if (!diff(A[i]*A[n-1-i] - A[j]*A[n-1-j] + A[k]*A[n-1-k], A[i], A[j], A[k])) cnt++;
        else if (!diff(-A[i]*A[n-1-i] + A[j]*A[n-1-j] + A[k]*A[n-1-k], A[i], A[j], A[k])) cnt++;
      }
  }
  w[s] = cnt + n/2;
}

void dfs(int r, int i, int k, int s) {
  int j;
  compose(r, s);
  r *= p[i];
  for (j = 1; r <= N && j <= k; j++, r *= p[i]) dfs(r, i + 1, j, s*m[i] + j);
}

int cmp(const void *a, const void *b) {
  return *(int *)b - *(int *)a;
}

void dfs2(long long n, int p, int d) {
  memcpy(sm, mm, sizeof mm);
  qsort(sm, d, sizeof *sm, cmp);
  int sum = 0;
  int i;
  for (i = 0; i < d; i++) sum = sum*m[i] + sm[i];
  res += t[N/n]*w[sum]*n;
  while (n*p <= N) {
    if (!s[p]) {
      int j = 1;
      long long nn = n*p;
      while (nn <= N) {
        mm[d] = j;
        dfs2(nn, p + 4, d + 1);
        nn *= p;
        j++;
      }
    }
    p += 4;
  }
}

int main() {
  int i, j;
  dfs(1, 0, 100, 0);
  for (int i = 2; i <= N; i++)
    if (!s[i])
      for (j = i*2; j <= N; j += i)
        s[j] = 1;
  for (i = 5; i <= N; i += 4)
    if (!s[i])
      for (j = i; j <= N; j += i)
        t[j] = 1;
  for (i = 1; i <= N; i++) t[i] = t[i-1] + (t[i] ? 0 : i);
  dfs2(1, 5, 0);
  printf("%lld\n", res);
}
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define ll long long
#define alok(n,t) (t*)malloc((n)*sizeof(t))
#define m 1000000000000000000LL

int main(int argc, char **argv) {
    ll tt = clock();
    int n = argc <= 1 ? 1000 : atoi(argv[1]);
    int v;
    
    // initialize grundy numbers
    int *nimbs = alok(n + 1, int);
    nimbs[0] = 0;
    nimbs[1] = 1;
    for (int k = 2; k < n; k++) nimbs[k] = (nimbs[k - 1] ^ nimbs[k - 2]) + 1;
    
    // initialize the arrays
    int mx = 500000;
    // for a fixed k, cnt[x] contains the number of contributions of f[k][x]
    ll *cnt2 = alok(mx, ll);
    ll *cnt1 = alok(mx, ll);
    ll *cnt0 = alok(mx, ll);
    // for a fixed k, ask[i] is a list of x's with nonzero cnt[k][x].
    ll *ask2 = alok(mx, ll);
    ll *ask1 = alok(mx, ll);
    ll *ask0 = alok(mx, ll);
    // len is the number of elements in the array "ask"
    int len2 = 0;
    int len1 = 0;
    int len0 = 0;
    for (int i = 0; i < mx; i++) {
        cnt2[i] = 0;
        cnt1[i] = 0;
        cnt0[i] = 0;
    }
    // base case: f[n][1] has 1 contribution
    ask0[len0++] = 1;
    cnt0[1] = 1; 
    
    ll s = 0;
    for (int val, k = n;; ) {
        
        while (len0 > 0) {
            int x = ask0[--len0];
            if (x == 0 || (x == 1 && k == 2)) {
                // base case. add all the contributions of this f[k][x].
                s += cnt0[x];
                if (s >= m) s -= m;
            } else {
                // inductive case. The contributions of this f[k][x] is the sum
                // of the contributions of two smaller values,
                // f[k-1][G[k-2]^(x-1)] and f[k-2][G[k-1]^(x-1)]
                v = nimbs[k - 2] ^ (x - 1);
                if (v < mx) {
                    if (cnt1[v] == 0) ask1[len1++] = v; // this is a newly-encountered value. add it to the list
                    cnt1[v] += cnt0[x]; // update the contribution count
                    if (cnt1[v] >= m) cnt1[v] -= m;
                }
                v = nimbs[k - 1] ^ (x - 1);
                if (v < mx) {
                    if (cnt2[v] == 0) ask2[len2++] = v;
                    cnt2[v] += cnt0[x];
                    if (cnt2[v] >= m) cnt2[v] -= m;
                }
            }
            cnt0[x] = 0; // clear the cnt array in preparation for the next loop
        }
        if (--k == 0 || !(len1 > 0 || len2 > 0)) break; // stop when k becomes zero, or there are no more to process
        
        // do the above code two more times, instead of swapping arrays
        while (len1 > 0) {
            int x = ask1[--len1];
            if (x == 0 || (x == 1 && k == 2)) {
                s += cnt1[x];
                if (s >= m) s -= m;
            } else {
                v = nimbs[k - 2] ^ (x - 1);
                if (v < mx) {
                    if (cnt2[v] == 0) ask2[len2++] = v;
                    cnt2[v] += cnt1[x];
                    if (cnt2[v] >= m) cnt2[v] -= m;
                }
                v = nimbs[k - 1] ^ (x - 1);
                if (v < mx) {
                    if (cnt0[v] == 0) ask0[len0++] = v;
                    cnt0[v] += cnt1[x];
                    if (cnt0[v] >= m) cnt0[v] -= m;
                }
            }
            cnt1[x] = 0;
        }
        if (--k == 0 || !(len2 > 0 || len0 > 0)) break;
        
        while (len2 > 0) {
            int x = ask2[--len2];
            if (x == 0 || (x == 1 && k == 2)) {
                s += cnt2[x];
                if (s >= m) s -= m;
            } else {
                v = nimbs[k - 2] ^ (x - 1);
                if (v < mx) {
                    if (cnt0[v] == 0) ask0[len0++] = v;
                    cnt0[v] += cnt2[x];
                    if (cnt0[v] >= m) cnt0[v] -= m;
                }
                v = nimbs[k - 1] ^ (x - 1);
                if (v < mx) {
                    if (cnt1[v] == 0) ask1[len1++] = v;
                    cnt1[v] += cnt2[x];
                    if (cnt1[v] >= m) cnt1[v] -= m;
                }
            }
            cnt2[x] = 0;
        }
        if (--k == 0 || !(len0 > 0 || len1 > 0)) break;
    }
    printf("%d %lld %.3f s.\n", n, s, 1e-3 * (clock() - tt));
}
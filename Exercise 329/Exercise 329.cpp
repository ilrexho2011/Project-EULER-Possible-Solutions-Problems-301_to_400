#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;
#define ull unsigned long long
#define MAXN 501
#define MAXC 16
bool croak[MAXC] = {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0};
pair<ull, ull> ans, p[MAXN][MAXC]; // p[i][j] represents the probability that the jth croak was on the ith square
ull gcd(ull a, ull b)
{
    if (!b) return a;
    return gcd(b, a%b);
}
ull lcm (ull a, ull b)
{
    return a/gcd(a, b) * b;
}
bool prime(int n)
{
    if (n==1) return false;
    for (int i = 2; i <= floor(sqrt(n)); i++) if (!(n%i)) return false;
    return true;
}
void init()
{
    for (int i = 1; i < MAXN; i++) p[i][1] = (prime(i)?make_pair(2,3):make_pair(1,3));
}
pair<ull, ull> add (pair<ull, ull> a, pair<ull, ull> b)
{
    ull tmp = lcm(a.second, b.second), num = a.first*(tmp/a.second) + b.first*(tmp/b.second), den = tmp, g = gcd(num, den);
    return make_pair(num/g, den/g);
}
pair<ull, ull> mult (pair<ull, ull> a, pair<ull, ull> b)
{
    ull g1 = gcd(a.first, a.second), g2 = gcd(b.first, b.second);
    a.first /= g1, a.second /= g1, b.first /= g2, b.second /= g2;
    g1 = gcd(a.first, b.second), g2 = gcd(b.first, a.second);
    a.first /= g1, b.second /= g1, b.first /= g2, a.second /= g2;
    return make_pair(a.first*b.first, a.second*b.second);
}
pair<ull, ull> div (pair<ull, ull> a, int b)
{
    ull g = gcd(a.first, a.second*b);
    return make_pair(a.first/g, (a.second*b)/g);
}
void solve()
{
    for (int i = 2; i < MAXC; i++)
        for (int j = 1; j < MAXN; j++)
        {
            p[j][i] = (!(croak[i-1]^prime(j))?make_pair(2,3):make_pair(1,3));
            if (j==2) p[2][i] = mult(p[2][i], add(p[1][i-1], div(p[3][i-1], 2)));
            else if (j==MAXN-2) p[MAXN-2][i] = mult(p[MAXN-2][i], add(p[MAXN-1][i-1], div(p[MAXN-3][i-1], 2)));
            else if (j==1) p[1][i] = mult(p[1][i], div(p[2][i-1], 2));
            else if (j==MAXN-1) p[MAXN-1][i] = mult(p[MAXN-1][i], div(p[MAXN-2][i-1], 2));
            else p[j][i] = mult(p[j][i], div(add(p[j+1][i-1], p[j-1][i-1]), 2));
        }
}
void output()
{
    ans = p[1][MAXC-1];
    for (int i = 2; i < MAXN; i++) ans = add(ans, p[i][MAXC-1]);
    ans = div(ans, MAXN-1);
    cout << ans.first << "/" << ans.second << endl;
}
main()
{
    init();
    solve();
    output();
}
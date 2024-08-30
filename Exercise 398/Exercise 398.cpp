#include <iostream>
#include <iomanip>
#include <cassert>

inline long double binomial(unsigned n, unsigned r)
{
    if ((int) n < 0) return 0;
    if (n == 0) return r == 0;
    long double f = 1;
    for (unsigned i = 1; i <= r; i++) f = f*n-- / i;
    return f;
}

int main(int argc, char* argv[])
{
    const unsigned n = 10000000;
    const unsigned m = 100;

    long double result = 0;

    long double bb = binomial(n-2, m-2-1);
    for (unsigned q = m; q <= n; q++)
    {
        //long double bb = binomial(n-q+m-2 -1, m-2-1);
        bb *= (n-q+1) / (long double)(n-(q-1)+m-2-1);

        for (unsigned k = 1; k < m; k++)
        {
            unsigned qq = q-(k-1);
            if (qq < m) break;
            if (!(qq % m)) result += bb * (qq/m) * k;        // d1=d2 possible!

            unsigned mind2 = qq/m+1;            // inclusive
            unsigned maxd2 = (qq+(m-2)) / (m-1);    // exclusive
            /*for (unsigned d2 = mind2; d2 < maxd2; d2++)
            {
                unsigned d1 = qq-(m-1)*d2;
                assert((int)d1 > 0);
                assert((int)d1 < d2);
                if (d1+d2 < n && d1+(m-1)*d2 == qq) result += bb*d2 * (d1==d2 ? k : m);
            }*/
            unsigned tmp = (maxd2*(maxd2-1) - mind2*(mind2-1)) / 2;
            result += tmp * m * bb;

        }
    }

    std::cout << std::fixed << std::setprecision(5) << result/binomial(n-1, m-1) << std::endl;
    return 0;
}
#include <stdio.h>
#include <math.h>

typedef long double ldbl;

#define K 20000
#define N 1000000

#define lfact(n) (lgammal((n)+1))

int main(void)
{
    ldbl log_kn = K * logl(N);
    ldbl log_2 = logl(2);
    ldbl sum = 0.0;
    for (int n2 = 0; n2 <= K/2; n2++) {
        int k1 = K-n2;
        int k2 = K-2*n2;
        sum += expl(lfact(N) - lfact(N-k1) + lfact(K) - lfact(k2) - lfact(n2) - log_2*n2 - log_kn);
    }
    printf("%.10Lf\n", 1.0L-sum);
    return 0;
}
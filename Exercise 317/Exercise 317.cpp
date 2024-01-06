#include <cstdio>
#include <cmath>
#include <algorithm>

int main() {
    static const double G = 9.81;
    static const double V = 20.0;
    static const double Y0 = 100.0;
    static const double MAXY = Y0 + V*V/G/2;

    double maxx = 0.0;
    static const size_t NA = 10000000;
    for (size_t j = 0; j <= NA; ++j) {
        const double alpha = double(j)/NA*M_PI/2;
        const double d = V*V*sin(alpha)*sin(alpha) + 2.0*Y0*G;
        if (d >= 0.) {
            const double x = V*cos(alpha)*(V*sin(alpha) + sqrt(d))/G;
            maxx = std::max(x, maxx);
        }
    }

    printf("%.4lf\n", maxx*maxx*M_PI*MAXY/2);

    return 0;
}
namespace Euler::Problem340 {
    constexpr auto MODULO = 1000000000ULL;

    constexpr unsigned long long mul(unsigned long long a, unsigned long long b) {
        return a * b % MODULO;
    }

    constexpr unsigned long long add(unsigned long long a, unsigned long long b) {
        return (a + b) % MODULO;
    }

    constexpr unsigned long long sub(unsigned long long a, unsigned long long b) {
        return (a + MODULO - b) % MODULO;
    }

    constexpr unsigned long long sum(unsigned long long a, unsigned long long rangeSize) {
        auto from1 = rangeSize * (rangeSize - 1) / 2 % MODULO;
        return add(mul(a, rangeSize), from1);
    }

    unsigned solve() {
        constexpr auto a = 1801088541ULL;
        constexpr auto b = 558545864083284007ULL;
        constexpr auto c = 35831808ULL;
        constexpr auto increment = mul(3, sub(a, c));
        constexpr auto extra = add(b, mul(4, sub(a, c)));
        constexpr auto bDivA = b / a;
        constexpr auto bModA = b % a;
        constexpr auto lowerInitial = sub(add(mul(increment, bDivA % MODULO), extra), bModA % MODULO);
        auto total = sum(lowerInitial, bModA + 1);
        for (auto steps = 0ULL; steps < bDivA; ++steps) {
            auto lower = sub(add(mul(increment, steps % MODULO), extra), (a - 1) % MODULO);
            total = add(total, sum(lower, a));
        }
        return static_cast<unsigned>(total % MODULO);
    }
}
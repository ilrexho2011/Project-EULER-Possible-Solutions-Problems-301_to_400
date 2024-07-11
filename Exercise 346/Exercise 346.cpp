#include <cstdio>
#include <cmath>

#include <set>

using namespace std;

typedef set<long long int> TCounts;

int main() {
	TCounts counts;
	counts.insert(1);

	// static const long long int BOUND = 1000ULL;
	static const long long int BOUND = 1000000000000ULL;
	static const long long int BASE_BOUND = sqrtf(BOUND) + 100;
	for (long long int base = 2; base < BASE_BOUND; ++base) {
		if (base % 10000 == 0) {
			fprintf(stderr, "%.2lf\n", 100.*base/BASE_BOUND);
		}
		long long int num = base*(base + 1) + 1;
		while (num < BOUND) {
			counts.insert(num);
			num = num*base + 1;
		}
	}

	long long int sum = 0;
	for (TCounts::const_iterator it = counts.begin(); it != counts.end(); ++it)
		sum += *it;

	printf("%lld\n", sum);

	return 0;
}
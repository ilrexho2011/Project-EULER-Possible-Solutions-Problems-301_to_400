#include <stdio.h>
#include <algorithm>

#define N 200000

int main()
{
	static int answers[N+1];
	long long sum = 0 + 0 + 1 + 2;
	answers[0] = 0;
	answers[1] = 0;
	answers[2] = 1;
	answers[3] = 2;
	// the current strategy
	int guessK = 0, guessS = 0;	// the first guess is g = n - 2(2^k+s) - 1
	int guessCost = 2;	// cost[g+1,n]
	// the next strategy
	int nextGuessK = 1, nextGuessS = 1;
	int nextGuessCost = 2;
	for (int n = 4; n <= N; n++) {
		// update cost after n++
		guessCost += guessK + 1;
		nextGuessCost += nextGuessK + 1;
		// calculate total cost of the current strategy
		int guessPoint = n - (1 << (guessK + 1)) - 2 * guessS - 1;
		int totalCurrent = guessPoint + std::max(answers[guessPoint - 1], guessCost);
		// calculate total cost of the next strategy
		int nextGuessPoint = n - (1 << (nextGuessK + 1)) - 2 * nextGuessS - 1;
		if (nextGuessPoint > 0) {
			int totalNext = nextGuessPoint + std::max(answers[nextGuessPoint - 1], nextGuessCost);
			// advance to the next strategy if needed
			if (totalCurrent >= totalNext) {
				totalCurrent = totalNext;
				guessK = nextGuessK;
				guessS = nextGuessS;
				guessCost = nextGuessCost;
				int i;
				for (i = 0; i < nextGuessK; i++)
					if ((nextGuessS & (1 << i)) == 0)
						break;
				if (i == nextGuessK) {
					nextGuessK++;
					nextGuessS = 3;
					nextGuessCost = (nextGuessK + 1) * n - (nextGuessK << (nextGuessK + 1)) + nextGuessK + 3;
				} else {
					int numOneBits = 0;
					for (int j = i + 1; j < nextGuessK; j++)
						if (nextGuessS & (1 << j))
							numOneBits++;
					if (i < numOneBits + 3) {
						nextGuessS += 1 << i;
						nextGuessCost += (i - numOneBits) << (i + 1);
					} else {
						nextGuessS += 1 << (numOneBits + 3);
						nextGuessCost += 3 << (i + 1);
					}
				}
			}
		}
		answers[n] = totalCurrent;
		sum += totalCurrent;
	}
	printf("%lld\n", sum);
	return 0;
}
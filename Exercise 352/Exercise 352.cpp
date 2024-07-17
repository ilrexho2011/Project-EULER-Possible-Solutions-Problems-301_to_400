#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>

using namespace std;

typedef long double ld;

ld Solve(int population, ld singleProbabilityOfInfection) {
  vector<ld> probabilityOfNoInfections(population + 1);
  vector<ld> probabilityOfAtLeastOneInfection(population + 1);

  probabilityOfNoInfections[0] = 1;
  for (int i = 1; i <= population; i++) {
    probabilityOfNoInfections[i] = probabilityOfNoInfections[i - 1] * (1 - singleProbabilityOfInfection);
  }

  for (int i = 0; i <= population; i++) {
    probabilityOfAtLeastOneInfection[i] = 1 - probabilityOfNoInfections[i];
  }

  vector<ld> bestWithoutInformation(population + 1);
  vector<ld> bestWithAtLeastOnePositive(population + 1);

  iota(bestWithAtLeastOnePositive.begin(), bestWithAtLeastOnePositive.end(), 0);
  iota(bestWithoutInformation.begin(), bestWithoutInformation.end(), 0);

  bestWithAtLeastOnePositive[1] = 0;

  for (int i = 2; i <= population; i++) {

    {
      /// compute bestWithAtLeastOnePositive[i]
      for (int j = 1; j < i; j++) {
        
        ld pAtLeastOneInfection = probabilityOfAtLeastOneInfection[j] / probabilityOfAtLeastOneInfection[i];

        bestWithAtLeastOnePositive[i] = min(bestWithAtLeastOnePositive[i],
          1 + pAtLeastOneInfection * (bestWithAtLeastOnePositive[j] + bestWithoutInformation[i - j]) + (1 - pAtLeastOneInfection) * (bestWithAtLeastOnePositive[i - j]));
      }
    }

    {
      /// compute bestWithoutInformation[i]

      for (int j = 1; j <= i; j++) {
        /// sample j
        bestWithoutInformation[i] = min(bestWithoutInformation[i],
          1 + bestWithoutInformation[i - j] + probabilityOfAtLeastOneInfection[j] * bestWithAtLeastOnePositive[j]);
      }
    }
  }
  return bestWithoutInformation[population];
}

int main() {
  ld sol = 0;
  for (int iter = 1; iter <= 50; iter++) {
    ld p = 0.01 * iter;
    cout << iter << "\n";
    sol += Solve(10000, p);
  }
  cout << fixed << setprecision(6) << sol << "\n";
}

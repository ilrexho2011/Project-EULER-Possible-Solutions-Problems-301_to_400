#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

template<typename T>
bool isPrime(T num)
{
  if(num < 2) return false;
  if(num == 2) return true;
  if(num % 2 == 0) return false;
  
  T max = floor(sqrt(num))+1;
  for(T i = 3; i < max; i+= 2)
    if(num % i == 0) return false;
  return true;
}

int main()
{
  long long int result = 1;
  clock_t start;
  start = clock();
  for(long long int i = 2; i < 100000000; i+=4)
  {
    bool isValid = true;
    long long int max = floor(sqrt(i))+1;
    for(long long int l = 1; l < max; l++)
    {
      if(i % l) continue;
      if(!isPrime<long long int>(l + i/l))
      {
	 isValid = false;
	 break;
      }
    }
    if(isValid) result += i;
  }
  cout << "Time is: " << (double)(clock() - start) / CLOCKS_PER_SEC;
  cout << "\nThe result is: " << result;
  return 0;
}
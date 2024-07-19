#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int sMod( int, int, int );
int sum( int, int, int );

int main()
{
	int n, p, m;
	
	cout << "Number of terms in sum? ";
	cin >> n;
	
	cout << "Power? ";
	cin >> p;
	
	cout << "Modulus? ";
	cin >> m;
	
	cout << "The result is " << sum( n, p, m ) << ".\n";
	
	return 0;
}

int sMod( int i, int n, int m )
{
	int twoToI = 1, twoTo2I = 1, s1, s2, s3, h, j, s;
	
	for ( h = 1; h <= i; h ++ )
	{
		twoToI *= 2;
		twoToI %= m;
		
		twoTo2I *= 4;
		twoTo2I %= m;
	}	
	
	s1 = twoTo2I;
	s2 = twoToI;
	s3 = 3;
	
	for ( h = 3; h <= n; h ++ )
	{
		s = s1;
		
		for ( j = 0; j < i; j ++ )
		{
			s *= 2;
			s %= m;
		}
		
		for ( j = 0; j < i; j ++ )
		{
			s -= s3;
			s %= m;
		}
		
		//s = ( twoToI * s1 - i * s3 ) % m;
		s3 = s2;
		s2 = s1;
		s1 = s;
	}
	
	return s;
}

int sum( int n, int p, int m )
{
	int i, result = m - n - ( p % 2 == 0 ? 1 : 0 );
	cout << "result = " << result << ".\n";
	
	for ( i = 1; i <= n; i ++ )
	{
		cout << "i = " << i << ".\n";
		
		result += sMod( i, p, m );
		result %= m;
	}
	
	return result;
}
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
typedef unsigned char		u8;
typedef int			s32;
typedef unsigned int		u32;
typedef long long int		s64;
typedef unsigned long long int	u64;
#define N			10000000000ULL
#define M			100000000
#define	DEL			(1.0e-10)

struct Key {
	s32 v2;			// exponent of 2.
	vector<s32> v1;		// exponent of 4k+1 primes.
};

bool operator < (const Key &k1, const Key &k2) {
	if (k1.v2 != k2.v2) return k1.v2 < k2.v2;
	if (k1.v1 != k2.v1) return k1.v1 < k2.v1;
	return false;
}

// Exponent notation
struct Exp {
	u64 b;
	u64 e;
};

struct Twin {
	u64 x;
	u64 y;
};

class SquareSum {
	map<u64, Twin> cache;
	bool Serret(u64 p, Twin &t);
	bool Expand(u64 a, u64 b, u64 c, u64 d, vector<Twin> *u);
public:
	SquareSum() {};
	~SquareSum() {};
	bool Find(vector<Exp> &v, vector<Twin> &u);
};

/*
	Return sqrt(n). Ex:10->3
*/
u64 Sqrt(u64 n)
{
	return (u64)( sqrt((double)n + DEL) );
}

/* 
	Return a^n (mod p)
*/
u64 PowMod(u64 a, u64 n, u64 p) {
	if (n == 0) return 1;
	if (n % 2 == 0) return PowMod( a * a % p, n / 2, p);
	return a * PowMod( a, n - 1, p ) % p;
}

/*
	Return (a|n).
	(a|n) = 0  if a = 0 (mod p)
		  = +1 if x^2 = a (mod p) for some x
		  = -1 if there is no such x
*/
s64 Jacobi(s64 a, s64 n)
{
	s64 t = 1;
	while (a != 0) {
		while (a % 2 == 0) {
			a = a / 2;
			if (n % 8 == 3 || n % 8 == 5) t = -t;
		}
		s64 tmp = a;	a = n;	n = tmp;
		if (a % 4 == 3 && n % 4 == 3) t = -t;
		a = a % n;
	}
	if (n == 1) return t;
	return 0;
}

/*
	Find x who satisfies x*x=n (mod prime p) by Shanks-Tonelli algorithm.
	https://www.codecodex.com/wiki/Shanks-Tonelli_algorithm
*/	
u64 Residue(u64 prime, u64 arg)
{
	u64 y = 2, b, t, result;
	u32 r = 0, m, q = prime - 1;
	if (Jacobi(arg, prime) == -1) return -1;
	while (Jacobi(y, prime) != -1) y ++;
	result = prime - 1;
	while (q % 2 == 0) {
		r ++;
		q /= 2;
	}
	result >>= r;
	y = PowMod(y, result, prime);
	result >>= 1;
	b = PowMod(arg, result, prime);
	result = arg * b;
	result = result % prime;
	b = result * b;
	b = b % prime;
	while(b!=1) {   
		t = b * b;
		t = t % prime;
		for (m = 1; t!=1; m++) {
			t = t * t;
			t = t % prime;
		}
		t=0;
		t |= (1ULL << (r-m-1));
		t = PowMod(y, t, prime);
		y = t*t;
		r = m;
		result = result * t;
		result = result % prime;
		b = b * (y%prime);
		b = b %prime;
	}  
	return result;
}

/*
	Express prime p as a sum of squared two integers, based on Serret's algorithm.
	See p.122 of "The higher arithmetic: an introduction to the theory of numbers" 7th edition.
*/
bool SquareSum::Serret(u64 p, Twin &t)
{
	if (p == 2) {
		t.x = t.y = 1;
		return true;
	}
	if (p % 4 != 1) return false;
	map<u64, Twin>::iterator it = cache.find(p);
	if (it != cache.end()) {
		t = it->second;
		return true;
	}
	t.x = p;
	t.y = Residue(p, p - 1);
	if (2 * t.y >= p) t.y = p - t.y;
	vector<u64> v;
	while (t.y > 0) {
		v.push_back(t.x / t.y);
		u64 y_tmp = t.y;
		t.y = t.x - (t.x / t.y) * t.y;
		t.x = y_tmp;
	}
	t.x = v[v.size() / 2];
	t.y = 1;
	for (vector<u64>::size_type i = v.size() / 2 + 1; i < v.size(); i ++) {
		u64 x_tmp = t.x;
		t.x = v[i] * t.x + t.y;
		t.y = x_tmp;
	}
	if (2 * t.x >= p) {
		t.x = p - t.x;
	}
	t.y = Sqrt(p - t.x * t.x);
	if (t.y < t.x) {
		u64 tmp = t.x;
		t.x = t.y;
		t.y = tmp;
	}
	cache.insert(pair<u64, Twin>(p, t));
	return true;
}

bool SquareSum::Expand(u64 a, u64 b, u64 c, u64 d, vector<Twin> *u)
{
	Twin t;
	if (a * c >= b * d)
		t.x = a * c - b * d;
	else
		t.x = b * d - a * c;
	t.y = a * d + b * c;
	if (t.y < t.x) {
		u64 tmp = t.x;
		t.x = t.y;
		t.y = tmp;
	}
	for (vector<Twin>::size_type i = 0; i < u->size(); i ++) {
		if (u->at(i).x == t.x) return false;
	}
	u->push_back(t);
	return true;
}

/* 
	Find all twins x>0 and y>0 which satisfy x^2+y^2=n (x<y).
	n is given as the form of exponent expression.
*/
bool SquareSum::Find(vector<Exp> &v, vector<Twin> &u)
{
	u64 n = 0;
	vector<u64> v1, v2;
	for (vector<Exp>::size_type i = 0; i < v.size(); i ++) {
		if (v[i].b == 2 || v[i].b % 4 == 1) {
			for (u64 j = 0; j < v[i].e; j ++) v1.push_back(v[i].b);
			n += v[i].e;
		} else {
			if (v[i].e % 2 != 0) return false;
			for (u64 j = 0; j < v[i].e / 2; j ++) v2.push_back(v[i].b);
		}
	}
	if (v1.empty()) return false;
	vector<Twin> w, *u1, *u0, *u_tmp;
	if (n % 2 == 1) {
		u0 = &u;	u1 = &w;
	} else {
		u0 = &w;	u1 = &u;
	}
	Twin t1;
	if (!Serret(v1[0], t1)) {
		t1.x = t1.y = v1[0];
	}
	u0->push_back(t1);
	for (vector<u64>::size_type i = 1; i < v1.size(); i ++) {
		if (Serret(v1[i], t1)) {
			for (vector<Twin>::size_type j = 0; j < u0->size(); j ++) {
				Expand(u0->at(j).x, u0->at(j).y, t1.x, t1.y, u1);
				Expand(u0->at(j).x, u0->at(j).y, t1.y, t1.x, u1);
			}
		}
		u_tmp = u0;
		u0 = u1;
		u1 = u_tmp;
		u1->clear();
	}
	for (vector<u64>::size_type i = 0; i < v2.size(); i ++) {
		for (vector<Twin>::size_type j = 0; j < u0->size(); j ++) {
			u0->at(j).x *= v2[i];
			u0->at(j).y *= v2[i];
		}
	}
	return true;
}

map<Key,u64> memo;
SquareSum ss;
u32 i_max;
u64 *prime;

// Calculate the number of square pairs
// by Serret algorithm with memorization.
u64 Check_MyOriginal(Key & key)
{
	map<Key,u64>::iterator i = memo.find(key);
	u64 r = 0;
	if (i == memo.end()) {
		vector<Exp> w;
		if (key.v2 > 0) {
			Exp ex = { 2, key.v2 };
			w.push_back(ex);
		}
		s32 l=1;
		for (u32 j = 0; j < key.v1.size(); j ++) {
			while (prime[l] % 4 != 1) l ++;
			Exp ex = { prime[l], key.v1[j] };
			l ++;
			w.push_back(ex);
		}
		vector<Twin> u;
		ss.Find(w, u);
		for (u32 j = 0; j < u.size(); j ++) {
			if (u[j].x == 0 || u[j].y == 0) continue;
			r ++;
		}
		memo.insert(pair<Key,u64>(k, r));
	} else {
		r = i->second;
	}
	return r > 2 ? r*(r-1)*(r-2)/6 : 0;
}

// Calculate the number of square pairs
// by the formula (17) in https://mathworld.wolfram.com/SumofSquaresFunction.html
u64 Check(Key & key)
{
	u64 r = 1;
	for (u32 i = 0; i < key.v1.size(); i ++) {
		r *= key.v1[i] + 1;
	}
	if (r % 2 == 0) r /= 2;
	else if (key.v2 % 2 == 0) r = (r - 1) / 2;
	else r  = (r + 1) / 2;
	return r > 2 ? r*(r-1)*(r-2)/6 : 0;;
}

// Recursive search
u64 Next(u32 i_min, u64 s, Key & key)
{
	u64 r = 0;
	bool end = false;
	for (u32 i = i_min; !end && i < i_max; i ++) {
		u64 s_new = s;
		s32 m = prime[i] % 4;
		if (m == 1) key.v1.push_back(0);
		if (m == 2) key.v2 = 0;
		for (s32 k = 1; ; k ++) {
			if (m == 1)  {
				key.v1.back() ++;
				s_new *= prime[i];
			}
			if (m == 2) {
				key.v2 ++;
				s_new *= prime[i];
			}
			if (m == 3) {
				s_new *= prime[i] * prime[i];
			}
			if (4 * s_new > N) {
				if (k == 1 && m == 1) end = true;
				break;
			}
			r += Check(key);
			//r += Check_MyOriginal(key);
			r += Next(i + 1, s_new, key);
		}
		if (m == 1) key.v1.pop_back();
		if (m == 2) key.v2 = 0;
	}
	return r;
}

int main(int argc, char* argv[])
{
	prime = ArrayOfPrimes(M);		// snip.
	i_max = NumOfPrimes(M);			// snip.

	// Begin a recursive search.
	Key key;
	u64 ans = Next(0, 1, key);	
	cout << ans << endl;
}
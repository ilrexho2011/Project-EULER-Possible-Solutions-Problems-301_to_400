#include <stdio.h>

typedef unsigned int u_int;
typedef unsigned long long u_llong;

enum { LIMIT = 9998 };

// least significant digit starts at tri[0]
void baseinc( u_int base, u_int num[] ) {
  u_int d;

  for ( d=0 ;; d++ ) {
    if ( ++num[d] >= base )
      num[d] = 0;
    else
      break;
  }
}

// this isn't a true base10 conversion
u_llong base10( u_int num[], u_int maxd ) {
  u_int d, ld; // digit, last digit
  u_llong e = 1,
          base10 = 0;

  for ( ld=maxd-1; !num[ld] && ld; ld-- );

  for ( d=0; d<=ld; d++, e*=10ULL )
    base10 += num[d] * e;

  return base10;
}

u_llong find12( u_llong n ) {
  u_int tri[30] = {0}; // trinary number
  u_llong d, mag = 1;

  // start with smallest 012 number with the same magnitude to save some marginal cycles
  for ( d=n; d/=10; mag++ );
  tri[mag-1] = 1;
  for ( d=base10( tri, 30 ); d%n; baseinc( 3, tri ), d=base10( tri, 30 ) );
  return d;
}

void main() {
  u_llong n, sum = 0;

  for ( n=1; n<=LIMIT; n++ )
    sum += find12( n ) / n;

  // account for 9999 and 10000
  sum += 1111333355557778 + 1;

  printf( "%I64Lu\n", sum );
}
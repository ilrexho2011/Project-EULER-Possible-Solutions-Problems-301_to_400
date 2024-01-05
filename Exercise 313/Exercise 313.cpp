#include<stdio.h>

int n;
bool sieve[1000010];

long long ans = 0;

long long B(long long num, long long c) {
	return c - (3*num);
}

long long Search(long long num) {
	bool sqgrid = false;
	if (num>999800010000ll) {
//		printf("%lld %lld\n", num, num%8);
	}
	if (num%8==5) {
		sqgrid = true;
		printf("%lld\n", num);
	}

	long long ub, lb;

	long long c = (13 + num) >> 1;
	long long a = (((num+13)+5) / 6)-1;
	long long b = B(a, c);

	if ((a==2)&&(b==1)) {
		ub = a;
	} else if ((a>b)&&(b>1)) {
		ub = a;
	} else
		ub = a-1;

	long long left = 1, right = ub+1, mid;
	while (left<right) {
		mid = left + ((right-left)/2);
		b = B(mid, c);
		if (mid>b)
			right = mid;
		else
			left = mid+1;
	}
	lb = left;
		
	return (((ub-lb+1)>0)?((ub-lb+1)*2):(0))+sqgrid;
}

int main() {
	scanf("%d", &n);
	for (long long i=2; i<=n; i++) {
		if (sieve[i]==false) {
			for (long long j=i*i; j<=n; j += i)
				sieve[j] = true;
			ans += Search(i*i);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
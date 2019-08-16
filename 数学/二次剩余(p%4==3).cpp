//https://ac.nowcoder.com/acm/contest/889/B
#include <bits/stdc++.h>
using namespace std;
const long long p = 1000000007;
long long qpow(long long a,long long b) {
	long long ret = 1;
	while (b) {
		if (b & 1) {
			ret *= a;
			ret %= p;
		}
		a *= a;
		a %= p;
		b >>= 1;
	}
	return ret;
}
long long b,c;
int main() {
	int T;
	scanf("%d",&T);
	while (T --) {
		scanf("%lld%lld",&b,&c);
		//(x^2-xb+c) % p==0
		long long d = ((b * b - 4ll * c) % p + p) % p;
		if (d == 0) {
			printf("%lld %lld\n",b/2,b/2);
		}
		else if (qpow(d,(p-1)/2) == 1) {
			long long sqrt_d = qpow(d,(p+1)/4);//仅在p%4==3时适用
			if ( (b ^ sqrt_d) & 1) sqrt_d = (p - sqrt_d) % p;//奇偶性不同的时候，下一步运算会有问题
			long long x = (b - sqrt_d) / 2;
			long long y = (b + sqrt_d) / 2;
			x = (x % p + p) % p;
			y = (y % p + p) % p;
			if (x > y) swap(x,y);
			printf("%lld %lld\n",x,y);
		}
		else printf("-1 -1\n");
	}
	return 0;
}

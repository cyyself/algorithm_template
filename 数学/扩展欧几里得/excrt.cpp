#include <cstdio>
long long exgcd(long long a,long long b,long long &x,long long &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	else {
		long long ret = exgcd(b,a%b,y,x);
		y -= x * (a / b);
		return ret;
	}
}
int main() {
	int k;
	while (scanf("%d",&k) == 1) {
		long long a1,r1;
		scanf("%lld%lld",&a1,&r1);
		if (k == 1) {
			if (a1 > r1) printf("%lld\n",r1);
			else printf("-1\n");
			continue;
		}
		bool flag = true;
		while (-- k) {
			long long a2,r2;
			scanf("%lld%lld",&a2,&r2);
			if (!flag) continue;
			long long k1,k2;
			long long g = exgcd(a1,a2,k1,k2);
			if ((r2 - r1) % g != 0) flag = false;
			k1 *= (r2 - r1) / g;
			long long xs = a2 / g;
			k1 = (k1 % xs + xs) % xs;
			r1 += k1 * a1;
			a1 = (a1 / g) * a2;
		}
		if (flag) printf("%lld\n",r1);
		else printf("-1\n");
	}
	return 0;
}

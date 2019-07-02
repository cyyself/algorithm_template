//给出一个n次多项式的n个f(x)=y，求出f(k)
#include <bits/stdc++.h>
using namespace std;
const long long mo = 998244353;
long long qpow(long long a,long long b) {
	long long ret = 1;
	while (b) {
		if (b & 1) {
			ret *= a;
			ret %= mo;
		}
		a *= a;
		a %= mo;
		b >>= 1;
	}
	return ret;
}
long long x[2000],y[2000];
int main() {
	int n;
	long long k;
	scanf("%d%lld",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%lld%lld",&x[i],&y[i]);
	}
	long long ans = 0;
	for (int i=0;i<n;i++) {
		long long tmp = 1;
		for (int j=0;j<n;j++) if (j != i) {
			tmp *= (x[i] - x[j] + mo) % mo;
			tmp %= mo;
		}
		tmp = qpow(tmp,mo-2);
		for (int j=0;j<n;j++) if (j != i) {
			tmp *= (k - x[j] + mo) % mo;
			tmp %= mo;
		}
		tmp *= y[i];
		tmp %= mo;
		ans += tmp;
		ans %= mo;
	}
	printf("%lld\n",ans);
	return 0;
}

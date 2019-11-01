const long long mo = 1e9+7;
long long fac[100005],inv[100005];
long long qpow(long long a,long long b) {
	long long ret = 1;
	while (b) {
		if (b & 1) {
			ret *= a;
			ret %= mo;
		}
		b >>= 1;
		a *= a;
		a %= mo;
	}
	return ret;
}
long long c(long long n,long long m) {
	if (n < 0 || m < 0 || m > n) return 0;
	return (((fac[n] * inv[m]) % mo) * inv[n-m]) % mo;
}
void init() {
	fac[0] = 1;
	for (int i=1;i<=100000;i++) {
		fac[i] = fac[i-1] * i;
		fac[i] %= mo;
	}
	inv[100000] = qpow(fac[100000],mo-2);
	for (int i=100000-1;i>=0;i--) {
		inv[i] = inv[i+1] * (i + 1LL);
		inv[i] %= mo;
	}
}

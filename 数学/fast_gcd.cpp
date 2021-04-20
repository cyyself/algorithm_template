long long gcd(long long a,long long b) {
	while (b^=a^=b^=a%=b);
	return a;
}

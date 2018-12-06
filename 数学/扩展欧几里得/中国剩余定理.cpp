//洛谷P1495 曹冲养猪
#include <cstdio>
long long exgcd(long long a,long long b,long long &x,long long &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	else {
		long long ret = exgcd(b,a%b,y,x);
		y -= x * (a/b);
		return ret;
	}
}
long long gcd(long long a,long long b) {
	if (b == 0) return a;
	else return gcd(b,a%b);
}
int a[10],b[10];
int main() {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d%d",&a[i],&b[i]);
	long long lcm = 1;
	long long ans = 0;
	for (int i=0;i<n;i++) lcm *= a[i] / gcd(a[i],lcm);
	for (int i=0;i<n;i++) {
		long long t = lcm / a[i];
		long long x,y;
		long long c = exgcd(t,a[i],x,y);
		ans = (ans + lcm + (b[i]*t*x)%lcm ) % lcm;
	}
	printf("%lld\n",ans);
	return 0;
}
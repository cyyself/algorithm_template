//洛谷P3382 【模板】三分法，输入一个N次函数和查找区间，求最值位置
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
int n;
double a[14];
inline double f(double x) {
	double ret = 0;
	for (int i=0;i<=n;i++) ret += a[i] * pow(x,n-i);
	return ret;
}
inline bool equal(double a,double b) {
	if (abs(a-b) < eps) return true;
	else return false;
}
int main() {
	double l,r;
	scanf("%d%lf%lf",&n,&l,&r);
	for (int i=0;i<=n;i++) scanf("%lf",&a[i]);
	while (!equal(l,r)) {
		double mid1 = l + (r-l)/3;
		double mid2 = l + 2 * (r-l) / 3;
		
		if (f(mid1) > f(mid2)) r = mid2;
		else l = mid1;
	}
	printf("%0.5lf\n",l);
	return 0;
}

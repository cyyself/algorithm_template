#include <bits/stdc++.h>
using std::swap;
#define eps 1e-8
int n;
double a[105][105];
bool gauss() {
	for (int i=0;i<n;i++) {
		int k = i;
		for (int j=i+1;j<n;j++) if (fabs(a[j][i]) > fabs(a[k][i])) k = j;
		double now = a[k][i];
		if (fabs(now) < eps) return false;
		for (int j=i;j<=n;j++) swap(a[i][j],a[k][j]);
		for (int j=i;j<=n;j++) a[i][j] /= now;
		for (int k=0;k<n;k++) if (k != i) {
			now = a[k][i];
			for (int j=i;j<=n;j++) a[k][j] -= now * a[i][j];
		}
	}
	return true;
}
int main() {
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		for (int j=0;j<=n;j++) scanf("%lf",&a[i][j]);
	if (gauss()) {
		for (int i=0;i<n;i++) printf("%0.2lf\n",a[i][n]);
	}
	else printf("No Solution\n");
	return 0;
}

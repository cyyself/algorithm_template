//给定n个整数（数字可能重复），求在这些数中选取任意个，使得他们的异或和最大。
#include <bits/stdc++.h>
using namespace std;
long long a[65];
int main() {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		long long tmp;
		scanf("%lld",&tmp);
		for (int j=log(tmp)/log(2);j>=0;j--) 
			if (tmp & (1LL << j)) {
				if (a[j]) tmp ^= a[j];
				else {
					a[j] = tmp;
					break;
				}
			}
	}
	long long ans = 0;
	for (int i=60;i>=0;i--) ans = max(ans,ans^a[i]);
	printf("%lld\n",ans);
	return 0;
}

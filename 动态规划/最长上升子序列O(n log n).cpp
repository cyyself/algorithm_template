//http://poj.org/problem?id=1631
#include <cstdio>
#include <algorithm>
using namespace std;
int a[40005];
int s[40005];
int main() {
	int T;
	scanf("%d",&T);
	while (T --) {
		int n;
		scanf("%d",&n);
		for (int i=0;i<n;i++) scanf("%d",&a[i]);
		s[0] = 0;
		int tail = 0;
		for (int i=0;i<n;i++) {
			if (a[i] > s[tail]) {
				s[++tail] = a[i];
				continue;
			}
			int p = upper_bound(s,s+tail,a[i]) - s;
			//上面的upper_bound实际上范围不包括最后一个元素
			s[p] = a[i];
		}
		printf("%d\n",tail);
	}
	return 0;
}

//https://www.luogu.org/problemnew/show/P3383
#include <bits/stdc++.h>
using namespace std;
bool judge[10000005];
vector <int> prime;
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	judge[1] = true;
	for (int i=2;i<=n;i++) {
		if (!judge[i]) prime.push_back(i);
		for (auto p:prime) {
			if (i * p > n) break;
			judge[i*p] = true;
			if (i % p == 0) break;
		}
	}
	while (m --) {
		int num;
		scanf("%d",&num);
		if (judge[num]) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}

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
			/*
			上一行是最难理解的地方，大概口胡一下：
			如果i%p==0，那么说明i是p本身或者i是一个合数
			那么欧拉筛要保证线性的话，就必须让一个数只能被它最小的质因子筛
			例如，当i=4,p=2时，我们筛掉了8就可以停止了
			此时下一个p=3，尽管4*3==12，但很显然，3并不是12的最小质因子
			而12的最小质因子是2，应该在i==6时被p==2的情况筛掉
			因此当我们做到i%p==0时就可以break了
			*/
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

#include <cstdio>
#include <cstring>
bool zhishu[10000005] = {0};
int main() {
	int N,M;
	scanf("%d%d",&N,&M);
	memset(zhishu,true,sizeof(zhishu));
	zhishu[1] = false;
    for (int i=2;i<N;i++) 
		if (zhishu[i]) //对于一个质数，它的倍数就不是质数
		for (int j=2*i;j<=N;j+=i) zhishu[j] = false;
	for (int i=0;i<M;i++) {
		int num;
		scanf("%d",&num);
		if (zhishu[num]) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
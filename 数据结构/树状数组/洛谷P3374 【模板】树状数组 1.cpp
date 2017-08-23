#include <cstdio>
int n;
int a[500005];
inline int lowbit(int x) {
	return x&(-x);
}
inline void add(int x,int d) {
	for (int i=x;i<=n;i+=lowbit(i)) a[i] += d;
}
inline int sum(int x) {
	int ret = 0;
	for (int i=x;i>=1;i-=lowbit(i)) ret += a[i];
	return ret;
}
inline int query(int x,int y) {
	return sum(y)-sum(x-1);
}
int main() {
	int m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		int t;
		scanf("%d",&t);
		add(i,t);
	}
	while(m--) {
		int o;
		scanf("%d",&o);
		if (o == 1) {
			int x,k;
			scanf("%d%d",&x,&k);
			add(x,k);
		}
		else {
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%d\n",query(x,y));
		}
	}
	return 0;
}
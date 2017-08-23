#include <cstdio>
int n;
int a[500000];//差分存储，树状数组维护
inline int lowbit(int n) {
	return n&(-n);
}
inline void add(int x,int d) {
	for (int i=x;i<=n;i+=lowbit(i)) a[i] += d;
}
inline int query(int x) {
	int ret = 0;
	for (int i=x;i>=1;i-=lowbit(i)) ret += a[i];
	return ret;
}
int main() {
	int m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		int t;
		scanf("%d",&t);
		add(i,t);
		add(i+1,-t);
	}
	while(m--) {
		int o;
		scanf("%d",&o);
		if (o == 1) {
			int x,y,k;
			scanf("%d%d%d",&x,&y,&k);
			add(x,k);
			add(y+1,-k);
		}
		else {
			int x;
			scanf("%d",&x);
			printf("%d\n",query(x));
		}
	}
	return 0;
}
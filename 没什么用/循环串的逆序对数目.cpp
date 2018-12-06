//HDU 1394:http://acm.hdu.edu.cn/showproblem.php?pid=1394
#include <bits/stdc++.h>
using namespace std;
struct DATA {
	int v;
	int pos;
	friend bool operator < (const DATA &a,const DATA &b) {
		return a.v < b.v;
	}
}d[5005];
int r[5005];
int tr[5005];
int n;
inline int lowbit(int x) {
	return x & (-x);
}
inline long long sum(int x) {
	long long ret = 0;
	for (int i=x;i>=1;i-=lowbit(i)) ret += tr[i];
	return ret;
}
inline void add(int x,int d) {
	for (int i=x;i<=n;i+=lowbit(i)) tr[i] += d;
}
int main() {
	while (scanf("%d",&n) == 1) {
		memset(tr,0,sizeof(tr));
		for (int i=1;i<=n;i++) {
			scanf("%d",&d[i].v);
			d[i].pos = i;
		}
		sort(d+1,d+1+n);
		int rank = 0;
		for (int i=1;i<=n;i++) {
			if (i == 1 || d[i].v != d[i-1].v) rank ++;
			r[d[i].pos] = rank;
		}
		long long cnt = 0;//这里所求即为未循环前的逆序对数
		for (int i=n;i>=1;i--) {
			cnt += sum(r[i]-1);
			add(r[i],1);
		}
		long long ans = cnt;
		for (int i=1;i<=n;i++) {
			cnt = cnt - 2*(r[i]-1) + n - 1;//rank从1开始，所以-1
			//将第一个数移动到最后，则逆序对数会减少r[i]-1个
			//同时，逆序对数会增加n-r[i]个
			//最后得cnt = cnt - 2*(r[i]-1) + n - 1;
			ans = min(ans,cnt);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

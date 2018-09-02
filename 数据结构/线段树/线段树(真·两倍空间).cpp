//https://www.luogu.org/problemnew/show/P3372
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
//两倍空间公式 {
#define node (l+r) | (l!=r)
#define mid (l+r)/2
#define lson (l+mid) | (l != mid)
#define rson (mid+1+r) | (mid+1 != r)
//两倍空间公式 }
struct segtree {
	long long sum;
	long long lazy;
}tr[200005];
long long init[100005];
inline void push_up(int l,int r) {
	tr[node].sum = tr[lson].sum + tr[rson].sum;
}
void build_tree(int l,int r) {
	if (l == r) {
		tr[node].sum = init[l];
	}
	else {
		build_tree(l,mid);
		build_tree(mid+1,r);
		push_up(l,r);
	}
}
long long sum(int l,int r,int L,int R) {//小写的l和r是当前节点区间，大写的L和R是要操作的区间
	if (l == L && r == R) return tr[node].sum;
	else {
		if (R <= mid) return (R - L + 1LL) * tr[node].lazy + sum(l,mid,L,R);
		if (L >= mid + 1) return (R - L + 1LL) * tr[node].lazy + sum(mid+1,r,L,R);
		return (R - L + 1LL) * tr[node].lazy + sum(l,mid,L,mid) + sum(mid+1,r,mid+1,R);
	}
}
void add(int l,int r,int L,int R,int d) {
	tr[node].sum += (R - L + 1) * d;
	if (l == L && r == R) {
		tr[node].lazy += d;
	}
	else {
		if (R <= mid) {
			add(l,mid,L,R,d);
		}
		else if (L >= mid + 1) {
			add(mid+1,r,L,R,d);
		}
		else {
			add(l,mid,L,mid,d);
			add(mid+1,r,mid+1,R,d);
		}
	}
}
int main() {
	int n,q;
	while (scanf("%d%d",&n,&q) == 2) {
		memset(tr,0,sizeof(tr));
		for (int i=1;i<=n;i++) scanf("%lld",&init[i]);
		build_tree(1,n);
		while (q --) {
			int cmd;
			scanf("%d",&cmd);
			if (cmd == 2) {
				int a,b;
				scanf("%d%d",&a,&b);
				printf("%lld\n",sum(1,n,a,b));
			}
			else {
				int a,b;
				long long c;
				scanf("%d%d%lld",&a,&b,&c);
				add(1,n,a,b,c);
			}
		}
	}
	return 0;
}

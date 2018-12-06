#include <bits/stdc++.h>
using namespace std;

#define node ((l+r)|(l!=r))
#define mid ((l + r) >> 1)
#define lson ((l+mid)|(l!=mid))
#define rson ((mid+1+r)|(mid+1!=r))

struct tree {
	long long sum;
	long long lazy;
}tr[200005];
long long a[100005];
void init(int l,int r) {
	if (l == r) {
		tr[node].sum = a[l];
		tr[node].lazy = 0;
	}
	else {
		init(l,mid);
		init(mid+1,r);
		tr[node].sum = tr[lson].sum + tr[rson].sum;
		tr[node].lazy = 0;
	}
}
void update(int l,int r,int rangeL,int rangeR,long long d) {
	//l和r是树的节点
	//rangeL和rangeR是要更新的范围
	tr[node].sum += (rangeR - rangeL + 1LL) * d;
	if (l == rangeL && r == rangeR) {
		tr[node].lazy += d;
	}
	else {
		if (rangeL <= mid) update(l,mid,rangeL,min(rangeR,mid),d);
		if (rangeR > mid) update(mid+1,r,max(rangeL,mid+1),rangeR,d);
	}
}
void push_down(int l,int r) {
	if (l != r) {
		tr[lson].lazy += tr[node].lazy;
		tr[rson].lazy += tr[node].lazy;
		tr[lson].sum += (mid-l+1LL) * tr[node].lazy;
		tr[rson].sum += (r-(mid+1)+1LL) * tr[node].lazy;
	}
	tr[node].lazy = 0;
}
long long query(int l,int r,int rangeL,int rangeR) {
	if (tr[node].lazy) push_down(l,r);
	if (l == rangeL && r == rangeR) return tr[node].sum;
	long long ret = 0;
	if (rangeL <= mid) ret += query(l,mid,rangeL,min(rangeR,mid));
	if (rangeR  > mid) ret += query(mid+1,r,max(rangeL,mid+1),rangeR);
	return ret;
}
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	init(1,n);
	for (int i=0;i<m;i++) {
		int o,x,y;
		scanf("%d%d%d",&o,&x,&y);
		if (o == 1) {
			long long k;
			scanf("%lld",&k);
			update(1,n,x,y,k);
		}
		else {
			printf("%lld\n",query(1,n,x,y));
		}
	}
	return 0;
}

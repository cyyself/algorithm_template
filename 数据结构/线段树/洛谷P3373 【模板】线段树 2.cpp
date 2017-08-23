#include <cstdio>
#include <algorithm>
using namespace std;
long long n,m,p;
long long a[100005];
struct node {
	long long sum;
	long long add,mul;//lazy-tag
	node *l,*r;
	node():sum(0),add(0),mul(1),l(NULL),r(NULL){};
}root;
inline void PushUp(node *n) {
	n->sum = (n->l->sum + n->r-> sum) % p;
}
void build_tree(node *n,int lv,int rv) {
	if (lv == rv) n->sum = a[lv] % p;//其实可以在这读入，不必使用row数组
	else {
		int mid = (lv + rv) >> 1;
		n->l = new node;
		n->r = new node;
		build_tree(n->l,lv,mid);
		build_tree(n->r,mid+1,rv);
		PushUp(n);
	}
}
inline void PushDown(node *n,int len) {
	n->l->add = ((n->l->add * n->mul)%p + n->add)%p;
	n->r->add = ((n->r->add * n->mul)%p + n->add)%p;
	n->l->mul = (n->l->mul * n->mul)%p;
	n->r->mul = (n->r->mul * n->mul)%p;
	n->l->sum = (n->l->sum * n->mul)%p + (n->add * (len - (len>>1)))%p;
	//很多人以为len的计算写错了，举个例子，当前节点为1...3，len=3，3/2=1，左节点长度为2，右节点长度为1，所以左节点长度为len-len/2
	n->r->sum = (n->r->sum * n->mul)%p + (n->add * (len>>1))%p;
	n->add = 0;
	n->mul = 1;
}
void update(node *n,int l,int r,int lv,int rv,long long k,int o) {
	if (l == lv && r == rv) {
		if (o == 1) {
			n->add = (n->add * k)%p;
			n->mul = (n->mul * k)%p;
			n->sum = (n->sum * k)%p;
		}
		else {
			n->add = (n->add + k)%p;
			n->sum = (n->sum + k*(r-l+1))%p;
		}
	}
	else {
		PushDown(n,rv-lv+1);//先把这个节点的懒人标记做到两个子节点上
		int mid = (lv + rv) >> 1;
		if (r<=mid) update(n->l,l,r,lv,mid,k,o);
		else if (l > mid) update(n->r,l,r,mid+1,rv,k,o);
		else {
			update(n->l,l,mid,lv,mid,k,o);
			update(n->r,mid+1,r,mid+1,rv,k,o);
		}
		PushUp(n);
	}
}
long long query(node *n,int l,int r,int lv,int rv) {
	if (l == lv && r == rv) return n->sum %p;
	else {
		PushDown(n,rv-lv+1);
		int mid = (lv + rv) >> 1;
		if (r <= mid) return query(n->l,l,r,lv,mid);
		if (l > mid) return query(n->r,l,r,mid+1,rv);
		return (query(n->l,l,mid,lv,mid) + query(n->r,mid+1,r,mid+1,rv))%p;
	}
}
int main() {
	scanf("%lld%lld%lld",&n,&m,&p);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	build_tree(&root,1,n);
	while(m--) {
		int o,x,y;
		scanf("%d%d%d",&o,&x,&y);
		if (o == 3) {
			printf("%lld\n",query(&root,x,y,1,n));
		}
		else {
			long long k;
			scanf("%lld",&k);
			k = k %p;
			update(&root,x,y,1,n,k,o);
		}
	}
	return 0;
}
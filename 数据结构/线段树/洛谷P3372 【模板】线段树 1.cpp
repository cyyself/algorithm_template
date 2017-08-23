#include <cstdio>
long long N,M;
struct node {
	node *l;
	node *r;
	long long lv;
	long long rv;
	long long sum;
	long long lan;//懒人标记，其下子节点加上的数
	node():l(NULL),r(NULL),lv(0),rv(0),sum(0),lan(0){}
}root;
void build_tree(node *n,long long l,long long r) {
	n->lv = l;
	n->rv = r;
	if (l == r) return;
	long long mid = (l + r) >> 1;
	n->l = new node;
	build_tree(n->l,l,mid);
	n->r = new node;
	build_tree(n->r,mid+1,r);
}
void update(node *n,long long l,long long r,long long v) {
	n->sum += v * (r-l+1);
	if (n->lv == n->rv) return;
	if (l == n->lv && r == n->rv) n->lan += v;
	else {
		long long mid = (n->lv + n->rv) >> 1;
		if (r < mid + 1) update(n->l,l,r,v);
		else if (l > mid) update(n->r,l,r,v);
		else {
			update(n->l,l,mid,v);
			update(n->r,mid+1,r,v);
		}
	}
}
long long query(node *n,long long l,long long r) {
	if (n->lv == l && n->rv == r) return n->sum;
	else {
		long long mid = (n->lv + n->rv) >> 1;
		if (r < mid + 1) return n->lan * (r-l+1) + query(n->l,l,r);
		else if (l > mid) return n->lan * (r-l+1) + query(n->r,l,r);
		else return n->lan * (r-l+1) + query(n->l,l,mid) + query(n->r,mid+1,r);
		
	}
}
//注意：一般线段树会有pushUp和pushDown，在插入时对打过懒人标记的点开始向下DFS把懒人标记处理上去，但是这里cyy没有使用这样的方法，因为这里只需要加法不需要乘法
int main() {
	int N,M;
	scanf("%d%d",&N,&M);
	build_tree(&root,1,N);
	for (int i=1;i<=N;i++) {
		long long x;
		scanf("%lld",&x);
		update(&root,i,i,x);
	}
	while (M--) {
		int o,x,y;
		scanf("%d%d%d",&o,&x,&y);
		if (o == 1) {
			long long k;
			scanf("%lld",&k);
			update(&root,x,y,k);
		}
		else {
			printf("%lld\n",query(&root,x,y));
		}
	}
	return 0;
}

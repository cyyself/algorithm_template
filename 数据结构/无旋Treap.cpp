#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
struct Treap {//无旋Treap
	int sz[maxn];
	int rd[maxn];
	int val[maxn];
	int son[maxn][2];
	int rt,nodecnt;
	void init() {
		for (int i=1;i<nodecnt;i++) {
			sz[i] = val[i] = son[i][0] = son[i][1] = 0;
		}
		rt = 0;
		nodecnt = 1;
	}
	void push_up(int node) {
		sz[node] = sz[son[node][0]] + sz[son[node][1]] + 1;
	}
	void split_val(int node,int x,int &l,int &r) {
		if (!node) l = r = 0;
		else {
			if (val[node] <= x) {
				l = node;
				split_val(son[node][1],x,son[node][1],r);
			}
			else {
				r = node;
				split_val(son[node][0],x,l,son[node][0]);
			}
			push_up(node);
		}
	}
	int merge(int x,int y) {//保证x<y
		if (!x || !y) return x + y;
		if (rd[x] < rd[y]) {
			son[x][1] = merge(son[x][1],y);
			push_up(x);
			return x;
		}
		else {
			son[y][0] = merge(x,son[y][0]);
			push_up(y);
			return y;
		}
	}
	void insert(int x) {
		int l,r;
		split_val(rt,x,l,r);
		rd[nodecnt] = rand();
		val[nodecnt] = x;
		sz[nodecnt] = 1;
		rt = merge(l,merge(nodecnt,r));
		nodecnt ++;
	}
	void del(int x) {
		int l,r,rr;
		split_val(rt,x,l,rr);
		split_val(l,x-1,l,r);
		rt = merge(merge(l,merge(son[r][0],son[r][1])),rr);
	}
	int rank_by_val(int x) {
		int l,r;
		split_val(rt,x-1,l,r);
		int res = sz[l] + 1;
		rt = merge(l,r);
		return res;
	}
	int val_by_rank(int x) {
		int node = rt;
		while (node) {
			if (x <= sz[son[node][0]]) {
				node = son[node][0];
			}
			else if (x == sz[son[node][0]] + 1) return val[node];
			else {
				x -= sz[son[node][0]] + 1;
				node = son[node][1];
			}
		}
		return -1;
	}
	int pre(int x) {
		int l,r;
		split_val(rt,x-1,l,r);
		int szl = sz[l];
		rt = merge(l,r);
		return val_by_rank(szl);
	}
	int suf(int x) {
		int l,r;
		split_val(rt,x,l,r);
		int szl = sz[l] + 1;
		rt = merge(l,r);
		return val_by_rank(szl);
	}
}tr;

int main() {
	tr.init();
	int q;
	scanf("%d",&q);
	while (q --) {
		int op,x;
		scanf("%d%d",&op,&x);
		switch (op) {
			case 1:
				tr.insert(x);
				break;
			case 2:
				tr.del(x);
				break;
			case 3:
				printf("%d\n",tr.rank_by_val(x));
				break;
			case 4:
				printf("%d\n",tr.val_by_rank(x));
				break;
			case 5:
				printf("%d\n",tr.pre(x));
				break;
			case 6:
				printf("%d\n",tr.suf(x));
				break;
		}
	}
	return 0;
}

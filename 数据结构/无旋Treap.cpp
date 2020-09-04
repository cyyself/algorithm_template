#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
struct Treap {//无旋Treap，注：按照权值和按照大小不能同时使用
	int sz[maxn];
	int rd[maxn];
	int val[maxn];
	int son[maxn][2];
	bool rev[maxn];
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
	void push_down(int node) {
		if (rev[node]) {
			swap(son[node][0],son[node][1]);
			rev[son[node][0]] ^= 1;
			rev[son[node][1]] ^= 1;
			rev[node] = 0;
		}
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
	void split_sz(int node,int x,int &l,int &r) {
		if (!node) l = r = 0;
		else {
			push_down(node);
			if (sz[son[node][0]] + 1 <= x) {
				l = node;
				split_sz(son[node][1],x-(sz[son[node][0]] + 1),son[node][1],r);
			}
			else {
				r = node;
				split_sz(son[node][0],x,l,son[node][0]);
			}
			push_up(node);
		}
	}
	int merge(int x,int y) {//保证x<y
		if (!x || !y) return x + y;
		if (rd[x] < rd[y]) {
			push_down(x);
			son[x][1] = merge(son[x][1],y);
			push_up(x);
			return x;
		}
		else {
			push_down(y);
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
		rev[nodecnt] = 0;
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
	void out(int node,vector<int> &buf) {
		if (!node) return;
		push_down(node);
		out(son[node][0],buf);
		buf.push_back(val[node]);
		out(son[node][1],buf);
	}
	void out(vector <int> &buf) {
		out(rt,buf);
	}
	void reverse(int l,int r) {
		int t1,t2,t3;
		split_sz(rt,l-1,t1,t2);
		split_sz(t2,r-l+1,t2,t3);
		rev[t2] ^= 1;
		rt = merge(t1,merge(t2,t3));
	}
}tr;
int main() {
	tr.init();
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) tr.insert(i);
	while (m --) {
		int l,r;
		scanf("%d%d",&l,&r);
		tr.reverse(l,r);
	}
	vector <int> ans;
	tr.out(ans);
	for (int i=0;i<ans.size();i++) printf("%d%c",ans[i],i==ans.size()-1?'\n':' ');
	return 0;
}

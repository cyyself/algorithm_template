//https://www.luogu.com.cn/problem/P3369
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int inf = 0x3f3f3f3f;
struct Treap {//有旋Treap
	int sz[maxn];//子树大小
	int rd[maxn];//随机权值
	int cnt[maxn];//这个节点值的数量
	int val[maxn];//节点的数值
	int son[maxn][2];
	int rt,nodecnt;
	void init() {
		for (int i=1;i<nodecnt;i++) {
			sz[i] = cnt[i] = val[i] = son[i][0] = son[i][1] = 0;
		}
		rt = 0;
		nodecnt = 1;
	}
	void pushup(int node) {
		sz[node] = sz[son[node][0]] + sz[son[node][1]] + cnt[node];
	}
	void rotate(int &node,int d) {
		int ch = son[node][d^1];
		son[node][d^1] = son[ch][d];
		son[ch][d] = node;
		pushup(node);
		pushup(ch);
		node = ch;
	}
	void insert(int x) {insert(rt,x);}
	void insert(int &node,int x) {
		if (!node) {
			node = nodecnt ++;
			sz[node] = cnt[node] = 1;
			val[node] = x;
			rd[node] = rand();
		}
		else if (val[node] == x) {
			cnt[node] ++;
			sz[node] ++;
		}
		else {
			int d = (x > val[node]);
			insert(son[node][d],x);
			if (rd[node] < rd[son[node][d]]) rotate(node,d^1);
			pushup(node);
		}
	}
	void del(int x) {del(rt,x);}
	void del(int &node,int x) {
		if (!node) return;
		if (x < val[node]) {
			del(son[node][0],x);
		}
		else if (x > val[node]) {
			del(son[node][1],x);
		}
		else {
			if (!son[node][0] && !son[node][1]) {
				cnt[node] --;
				sz[node] --;
				if (cnt[node] == 0) node = 0;
			}
			else if (son[node][0] && son[node][1]) {
				int d = (rd[son[node][0]] > rd[son[node][1]]);
				rotate(node,d);
				del(son[node][d],x);
			}
			else if (son[node][0]) {
				rotate(node,1);
				del(son[node][1],x);
			}
			else {
				rotate(node,0);
				del(son[node][0],x);
			}
		}
		pushup(node);
	}
	int getrankbyval(int x) {return getrankbyval(rt,x);}
	int getrankbyval(int node,int x) {
		if (!node) return 0;
		if (val[node] == x) return sz[son[node][0]] + 1;
		else if (val[node] < x) return sz[son[node][0]] + cnt[node] + getrankbyval(son[node][1],x);
		else return getrankbyval(son[node][0],x);
	}
	int getvalbyrank(int x) {return getvalbyrank(rt,x);}
	int getvalbyrank(int node,int x) {
		if (!node) return 0;
		if (sz[son[node][0]] >= x) return getvalbyrank(son[node][0],x);
		else if (sz[son[node][0]] + cnt[node] < x) 
			return getvalbyrank(son[node][1],x-sz[son[node][0]]-cnt[node]);
		else return val[node];
	}
	int pre(int x) {return pre(rt,x);}
	int pre(int node,int x) {
		if (!node) return -inf;
		if (val[node] >= x) return pre(son[node][0],x);
		else return max(val[node],pre(son[node][1],x));
	}
	int nxt(int x) {return nxt(rt,x);}
	int nxt(int node,int x) {
		if (!node) return inf;
		if (val[node] <= x) return nxt(son[node][1],x);
		else return min(val[node],nxt(son[node][0],x));
	}
} tr;
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
				printf("%d\n",tr.getrankbyval(x));
				break;
			case 4:
				printf("%d\n",tr.getvalbyrank(x));
				break;
			case 5:
				printf("%d\n",tr.pre(x));
				break;
			case 6:
				printf("%d\n",tr.nxt(x));
				break;
		}
	}
	return 0;
}

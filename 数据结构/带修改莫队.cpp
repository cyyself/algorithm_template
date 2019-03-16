//https://codeforces.com/contest/940/problem/F
#include <bits/stdc++.h>
using namespace std;
int bs;
struct query {
	int l,r,x,id;
	friend bool operator < (const query &u,const query &v) {
		if (u.l/bs != v.l/bs) return u.l/bs < v.l/bs;
		if (u.r/bs != v.r/bs) return u.r/bs < v.r/bs;
		return u.x < v.x;
	}
}Q[100000];
int qcnt;
struct modify {
	int pos,last,val;
}M[100000];
int mcnt;
int a[200005];
int last[200005];
int ans[200005];
int cnt[200005];
int scnt[200005];
bool exist[200005];
void update(int x) {
	if (exist[x]) {
		scnt[cnt[a[x]]] --;
		cnt[a[x]] --;
		scnt[cnt[a[x]]] ++;
	}
	else {
		scnt[cnt[a[x]]] --;
		cnt[a[x]] ++;
		scnt[cnt[a[x]]] ++;
	}
	exist[x] ^= 1;
}
void change(int mi) {
	int x = M[mi].pos;
	if (exist[x]) {
		update(x);
		a[x] = M[mi].val;
		update(x);
	}
	else a[x] = M[mi].val;
}
void restore(int mi) {
	int x = M[mi].pos;
	if (exist[x]) {
		update(x);
		a[x] = M[mi].last;
		update(x);
	}
	else a[x] = M[mi].last;
}
unordered_map <int,int> ls;
int lscnt;
int getls(int x) {
	if (ls.find(x) == ls.end()) ls[x] = ++lscnt;
	return ls[x];
}
int main() {
	int n,q;
	scanf("%d%d",&n,&q);
	bs = pow(n,2.0/3.0);
	for (int i=1;i<=n;i++) {
		int x;
		scanf("%d",&x);
		a[i] = getls(x);
		last[i] = a[i];
	}
	while (q --) {
		int t,l,r;
		scanf("%d%d%d",&t,&l,&r);
		if (t == 1) {
			Q[qcnt] = (query){l,r,mcnt-1,qcnt};
			qcnt ++;
		}
		else {
			r = getls(r);
			M[mcnt++] = (modify){l,last[l],r};
			last[l] = r;
		}
	}
	sort(Q,Q+qcnt);
	int l=1,r=0;
	int mi=-1;
	for (int i=0;i<qcnt;i++) {
		while (mi < Q[i].x) change(++mi);
		while (mi > Q[i].x) restore(mi--);
		while (r < Q[i].r) update(++r);
		while (r > Q[i].r) update(r--);
		while (l < Q[i].l) update(l++);
		while (l > Q[i].l) update(--l);
		int cur = 1;
		while (scnt[cur] > 0) cur ++;
		ans[Q[i].id] = cur;
	}
	for (int i=0;i<qcnt;i++) printf("%d\n",ans[i]);
	return 0;
}

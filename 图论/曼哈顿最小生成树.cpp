//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1663
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int n;
struct Pos {
	int x,y,id;
	friend bool operator < (const Pos &a,const Pos &b) {
		if (a.x == b.x) return a.y < b.y;
		return a.x < b.x;
	}
}p[100000];
struct Edge {
	int u,v,w;
	friend bool operator < (const Edge &a,const Edge &b) {
		return a.w < b.w;
	}
}e[400000];
int ecnt;
struct DATA {
	int w;
	int id;
}tr[100001];
inline int lowbit(int x) {
	return x & (-x);
}
void find_vertice(int u,int pos,int w) {
	DATA cur;
	cur.w = INF;
	for (int i=pos;i<=n;i+=lowbit(i)) if (tr[i].w < cur.w) cur = tr[i];
	if (cur.w != INF) e[ecnt++] = (Edge){u,cur.id,cur.w-w};
}
void insert_vertice(int u,int pos,int w) {
	for (int i=pos;i>=1;i-=lowbit(i)) if (w < tr[i].w) {
		tr[i].w = w;
		tr[i].id = u;
	}
}
int d[100000];
int lsd[100000];
void build_graph() {
	memset(tr,0x3f,sizeof(tr));
	sort(p,p+n);
  //离散化
	for (int i=0;i<n;i++) lsd[i] = d[i] = p[i].y - p[i].x;
	sort(d,d+n);
	for (int i=0;i<n;i++) lsd[i] = 1 + lower_bound(d,d+n,lsd[i]) - d;
	for (int i=n-1;i>=0;i--) {
		int pos = lsd[i];
		int w = p[i].x + p[i].y;
		find_vertice(p[i].id,pos,w);
		insert_vertice(p[i].id,pos,w);
	}
}
int f[100000];
int find(int x) {
	if (f[x] != x) f[x] = find(f[x]);
	return f[x];
}
void uni(int u,int v) {
	f[find(u)] = find(v);
}
long long kruskal() {
	sort(e,e+ecnt);
	int cnt = 0;
	long long sum = 0;
	for (int i=0;i<ecnt;i++) {
		if (find(e[i].u) == find(e[i].v)) continue;
		uni(e[i].u,e[i].v);
		sum += e[i].w;
		if (++cnt == n - 1) return sum;
	}
	return -1;
}
int main() {
	int cas = 0;
	while (scanf("%d",&n) == 1 && n) {
		ecnt = 0;
		for (int i=0;i<n;i++) f[i] = i;
		for (int i=0;i<n;i++) {
			scanf("%d%d",&p[i].x,&p[i].y);
			p[i].id = i;
		}
		build_graph();
		for (int i=0;i<n;i++) swap(p[i].x,p[i].y);
		build_graph();
		for (int i=0;i<n;i++) p[i].y = -p[i].y;
		build_graph();
		for (int i=0;i<n;i++) swap(p[i].x,p[i].y);
		build_graph();
		printf("Case %d: Total Weight = %lld\n",++cas,kruskal());
	}
	return 0;
}

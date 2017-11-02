//TLE:https://www.luogu.org/problemnew/show/P3379
#include <bits/stdc++.h>
int n,m,s;
int f[500005];
int ehead[500005];
int qhead[500005];
struct Edge {
	int v;
	int next;
}e[500005];
int ecnt = 0;
struct Query {
	int v;
	int next;
}q[500005];
int qcnt = 0;
inline void AddEdge(int u,int v) {
	e[ecnt].v = v;
	e[ecnt].next = ehead[u];
	ehead[u] = ecnt;
	ecnt ++;
}
inline void AddQuery(int u,int v) {
	q[qcnt].v = v;
	q[qcnt].next = qhead[u];
	qhead[u] = qcnt;
	qcnt ++;
}
inline int find(int x) {
	if (f[x] != x) f[x] = find(f[x]);
	return f[x];
}
inline void uni(int u,int v) {
	f[find(u)] = find(v);
}
int ans[500005];
bool vis[500005];
void tarjan(int node) {
	vis[node] = true;
	for (int i=ehead[node];i != -1;i=e[i].next) {
		if (!vis[e[i].v]) {
			tarjan(e[i].v);
			uni(e[i].v,node);
		}
	}
	for (int i=qhead[node];i != -1;i=q[i].next) {
		if (vis[q[i].v]) ans[i/2] = find(q[i].v);
	}
}
int main() {
	memset(ehead,-1,sizeof(ehead));
	memset(qhead,-1,sizeof(qhead));
	scanf("%d%d%d",&n,&m,&s);
	for (int i=1;i<=n;i++) f[i] = i;
	for (int i=1;i<n;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		AddEdge(u,v);
		AddEdge(v,u);
	}
	for (int i=0;i<m;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		AddQuery(u,v);
		AddQuery(v,u);
	}
	tarjan(s);
	for (int i=0;i<m;i++) printf("%d\n",ans[i]);
	return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+15;
const int maxm = 1e6+15;
int w[maxn];
int head[maxn];
struct Edge{
	int u,v;
	int next;
}e[maxm];
int ecnt = 0;
inline void AddEdge(int u,int v) {
	e[ecnt].u = u;
	e[ecnt].v = v;
	e[ecnt].next = head[u];
	head[u] = ecnt;
	ecnt ++;
}
int rt[maxn];//root
int nw[maxn];//缩点后的新权值
int dfn[maxn];
int low[maxn];
int tjtime;//tarjan time
stack <int> s;
bool ins[maxn];
int subg = 0;//子图数量
void tarjan(int u) {
	dfn[u] = ++tjtime;
	low[u] = tjtime;
	s.push(u);
	ins[u] = true;
	for (int i=head[u];i != -1;i=e[i].next) {
		int v = e[i].v;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}
		else if (ins[v]) low[u] = min(low[u],dfn[v]);
	}
	if (low[u] == dfn[u]) {//一个强连通分量
		subg ++;
		while (!s.empty()) {
			int cur = s.top();
			s.pop();
			ins[cur] = false;
			rt[cur] = subg;
			nw[subg] += w[cur];
			if (cur == u) break;
		}
	}
}
int dis[maxn];
bool inq[maxn];
queue <int> q;
int spfa(int u) {
	memset(dis,0,sizeof(dis));
	memset(inq,0,sizeof(inq));
	q.push(u);
	inq[u] = true;
	dis[u] = nw[u];
	int maxdis = nw[u];
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		inq[cur] = false;
		for (int i=head[cur];i != -1;i=e[i].next) {
			int v = e[i].v;
			if (dis[v] < dis[cur] + nw[v]) {
				dis[v] = dis[cur] + nw[v];
				maxdis = max(maxdis,dis[v]);
				if (!inq[v]) {
					q.push(v);
					inq[v] = true;
				}
			}
		}
	}
	return maxdis;
}
int mx[maxm],my[maxm];
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	memset(head,-1,sizeof(head));
	for (int i=1;i<=n;i++) scanf("%d",&w[i]);
	for (int i=1;i<=m;i++) {
		scanf("%d%d",&mx[i],&my[i]);
		AddEdge(mx[i],my[i]);
	}
	for (int i=1;i<=n;i++) if (!rt[i]) tarjan(i);
	memset(head,-1,sizeof(head));
	ecnt = 0;
	for (int i=1;i<=m;i++) {
		int x = rt[mx[i]];
		int y = rt[my[i]];
		if (x != y) AddEdge(x,y);
	}
	int ans = 0;
	for (int i=1;i<=subg;i++) ans = max(ans,spfa(i));
	printf("%d\n",ans);
	return 0;
}

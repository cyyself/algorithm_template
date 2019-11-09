//POJ 2186，奶牛的仰慕具有传递性，给m个仰慕关系，问多少奶牛被所有的奶牛仰慕
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;
const int maxn = 10005;
const int maxe = 50005;
int dfn[maxn],low[maxn],rt[maxn],sz[maxn],ts,scc;
bool vis[maxn];
stack <int> s;
int head[maxn];
struct Edge {
	int v,next;
}e[maxe];
int ecnt;
void addedge(int u,int v) {
	e[ecnt].v = v;
	e[ecnt].next = head[u];
	head[u] = ecnt;
	ecnt ++;
}
void tarjan(int u) {
	dfn[u] = low[u] = ++ts;
	vis[u] = true;
	s.push(u);
	for (int i=head[u];~i;i=e[i].next) {
		int v = e[i].v;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}
		else if (vis[v]) low[u] = min(low[u],dfn[v]);
	}
	if (dfn[u] == low[u]) {
		scc ++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();
			rt[v] = scc;
			sz[scc] ++;
			vis[v] = false;
			if (v == u) break;
		}
	}
}
int outdeg[maxn];
int main() {
	int n,m;
	while (scanf("%d%d",&n,&m) == 2) {
		memset(head,-1,sizeof(head));
		ecnt = 0;
		ts = 0;
		scc = 0;
		for (int i=1;i<=n;i++) dfn[i] = low[i] = rt[i] = sz[i] = 0;
		for (int i=0;i<m;i++) {
			int u,v;
			scanf("%d%d",&u,&v);
			addedge(u,v);
		}
		for (int i=1;i<=n;i++) if (!dfn[i]) tarjan(i);
		for (int i=1;i<=scc;i++) outdeg[i] = 0;
		for (int u=1;u<=n;u++) {
			int uu = rt[u];
			for (int i=head[u];~i;i=e[i].next) {
				int v = e[i].v;
				int vv = rt[v];
				if (uu != vv) outdeg[uu] ++;
			}
		}
		int ans = -1;
		for (int i=1;i<=scc;i++) if (outdeg[i] == 0) {
			if (ans == -1) ans = i;
			else ans = 0;
		}
		if (ans > 0) printf("%d\n",sz[ans]);
		else printf("0\n");
	}
	return 0;
}

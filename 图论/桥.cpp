//http://poj.org/problem?id=3177
//给一张无向图，问需要加多少条边，使得图没有桥
//求边双，然后统计度数为1的节点个数，每次选两个点连起来，就是答案
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10005;
const int maxm = 20005;
struct DATA {
	int v,next;
}e[20005];
int ecnt;
int head[maxn];
void addedge(int u,int v) {
	e[ecnt].v = v;
	e[ecnt].next = head[u];
	head[u] = ecnt;
	ecnt ++;
}
int dfn[maxn],low[maxn];
int ts;
bool br[maxm];
void tarjan(int u,int r) {
	dfn[u] = low[u] = ++ts;
	for (int i=head[u];~i;i=e[i].next) {
		int v = e[i].v;
		if (v == r) continue;
		if (!dfn[v]) {
			tarjan(v,u);
			if (low[v] > dfn[u]) {
				br[ i ] = true;
				br[i^1] = true;
			}
			low[u] = min(low[u],low[v]);
		}
		else low[u] = min(low[u],dfn[v]);
	}
}
int rt[maxn],subg;
int deg[maxn];
void dfs(int u) {
	rt[u] = subg;
	for (int i=head[u];~i;i=e[i].next) {
		if (br[i]) continue;
		int v = e[i].v;
		if (!rt[v]) dfs(v);
	}
}
int main() {
	memset(head,-1,sizeof(head));
	int f,r;
	scanf("%d%d",&f,&r);
	for (int i=0;i<r;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	for (int i=1;i<=f;i++) if (!dfn[i]) tarjan(i,i);
	for (int i=1;i<=f;i++) if (!rt[i]) {
		subg ++;
		dfs(i);
	}
	for (int u=1;u<=f;u++) {
		for (int i=head[u];~i;i=e[i].next) {
			int v = e[i].v;
			if (rt[u] != rt[v]) {
				deg[rt[u]] ++;
				deg[rt[v]] ++;
			}
		}
	}
	int cnt = 0;
	for (int i=1;i<=subg;i++) if (deg[i] == 2) cnt ++;
	printf("%d\n",(cnt+1)/2);
	return 0;
}

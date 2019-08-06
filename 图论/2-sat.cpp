#include <bits/stdc++.h>
using namespace std;
vector <int> g[2000005];
bool vis[2000005];
int dfn[2000005],low[2000005],root[2000005];
int rootcnt;
int timestamp;
stack <int> s;
void tarjan(int u) {
	dfn[u] = low[u] = ++timestamp;
	vis[u] = true;
	s.push(u);
	for (auto v:g[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}
		else {
			if (vis[v]) low[u] = min(low[u],dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		rootcnt ++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();
			root[v] = rootcnt;
			vis[v] = false;
			if (v == u) break;
		}
	}
}
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	while (m --) {
		int i,a,j,b;
		scanf("%d%d%d%d",&i,&a,&j,&b);
		g[i+n*(a&1)].push_back(j+n*(b^1));
		g[j+n*(b&1)].push_back(i+n*(a^1));
	}
	for (int i=1;i<=2*n;i++) if (!dfn[i]) tarjan(i);
	bool ans = true;
	for (int i=1;i<=n && ans;i++) if (root[i] == root[i+n]) ans = false;
	if (ans) {
		printf("POSSIBLE\n");
		for (int i=1;i<=n;i++) printf("%d ",root[i]<root[i+n]);
		printf("\n");
	}
	else printf("IMPOSSIBLE\n");
	return 0;
}
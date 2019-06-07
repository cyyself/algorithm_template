//给一张无向图，求图中的割边数量
#include <bits/stdc++.h>
using namespace std;
int dfn[10005];
int low[10005];
vector <int> g[10005];
map <pair<int,int>,int> cnt;
int ans;
int n,m;
int ts;
void tarjan(int u,int r) {
	dfn[u] = low[u] = ++ts;
	for (auto v:g[u]) {
		if (v == r) continue;
		if (!dfn[v]) {
			tarjan(v,u);
			if (low[v] > dfn[u] && cnt[make_pair(u,v)] == 1) ans ++;
			low[u] = min(low[u],low[v]);
		}
		else low[u] = min(low[u],dfn[v]);
	}
}
int main() {
	int T;
	scanf("%d",&T);
	for (int cas=1;cas<=T;cas++) {
		ans = 0;
		ts = 0;
		cnt.clear();
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) {
			dfn[i] = low[i] = 0;
			g[i].clear();
		}
		for (int i=0;i<m;i++) {
			int u,v;
			scanf("%d%d",&u,&v);
			g[u].push_back(v);
			g[v].push_back(u);
			cnt[make_pair(u,v)] ++;
			cnt[make_pair(v,u)] ++;
		}
		for (int i=1;i<=n;i++) if (!dfn[i]) tarjan(i,i);
		printf("Case %d: %d\n",cas,ans);
	}
	return 0;
}

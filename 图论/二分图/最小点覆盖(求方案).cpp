#include <bits/stdc++.h>
using namespace std;
vector <int> g[1005];
int pre[1005],nxt[1005];
bool visl[1005],visr[1005];
bool dfs(int u) {
	visl[u] = true;
	for (auto v:g[u]) {
		if (visr[v]) continue;
		visr[v] = true;
		if (pre[v] == -1 || dfs(pre[v])) {
			pre[v] = u;
			nxt[u] = v;
			return true;
		}
	}
	return false;
}
int r,c,n;
void work() {
	int match = 0;
	memset(pre,-1,sizeof(pre));
	memset(nxt,-1,sizeof(nxt));
	memset(visl,false,sizeof(visl));
	for (int i=1;i<=r;i++) {
		if (!g[i].size()) continue;
		memset(visr,0,sizeof(visr));
		match += dfs(i);
	}
	memset(visl,false,sizeof(visl));
	memset(visr,false,sizeof(visr));
	for (int i=1;i<=r;i++) if (nxt[i] == -1) dfs(i);
	printf("%d",match);
	for (int i=1;i<=r;i++) if (!visl[i]) printf(" r%d",i);
	for (int i=1;i<=c;i++) if (visr[i]) printf(" c%d",i);
	printf("\n");
}
int main() {
	while (scanf("%d%d%d",&r,&c,&n) == 3 && n) {
		for (int i=1;i<=r;i++) g[i].clear();
		for (int i=0;i<n;i++) {
			int x,y;
			scanf("%d%d",&x,&y);
			g[x].push_back(y);
		}
		work();
	}
	return 0;
}

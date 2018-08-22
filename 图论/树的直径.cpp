//http://codeforces.com/contest/690/problem/C2
//取任意一点开始DFS找到最远的点u，再从这个点u开始DFS找到最远的点v，dis(u,v)即为树的直径
#include <bits/stdc++.h>
using namespace std;
vector <int> g[100005];
bool vis[100005];
int dis[100005];
int n;
void getdis(int u) {
	vis[u] = true;
	for (auto v:g[u]) {
		if (!vis[v]) {
			dis[v] = dis[u] + 1;
			getdis(v);
		}
	}
}
int main() {
	int m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	memset(vis,false,sizeof(vis));
	getdis(1);
	int root = 0;
	for (int i=1;i<=n;i++) if (dis[i] > dis[root]) root = i;
	memset(dis,0,sizeof(dis));
	memset(vis,false,sizeof(vis));
	getdis(root);
	int ans = 0;
	for (int i=1;i<=n;i++) ans = max(ans,dis[i]);
	printf("%d\n",ans);
	return 0;
}

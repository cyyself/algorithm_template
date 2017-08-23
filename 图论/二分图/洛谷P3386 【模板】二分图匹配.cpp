//匈牙利算法，寻找增广路
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int n,m;
vector <int> g[1005];
bool vis[1005];
int pre[1005];
bool zg(int p) {
	for(vector<int>::iterator iter=g[p].begin();iter!=g[p].end();iter++) {
		int i = *iter;
		if (!vis[i]) {
			vis[i] = true;
			if (pre[i] == 0 || zg(pre[i])) {
				pre[i] = p;
				return true;
			}
		}
	}
	return false;
}
int main() {
	int e;
	scanf("%d%d%d",&n,&m,&e);
	for (int i=0;i<e;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		if (u >= 1 && m >= 1 && u <= n && v <= m) g[u].push_back(v);
	}
	int ans = 0;
	for (int i=1;i<=n;i++) {
		memset(vis,0,sizeof(vis));
		if (zg(i)) ans ++;
	}
	printf("%d\n",ans);
	return 0;
}

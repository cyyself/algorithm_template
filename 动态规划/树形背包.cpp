//Luogu P2014：给出每个物品的价值和所属关系（如果父节点为0则没有所属关系，若不为0则存在父节点），求选M个物品能获得的最大权值
#include <bits/stdc++.h>
using namespace std;
int f[305][305];
int n,m;
vector <int> g[305];
int s[305];
void dfs(int u) {
	for (auto v:g[u]) {
		for (int i=0;i<=m-1;i++) f[v][i] = f[u][i] + s[v];
		dfs(v);
		for (int i=m;i>=1;i--) f[u][i] = max(f[u][i],f[v][i-1]);
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		int ki;
		scanf("%d%d",&ki,&s[i]);
		g[ki].push_back(i);
	}
	dfs(0);
	printf("%d\n",f[0][m]);
	return 0;
}

//http://noalgo.info/496.html
/*
图样例：
8
0 1 1
1 4 1
1 5 1
5 7 1
0 2 1
0 3 1
3 6 1
*/
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
struct Edge{
	int v;
	int w;
};
int n;
vector <Edge> g[100005];
bool vis[100005];
int depth[200005];
int node[200005];
int first[100005];
int t = 0;
int st[100005][20];
void init_RMQ(int maxn){
	for (int i=0;i<maxn;i++) st[i][0] = i;
	for (int j=1;pow(2,j)<=maxn;j++) {
		for (int i=0;i+pow(2,j)-1<maxn;i++) {
			int l = st[i][j-1];
			int r = st[i+int(pow(2,j-1))][j-1];
			st[i][j] = depth[l] < depth[r] ? l : r;
		}
	}
}
inline int RMQ(int u,int v) {//返回位置
	if (u > v) swap(u,v);
	int k = log(v-u+1) / log(2);
	int l = st[u][k];
	int r = st[v-int(pow(2,k))+1][k];
	return depth[l] < depth[r] ? l : r;
}
inline int LCA(int u,int v) {
	return node[RMQ(first[u],first[v])];
}
void DFS(int n,int d) {
	node[t] = n;
	depth[t] = d;
	first[n] = t;
	t++;
	vis[n] = true;
	for (int i=0;i<g[n].size();i++) {
		Edge curr = g[n][i];
		if (!vis[curr.v]) {
			DFS(curr.v,d+1);
			node[t] = n;
			depth[t] = d;
			t++;
		}
	}
}
int main() {
	scanf("%d",&n);//n个节点
	for (int i=1;i<n;i++) {//n-1条边
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		g[u].push_back((Edge){v,w});
		g[v].push_back((Edge){u,w});
	}
	DFS(0,0);//以0节点作为根节点
	printf("----depth & node----\n");
	for (int i=0;i<t;i++) printf("%d %d\n",depth[i],node[i]);
	printf("----First----\n");
	for (int i=0;i<n;i++) printf("%d ",first[i]);
	printf("\n");
	printf("----可在下面查询LCA----\n");
	init_RMQ(t);
	while(true) {
		int u,v;
		scanf("%d%d",&u,&v);
		printf("LCA:%d\n",LCA(u,v));
	}
	return 0;
}

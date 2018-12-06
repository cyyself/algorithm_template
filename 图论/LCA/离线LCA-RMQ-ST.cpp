//2136ms:https://www.luogu.org/problemnew/show/P3379
#include <bits/stdc++.h>
using namespace std;
//邻接表{
//这里采用的是传统的邻接表写法，而非变长数组模拟邻接表
int pre[1000005];//previous,pre[n]代表n节点下的第一条边，也是最后一个插入的边
int nextn[1000005];//nextn[e]代表与e边指向的节点n的上级节点所连的节点中与n相邻的下一条边
int v[1000005];//v[e]代表编号为e的边的指向的节点
int en = 0;//Edge number
inline void AddEdge(int _u,int _v) {
	v[en] = _v;
	nextn[en] = pre[_u];
	pre[_u] = en;
	en++;
}
//}
int n,m,s;
bool vis[1000005];
int depth[1000005];
int node[1000005];
int first[1000005];
int t = 0;
int st[1000005][20];
inline int pow2(int n) {
	return 1 << n;
}
void init_RMQ(int maxn){
	for (int i=0;i<=maxn;i++) st[i][0] = i;
	for (int j=1;pow2(j)<=maxn;j++) {
		for (int i=0;i+pow2(j)-1<maxn;i++) {
			int l = st[i][j-1];
			int r = st[i+int(pow2(j-1))][j-1];
			st[i][j] = depth[l] < depth[r] ? l : r;
		}
	}
}
inline int RMQ(int u,int v) {//返回位置
	if (u > v) swap(u,v);
	int k = log(v-u+1) / log(2);
	int l = st[u][k];
	int r = st[v-int(pow2(k))+1][k];
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
	for (int e=pre[n];e!=-1;e=nextn[e]) {
		if (!vis[v[e]]) {
			DFS(v[e],d+1);
			node[t] = n;
			depth[t] = d;
			t++;
		}
	}
}
int main() {
	scanf("%d%d%d",&n,&m,&s);//n个节点
	memset(nextn,-1,sizeof(nextn));
	memset(pre,-1,sizeof(pre));
	for (int i=1;i<n;i++) {//n-1条边
		int u,v;
		scanf("%d%d",&u,&v);
		AddEdge(u,v);
		AddEdge(v,u);
	}
	DFS(s,0);//以s节点作为根节点
	init_RMQ(t);
	while(m--) {
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%d\n",LCA(u,v));
	}
	return 0;
}

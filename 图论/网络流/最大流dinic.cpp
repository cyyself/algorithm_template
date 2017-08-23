//洛谷P3376
#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x7f7f7f7f
using namespace std;
struct Edge{
	int f,v,next;
}e[200005];
int ecnt = 0;//因为采用了一个邻接表奇偶存两条边的方法，所以必须从偶数开始
int head[10005];
void AddEdge(int u,int v,int c) {
	e[ecnt].v = v;
	e[ecnt].f = c;
	e[ecnt].next = head[u];
	head[u] = ecnt;
	ecnt ++;
}
int n,m,s,t;
int dis[10005];

bool bfs() {//划分层次，同时判断是否可到达
	memset(dis,0x7f,sizeof(dis));
	dis[s] = 1;
	queue <int> q;
	q.push(s);
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int en=head[cur];en!=-1;en = e[en].next) {
			int v = e[en].v;
			if (e[en].f != 0 && dis[v] == INF) {
				dis[v] = dis[cur] + 1;
				q.push(v);
			}
		}
	}
	return dis[t] != INF;
}

int dfs(int u,int curflow) {//curflow=>当前可增广的最大流量
	if (u == t) return curflow;
	if (dis[u] >= dis[t]) return 0;
	for (int en=head[u];en!=-1;en=e[en].next) {
		int v = e[en].v;
		int flow;
		if (e[en].f != 0 && dis[v] == dis[u] + 1 && (flow = dfs(v,min(curflow,e[en].f)))) {
			e[en].f -= flow;
			e[en ^ 1].f += flow;//偶数+1,奇数-1，很巧妙的位运算
			return flow;
		}
	}
	return 0;
}
int dinic() {
	int ans = 0;
	int flow;
	while(bfs()) while(flow = dfs(s,INF)) ans += flow;
	return ans;
}
int main() {
	scanf("%d%d%d%d",&n,&m,&s,&t);
	memset(head,-1,sizeof(head));
	for (int i=0;i<m;i++) {
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		AddEdge(u,v,c);
		AddEdge(v,u,0);
		//一个邻接表双向存储
	}
	printf("%d\n",dinic());
	return 0;
}
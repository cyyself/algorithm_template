#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
struct Edge{
	int u;
	int v;
	int f;
	int c;
	int next;
}e[100005];
int head[5005];
int pre[5005];
int n,m,s,t;
int ecnt;
inline void AddEdge(int _u,int _v,int _f,int _c) {
	e[ecnt].next = head[_u];
	head[_u] = ecnt;
	e[ecnt].u = _u;
	e[ecnt].v = _v;
	e[ecnt].f = _f;
	e[ecnt].c = _c;
	ecnt++;
}
inline void Add(int _u,int _v,int _f,int _c) {
	AddEdge(_u,_v,_f,_c);
	AddEdge(_v,_u,0,-_c);
}
int dis[5005];
bool inq[5005];
bool SPFA(int s,int t) {
	queue <int> q;
	q.push(s);
	memset(dis,0x3f,sizeof(dis));
	memset(inq,0,sizeof(inq));
	memset(pre,-1,sizeof(pre));
	inq[s] = true;
	dis[s] = 0;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		inq[cur] = false;
		for (int i = head[cur];i != -1;i = e[i].next) {
			if (e[i].f > 0 && dis[e[i].v] > dis[cur] + e[i].c) {
				dis[e[i].v] = dis[cur] + e[i].c;
				pre[e[i].v] = i;
				if (!inq[e[i].v]) {
					inq[e[i].v] = true;
					q.push(e[i].v);
				}
			}
		}
	}
	return dis[t] != INF;
}
void MICMAF(int s,int t,int &flow,int &cost) {
	flow = 0;
	cost = 0;
	while (SPFA(s,t)) {
		int minF = INF;
		for (int i=pre[t];i != -1;i=pre[e[i].u]) {
			minF = min(minF,e[i].f);
			if (ans[flow].size() == 0 || e[i].v != ans[flow][ans[flow].size()-1]-1) ans[flow].push_back(e[i].v);
		}
		flow += minF;
		for (int i=pre[t];i != -1;i=pre[e[i].u]) {
			e[i].f -= minF;
			e[i^1].f += minF;
		}
		cost += dis[t] * minF;
	}
}
vector <int> path[2];
void dfs(int u,int p) {
	for (int i=head[u];~i;i=e[i].next) {
		if ( (i & 1) == 0 && e[i].f == 0) {
			if (e[i].v == (u ^ 1) ) path[p].push_back(e[i].u/2);
			dfs(e[i].v,p);
		}
	}
}
int main() {
	scanf("%d%d%d%d",&n,&m,&s,&t);
	memset(head,-1,sizeof(head));
	for (int i=0;i<m;i++) {
		int _u,_v,_f,_c;
		scanf("%d%d%d%d",&_u,&_v,&_f,&_c);
		Add(_u,_v,_f,_c);
	}
	int f,c;
	MICMAF(f,c);
	printf("%d %d\n",f,c);
	return 0;
}

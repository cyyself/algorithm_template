#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x7f7f7f7f
using namespace std;

struct Edge{
	int u;//大多数算法在邻接表中并不需要这个，但费用流比较例外
	int v;
	int f;//残量 
	int c;//费用 
	int next;
}e[100005];
int head[5005];
int pre[5005];
int n,m,s,t;
int ecnt = 0;
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
bool SPFA() {
	queue <int> q;
	q.push(s);
	memset(dis,0x7f,sizeof(dis));
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
			    //网上很多模板都是写e[i].f相当于e[i].f != 0，如果你真的理解网络流的话你会发现这样虽然也能跑出正确结果但是会增加时间复杂度，一个点要重复入队列两次走同样的路
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

void MICMAF(int &flow,int &cost) {
	flow = 0;
	cost = 0;
	while (SPFA()) {
		int minF = INF;
		for (int i=pre[t];i != -1;i=pre[e[i].u]) minF = min(minF,e[i].f);
		flow += minF;
		for (int i=pre[t];i != -1;i=pre[e[i].u]) {
			e[i].f -= minF;
			e[i^1].f += minF;
		}
		cost += dis[t] * minF;
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
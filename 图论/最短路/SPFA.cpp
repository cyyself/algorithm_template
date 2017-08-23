#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define UINF 0xffffffff
struct Edge {
	int to;
	int w;
	Edge(int _to,int _w):to(_to),w(_w){}
};
vector <Edge> g[10005];//数组模拟邻接表
unsigned int dis[10005];
bool inqueue[10005];
int main() {
	int N,M,S;
	scanf("%d%d%d",&N,&M,&S);
	for (int i=0;i<M;i++) {
		int Fi,Gi,Wi;
		scanf("%d%d%d",&Fi,&Gi,&Wi);
		g[Fi].push_back(Edge(Gi,Wi));
	}
	memset(dis,0xff,sizeof(dis));
	dis[S] = 0;
	queue <int> q;
	q.push(S);
	while(!q.empty()) {
		int curr = q.front();
		q.pop();
		inqueue[curr] = false;
		for (int i=0;i<g[curr].size();i++) {
			if (dis[curr] + g[curr][i].w < dis[g[curr][i].to]) {
				dis[g[curr][i].to] = dis[curr] + g[curr][i].w;
				if (!inqueue[g[curr][i].to]){
					q.push(g[curr][i].to);
					inqueue[g[curr][i].to] = true;
				}
			}
		}
	}
	for (int i=1;i<=N;i++) {
		if (dis[i] == UINF) printf("2147483647 ");
		else printf("%u ",dis[i]);
	}
	return 0;
}
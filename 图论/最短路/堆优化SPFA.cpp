//Luogu P4779:https://www.luogu.org/problemnew/show/P4779
#include <bits/stdc++.h>
using namespace std;
struct p {
	int u;
	int dis;
	friend bool operator < (const p &a,const p &b) {
		return a.dis > b.dis;
	}
	p(int _u,int _dis) {
		u = _u;
		dis = _dis;
	}
};
struct edge {
	int v,w;
	int next;
}e[200005];
int head[100005];
int ecnt;
void AddEdge(int u,int v,int w) {
	e[ecnt].v = v;
	e[ecnt].w = w;
	e[ecnt].next = head[u];
	head[u] = ecnt;
	ecnt ++;
}
int read() {
	int ret = 0;
	int f = 1;
	char c = getchar();
	while (!(c >= '0' && c <= '9')) {
		if (c == '-') f = -f;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		ret *= 10;
		ret += c - '0';
		c = getchar();
	}
	return ret * f;
}
int dis[100005];
void spfa(int s) {
	memset(dis,0x3f,sizeof(dis));
	dis[s] = 0;
	priority_queue <p> q;
	q.push(p(s,0));
	while (!q.empty()) {
		p cur = q.top();
		q.pop();
		int u = cur.u;
		if (cur.dis > dis[u]) continue;
		for (int i=head[u];i != -1;i=e[i].next) {
			int v = e[i].v;
			int w = e[i].w;
			if (dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				q.push(p(v,dis[v]));
			}
		}
	}
}
int main() {
	memset(head,-1,sizeof(head));
	ecnt = 0;
	int n,m,s;
	scanf("%d%d%d",&n,&m,&s);
	while (m--) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		AddEdge(u,v,w);
	}
	spfa(s);
	for (int i=1;i<=n;i++) {
		if (i != 1) printf(" ");
		printf("%d",dis[i]);
	}
	printf("\n");
	return 0;
}

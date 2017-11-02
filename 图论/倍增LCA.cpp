//AC 1404ms https://www.luogu.org/problemnew/show/P3379
#include <bits/stdc++.h>
using namespace std;
int head[500005];
struct Edge {
	int v;
	int next;
}e[1000005];
int ecnt = 0;
int n,m,s;
inline void AddEdge(int u,int v) {
	e[ecnt].v = v;
	e[ecnt].next = head[u];
	head[u] = ecnt;
	ecnt ++;
}
inline int read() {
	int f = 1;
	int ret = 0;
	char c = getchar();
	while (!(c >= '0' && c <= '9'))	{
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
int vis[500005];
int up[500005][25];
int dep[500005];
void dfs(int u) {
	vis[u] = true;
	for (int i=1,len=1;len<=dep[u];i++,len <<= 1) up[u][i] = up[up[u][i-1]][i-1];
	for (int i=head[u];i != -1;i = e[i].next) {
		if (!vis[e[i].v]) {
			dep[e[i].v] = dep[u] + 1;
			up[e[i].v][0] = u;
			dfs(e[i].v);
		}
	}
}
int query(int u,int v) {
	//u <= v,v更深
	if (dep[u] > dep[v]) swap(u,v);
	int diff = dep[v] - dep[u];
	for (int i=0,two=1;diff != 0;two <<= 1,i++) {
		if (diff & two) {
			v = up[v][i];
			diff -= two;
		}
	}
	for (int i=log(dep[u])/log(2);i>=0;i--) {
		if (up[u][i] != up[v][i]) {
			u = up[u][i];
			v = up[v][i];
		}
	}
	if (u == v) return u;
	else return up[u][0];
}
int main() {
	memset(head,-1,sizeof(head));
	n = read();
	m = read();
	s = read();
	for (int i=1;i<n;i++) {
		int u,v;
		u = read();
		v = read();
		AddEdge(u,v);
		AddEdge(v,u);
	}
	dfs(s);
	while (m--) {
		int u,v;
		u = read();
		v = read();
		printf("%d\n",query(u,v));
	}
	return 0;
}

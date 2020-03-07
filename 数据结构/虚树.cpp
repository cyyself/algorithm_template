//bzoj 3611
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000005;
const long long inf = 0x3f3f3f3f3f3f3f3f;
vector <int> g[maxn];
long long c[maxn];
int dep[maxn];
int dfn[maxn];
int ts;
int up[maxn][20];
void dfs(int u,int f) {
	dfn[u] = ts ++;
	for (int i=1;(1<<i) <= dep[u];i++) up[u][i] = up[up[u][i-1]][i-1];
	for (int i=0;i<g[u].size();i++) {
		int v = g[u][i];
		if (v == f) continue;
		dep[v] = dep[u] + 1;
		up[v][0] = u;
		dfs(v,u);
	}
}
bool cmp(int x,int y) {
	return dfn[x] < dfn[y];
}
int lca(int x,int y) {
	if (dep[x] > dep[y]) swap(x,y);
	int diff = dep[y] - dep[x];
	for (int i=0;diff;i++) if (diff & (1 << i)) {
		y = up[y][i];
		diff -= (1 << i);
	}
	for (int i=19;i>=0;i--) {
		if (up[x][i] != up[y][i]) {
			x = up[x][i];
			y = up[y][i];
		}
	}
	if (x == y) return x;
	else return up[x][0];
}
bool ins[maxn];
stack <int> used_s;
bool used[maxn];
vector <int> g2[maxn];
void clear_g2() {
	while (!used_s.empty()) {
		int u = used_s.top();
		used_s.pop();
		used[u] = false;
		g2[u].clear();
	}
}
void add(int u,int v) {
	if (!used[u]) {
		used[u] = true;
		used_s.push(u);
	}
	g2[u].push_back(v);
}
bool key_node[maxn];
long long sum,MIN,MAX;
long long down_cur[maxn],down_sz[maxn],down_MMIN[maxn],down_MMAX[maxn];
void dfs2(int u,int fa,long long up_cur,long long up_sz,long long up_MMIN,long long up_MMAX) {
	down_cur[u] = 0;
	down_sz[u] = key_node[u];
	down_MMIN[u] = key_node[u]?0:inf;
	down_MMAX[u] = key_node[u]?0:-inf;
	if (key_node[u]) {
		sum += up_cur;
		MIN = min(MIN,up_MMIN);
		MAX = max(MAX,up_MMAX);
		up_MMIN = min(up_MMIN,0ll);
		up_MMAX = max(up_MMAX,0ll);
		up_sz += 1;
	}
	for (int i=0;i<g2[u].size();i++) {
	//for (auto v:g2[u]) {
		int v = g2[u][i];
		if (v == fa) continue;
		long long d = dep[v] - dep[u];
		dfs2(v,u,up_cur+up_sz*d,up_sz,up_MMIN+d,up_MMAX+d);
		down_cur[u] += down_cur[v] + down_sz[v] * d;
		down_sz[u] += down_sz[v];
		down_MMIN[u] = min(down_MMIN[u],down_MMIN[v] + d);
		down_MMAX[u] = max(down_MMAX[u],down_MMAX[v] + d);
		up_cur += down_cur[v] + down_sz[v] * d;
		up_sz += down_sz[v];
		up_MMIN = min(up_MMIN,down_MMIN[v] + d);
		up_MMAX = max(up_MMAX,down_MMAX[v] + d);
	}
}
int main() {
	int n;
	scanf("%d",&n);
	for (int i=1;i<n;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	c[1] = inf;
	dfs(1,-1);
	int q;
	scanf("%d",&q);
	while (q --) {
		int k;
		scanf("%d",&k);
		vector <int> h;
		for (int i=0;i<k;i++) {
			int t;
			scanf("%d",&t);
			h.push_back(t);
			key_node[t] = true;
		}
		sort(h.begin(),h.end(),cmp);
		stack <int> s;
		s.push(1);
		ins[1] = true;
		clear_g2();
		for (int i=0;i<h.size();i++) {
		//for (auto x:h) {
			int x = h[i];
			if (x == 1) continue;
			int tmp = lca(x,s.top());
			if (tmp == s.top()) {
				s.push(x);
				ins[x] = true;
			}
			else if (ins[tmp]) {
				int last = s.top();
				int cur;
				do {
					ins[last] = false;
					s.pop();
					cur = s.top();
					add(cur,last);
					last = cur;
				}
				while (cur != tmp);
				s.push(x);
				ins[x] = true;
			}
			else {
				int last = s.top();
				while (true) {
					ins[last] = false;
					s.pop();
					int cur = s.top();
					if (dfn[cur] < dfn[tmp]) {
						add(tmp,last);
						s.push(tmp);
						ins[tmp] = true;
						s.push(x);
						ins[x] = true;
						break;
					}
					else {
						add(cur,last);
						last = cur;
					}
				}
			}
		}
		int last = s.top();
		while (!s.empty()) {
			ins[last] = false;
			s.pop();
			if (!s.empty()) {
				int cur = s.top();
				add(cur,last);
				last = cur;
			}
		}
		sum = 0;
		MIN = inf;
		MAX = -inf;
		dfs2(1,-1,0,0,inf,-inf);
		printf("%lld %lld %lld\n",sum,MIN,MAX);
		for (int i=0;i<h.size();i++) key_node[h[i]] = false;
	}
	return 0;
}

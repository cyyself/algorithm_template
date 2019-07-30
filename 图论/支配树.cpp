int n,m;
vector <int> g[100005],g2[100005];//反向图 正向图
int deg[100005],seq[100005];
void topo_sort() {
	queue <int> q;
	for (int i=1;i<=n;i++) if (deg[i] == 0) {
		q.push(i);
		g[0].push_back(i);
		g2[i].push_back(0);
	}
	int cnt = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		seq[++cnt] = u;
		for (auto v:g[u]) {
			deg[v] --;
			if (deg[v] == 0) q.push(v);
		}
	}
}
int f[100005][18],dep[100005];
int LCA(int u,int v) {
	if (dep[u] > dep[v]) swap(u,v);
	int diff = dep[v] - dep[u];
	for (int i=0,bin=1;diff;i++,bin<<=1) if (diff & bin) {
		v = f[v][i];
		diff -= bin;
	}
	if (u == v) return u;
	int m = 0;
	while ((1 << m) < dep[u]) m ++;
	for (int i=m;i>=0;i--) if (f[u][i] != f[v][i]) {
		u = f[u][i];
		v = f[v][i];
	}
	return f[u][0];
}
void build() {
	topo_sort();
	dep[0] = 1;
	for (int i=1;i<=n;i++) {
		int up = -1;
		int u = seq[i];
		for (auto v:g2[u]) {
			if (up == -1) up = v;
			else up = LCA(up,v);
		}
		f[u][0] = up;
		dep[u] = dep[up]+1;
		for (int i=1,bin=1;bin<=dep[u];i++,bin<<=1) f[u][i] = f[f[u][i-1]][i-1];
	}
}

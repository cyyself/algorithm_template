//UVa 247:https://vjudge.net/problem/UVA-247

##includeinclude  <bits/stdc++.h><bits/stdc+ 
using namespace std;
map <string,int> name;
map <int,string> name2;
vector <int> g[30];
bool vis[30];
int dfn[30];
int low[30];
int root[30];
int rootcnt;
int timestamp;
stack <int> s;
void tarjan(int u) {
	dfn[u] = low[u] = ++timestamp;
	vis[u] = true;
	s.push(u);
	for (auto v:g[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u],low[v]);
		}
		else {
			if (vis[v]) low[u] = min(low[u],dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		rootcnt ++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();
			root[v] = rootcnt;
			vis[v] = false;
			if (v == u) break;
		}
	}
}
int main() {
	int n,m;
	int c = 1;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		for (int i=1;i<=n;i++) g[i].clear();
		memset(root,0,sizeof(root));
		memset(vis,false,sizeof(vis));
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		timestamp = 0;
		rootcnt = 0;
		int namecnt = 0;
		name.clear();
		name2.clear();
		while (m --) {
			string a,b;
			cin >> a >> b;
			int _a,_b;
			if (name[a] == 0) {
				name[a] = ++namecnt;
				name2[namecnt] = a;
			}
			if (name[b] == 0) {
				name[b] = ++namecnt;
				name2[namecnt] = b;
			}
			_a = name[a];
			_b = name[b];
			g[_a].push_back(_b);
		}
		if (c > 1) cout << endl;
		cout << "Calling circles for data set "<< c++ <<":\n";
		for (int i=1;i<=n;i++) if (!dfn[i]) tarjan(i);
		memset(vis,false,sizeof(vis));
		for (int i=1;i<=n;i++) {
			if (vis[i]) continue;
			vis[i] = true;
			cout << name2[i];
			for (int j=i+1;j<=n;j++) {
				if (root[i] == root[j]) {
					cout << ", " << name2[j];
					vis[j] = true;
				}
			}
			cout << endl;
		}
	}
	return 0;
}

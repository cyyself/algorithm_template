#include <iostream>
#include <cstring>
using namespace std;
struct Edge {//点权化为边权
	int to;
	int w;
	int next;
};
Edge e[1005];
int pre[105];
int main() {
	memset(pre,-1,sizeof(pre));
	int n,m;
	cin >> n >> m;
	for (int i=0;i<m;i++) {//输入每条边
		int u,v,w;
		cin >> u >> v >> w;
		e[i].to = v;
		e[i].w = w;
		e[i].next = pre[u];
		pre[u] = i;
	}
	while(true) {
		int node;
		cin >> node;//输入要查询的节点
		for (int i = pre[node]; i != -1 ; i = e[i].next) {
			cout << node << "->" << e[i].to << " weight=" << e[i].w << endl;
		}
	}
	return 0;
}

//UVa 10305 - Ordering Tasks
#include <iostream>
#include <cstring>
using namespace std;
int main() {
	bool g[105][105];
	int indegree[105];
	int stack[105];
	int n,m;
	while(scanf("%d%d",&n,&m) == 2) {
		if (n == 0 && m == 0) break;
		memset(indegree,0,sizeof(indegree));
		memset(g,0,sizeof(g));
		for (int i=0;i<m;i++) {
			int u,v;
			scanf("%d%d",&u,&v);
			g[u][v] = true;
			indegree[v] ++;
		}
		int top = 0;
		int p = 0;
		for (int i=1;i<=n;i++) if (indegree[i] == 0) stack[top++] = i;
		while(p < top) {//这样模拟栈来深搜的方式可以写成函数递归的形式
			for (int i=1;i<=n;i++) if (g[stack[p]][i]) {
				indegree[i] --;
				if (indegree[i] == 0) stack[top++] = i;
			}
			p ++;
		}
		cout << stack[0];
		for (int i=1;i<top;i++) cout << " " << stack[i];
			cout << endl;
	}
	return 0;
}
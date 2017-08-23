#include <iostream>
using namespace std;
int g[105][105];//邻接矩阵，这里用NOIP初赛常见的-1代表最大值
int dis[105];
bool vis[105];
int main() {
	int n;
	cin >> n;
	//节点编号从0开始
	for (int i=0;i<n;i++) for (int j=0;j<n;j++) cin >> g[i][j];
	for (int i=0;i<n;i++) dis[i] = -1;//-1代表最大值
	dis[0] = 0;
	for (int i=0;i<n;i++) vis[i] = 0;//清空变量
	while(true) {
		int v = -1;
		for (int i=0;i<n;i++)
			if ( !vis[i] && dis[i] != -1 && (v == -1 || dis[i] < dis[v]) )//v==1时代表这是找到的第一个未扩展节点，dis[i]<dis[v]表示找到了一个距离更小的未扩展节点
				v = i;
		if (v == -1) break;//没找到点，退出
		vis[v] = true;
		for (int i=0;i<n;i++)
			if (g[v][i] != -1 && (dis[i] == -1 || dis[i] > dis[v] + g[v][i])) 
				dis[i] = dis[v] + g[v][i];
	}
	for (int i=0;i<n;i++) cout << dis[i] << endl;
	return 0;
}
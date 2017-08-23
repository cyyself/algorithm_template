#include <iostream>
using namespace std;
int g[105][105];
int main() {
	int n;
	cin >> n;
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) cin >> g[i][j];//输入整个邻接矩阵
	//输入数据中-1表示没有这条边，即无穷大，这里不使用0x3f，而使用NOIP初赛常用的-1作为无穷大，下面判断即可
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) 
				if (k != i && i != j && j != k && g[i][k] != -1 && g[k][j] != -1 && g[i][j] > g[i][k]+g[k][j]) g[i][j],g[i][k]+g[k][j];
			//思想：更小的路径一定是经过了一条更短的路径相连
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) cout << g[i][j] << " ";
		cout << endl;//打出整个邻接矩阵
	}
	return 0;
}
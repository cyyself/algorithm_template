//HDU 2888
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int n,m;
int st[301][301][9][9];
int pow2(int x) {
	return 1 << x;//相当于计算2的x次方，使用位运算
}
void init() {
	//st[x][y][0][0]已经预先填充
	for (int i=0;i<=log2(n);i++)
		for (int j=0;j<=log2(m);j++) {
			if (i == 0 && j == 0) continue;
			for (int x=1;x<=n;x++) for (int y=1;y<=m;y++) {
				int rangex = x + pow2(i) - 1;
				int rangey = y + pow2(j) - 1;
				if (rangex > n || rangey > m) continue;
				if (i == 0) {
					st[x][y][i][j] = max(	st[x][		y		][i][j-1],
											st[x][y+pow2(j-1)	][i][j-1]);
				}
				else {
					st[x][y][i][j] = max(	st[		x		][y][i-1][j],
											st[x+pow2(i-1)	][y][i-1][j]);
				}
			}
		}
}
int query_max(int x1,int y1,int x2,int y2) {
	int k1 = log2(x2-x1+1);
	int k2 = log2(y2-y1+1);
	return max(
				max(
					st[      x1     ][y1][k1][k2],
					st[x2-pow2(k1)+1][y1][k1][k2]
					),
				max(
					st[x1][y2-pow2(k2)+1][k1][k2],
					st[x2-pow2(k1)+1][y2-pow2(k2)+1][k1][k2]
					)
				);
}
int main() {
	while (scanf("%d%d",&n,&m) == 2) {
		for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) {
			scanf("%d",&st[i][j][0][0]);
		}
		init();
		int q;
		scanf("%d",&q);
		while (q --) {
			int r1,c1,r2,c2;
			scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
			int max_value = query_max(r1,c1,r2,c2);
			printf("%d ",max_value);
			if (max_value == max(max(st[r1][c1][0][0],st[r1][c2][0][0]),max(st[r2][c1][0][0],st[r2][c2][0][0]))) puts("yes");
			else puts("no");
		}
	}
	return 0;
}

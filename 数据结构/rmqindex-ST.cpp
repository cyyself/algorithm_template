//与前面的程序不同在于，它能求出最小值所在的位置
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int a[10005];
int st[10005][30];
void initRMQ(int maxn) {
	for (int i=0;i<maxn;i++) st[i][0] = i;
	for (int j=1;pow(2,j)<=maxn;j++) 
		for (int i=0;i+pow(2,j)-1<maxn;i++) {
			int l = st[i][j-1];
			int r = st[i+int(pow(2,j-1))][j-1];
			st[i][j] = a[l] < a[r] ? l : r;
		}
}
inline int RMQ(int u,int v) {
	if (u > v) swap(u,v);
	int k = log(v-u+1)/log(2);
	int l = st[u][k];
	int r = st[v-int(pow(2,k))+1][k];
	return a[l] < a[r] ? l : r;
}
int main() {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	initRMQ(n);
	while(true) {
		int u,v;
		scanf("%d%d",&u,&v);
		int pos = RMQ(u,v);
		printf("Pos:%dValue:%d\n",pos,a[pos]);
	}
	return 0;
}

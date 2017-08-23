//http://noalgo.info/489.html
//仅用于求出区间内最小值
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int a[10005];
int st[10005][30];
void initRMQ(int maxn) {
	for (int i=0;i<maxn;i++) st[i][0]=a[i];
	for (int j=1;pow(2,j)<=maxn;j++)
		for (int i=0;i+pow(2,j)-1<maxn;i++){
			int l = st[i][j-1];
			int r = st[i+int(pow(2,j-1))][j-1];
			st[i][j] = min(l,r);
			//printf("st[%d][%d] = min(st[%d][%d], st[%d][%d]);\n",i,j,i,j-1,i+int(pow(2,j-1)),j-1);
		}
}
inline int RMQ(int u,int v) {//inline会快一些
	if (u > v) swap(u,v);//非常重要！！！特别是在做LCA的时候
	int k = log(v-u+1)/log(2);
	//printf("RMQ(%d,%d)=min(st[%d][%d],st[%d,%d])\n",u,v,u,k,v-int(pow(2,k))+1,k);
	return min(st[u][k],st[v-int(pow(2,k))+1][k]);
}
int main() {
	int n;
	scanf("%d",&n);        
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	initRMQ(n);
	/*
	for (int i=0;i<n;i++) {
		for (int j=0;i + pow(2,j) - 1 < n;j++) printf("%d ",st[i][j]);
		printf("\n");
	}
	*/
	while(true) {
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%d",RMQ(u,v));
	}
	return 0;
}
/*
10
1
2
3
4
5
6
7
8
9
10
*/

//洛谷P3367 【模板】并查集
#include <cstdio>
int family[10005];
int find(int member){
	if (family[member] == member) return member;
	else {
		family[member] = find(family[member]);
		return family[member];
	}
}
int main() {
	int N,M;
	scanf("%d%d",&N,&M);
	for (int i=1;i<=N;i++) family[i] = i;//初始化并查集
	for (int i=0;i<M;i++) {
		int Z,X,Y;
		scanf("%d%d%d",&Z,&X,&Y);
		if (Z == 1) {
			//Union
			family[find(X)] = find(Y);
		}
		else {
			if (find(X) == find(Y)) printf("Y\n");
			else printf("N\n");
		}
	}
	return 0;
}

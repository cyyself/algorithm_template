//http://poj.org/problem?id=1703
#include <cstdio>
int f[100005];
int r[100005];
int find(int x) {
	if (f[x] == x) return x;
	int t = find(f[x]);
	r[x] = (r[x] + r[f[x]]) % 2;
	return f[x] = t;
}
void uni(int x,int y) {
	int xr = find(x);
	int yr = find(y);
	f[xr] = yr;
	r[xr] = (r[x] + r[y] + 1) % 2;
}
int n,m;
void init() {
	for (int i=1;i<=n;i++) {
		f[i] = i;
		r[i] = 0;
	}
}
int main() {
	int T;
	scanf("%d",&T);
	while (T --) {
		scanf("%d%d",&n,&m);
		init();
		char o;
		int x,y;
		while (m --) {
			scanf(" %c%d%d",&o,&x,&y);
			if (o == 'A') {
				if (find(x) == find(y)) {
					if (r[x] == r[y]) printf("In the same gang.\n");
					else printf("In different gangs.\n");
				}
				else printf("Not sure yet.\n");
			}
			else uni(x,y);
		}
	}
	return 0;
}

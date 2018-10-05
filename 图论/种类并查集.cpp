//http://poj.org/problem?id=1703
#include <cstdio>
int f[100005];
int r[100005];
int find(int x) {
	if (x == f[x]) return x;
	int t = find(f[x]);
	r[x] ^= r[f[x]];
	return f[x] = t;
}
void uni(int x,int y) {
	int root_x = find(x);
	int root_y = find(y);
	f[root_x] = root_y;
	if (r[y] == 1) r[root_x] = r[x];
	else r[root_x] = 1 - r[x];
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
		while (m --) {
			char o;
			int x,y;
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

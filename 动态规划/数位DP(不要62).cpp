#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int f[10][2];
int digit[10];
int dfs(int dep,bool last6,bool uplimited) {
	if (dep < 0) return 1;
	if (!uplimited && f[dep][last6] != INF) return f[dep][last6];
	int up = 9;
	if (uplimited) up = digit[dep];
	int cur = 0;
	for (int i=0;i<=up;i++) {
		if ( (i == 2 && last6) || i == 4) continue;
		cur += dfs(dep-1,i == 6,uplimited && i == up);
	}
	if (!uplimited) f[dep][last6] = cur;
	return cur;
}
int solve(int x) {
	int cnt = 0;
	while (x) {
		digit[cnt++] = x % 10;
		x /= 10;
	}
	return dfs(cnt-1,false,true);
}
int main() {
	memset(f,0x3f,sizeof(f));
	int n,m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		cout << solve(m) - solve(n-1) << endl;
	} 
	return 0;
} 

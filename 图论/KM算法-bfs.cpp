//二分图带权匹配的板子题，输出ans是权值
//之后是左边每个匹配到的右边的节点，如果左边和右边不匹配，则输出0
#include <bits/stdc++.h>
using namespace std;
const int maxn = 505;
const long long inf = 0x3f3f3f3f;
struct Matrix {
	int n;
	long long a[505][505];
};
struct KM:Matrix {
	long long hl[maxn],hr[maxn],slk[maxn];
	int fl[maxn],fr[maxn],pre[maxn];
	bool vl[maxn],vr[maxn];
	queue <int> q;
	bool check(int i) {
		vl[i] = 1;
		if (fl[i] != -1) {
			q.push(fl[i]);
			vr[fl[i]] = true;
			return true;
		}
		while (i != -1) {
			fl[i] = pre[i];
			swap(i,fr[fl[i]]);
		}
		return 0;
	}
	void bfs(int s) {
		memset(slk,0x3f,sizeof(slk));
		memset(vl,0,sizeof(vl));
		memset(vr,0,sizeof(vr));
		while (!q.empty()) q.pop();
		q.push(s);
		vr[s] = true;
		while (true) {
			long long d;
			while (!q.empty()) {
				for (int i=0,j=q.front();i<n;i++) {
					d = hl[i] + hr[j] - a[i][j];
					if (!vl[i] && slk[i] >= d) {
						pre[i] = j;
						if (d) slk[i] = d;
						else if (!check(i)) return;
					}
				}
				q.pop();
			}
			d = inf;
			for (int i=0;i<n;i++) 
				if (!vl[i] && d > slk[i]) d = slk[i];
			for (int i=0;i<n;i++) {
				if (vl[i]) hl[i] += d;
				else slk[i] -= d;
				if (vr[i]) hr[i] -= d;
			}
			for (int i=0;i<n;i++) 
				if (!vl[i] && slk[i] == 0 && !check(i)) return;
		}
	}
	void ask() {
		memset(pre,-1,sizeof(pre));
		memset(fl,-1,sizeof(fl));
		memset(fr,-1,sizeof(fr));
		memset(hl,0,sizeof(hl));
		memset(hr,0,sizeof(hr));
		for (int i=0;i<n;i++) 
			for (int j=0;j<n;j++) hl[i] = max(hl[i],a[i][j]);
		for (int i=0;i<n;i++) bfs(i);
	}
}km;
int main() {
	int nl,nr,m;
	scanf("%d%d%d",&nl,&nr,&m);
	for (int i=0;i<m;i++) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		u --;
		v --;
		km.a[u][v] = w;
	}
	km.n = max(nl,nr);
	km.ask();
	long long ans = 0;
	for (int i=0;i<nl;i++) 
		if (km.fl[i] != -1) ans += km.a[i][km.fl[i]];
	printf("%lld\n",ans);
	for (int i=0;i<nl;i++) {
		if (km.fl[i]!=-1 && km.a[i][km.fl[i]]) printf("%d",km.fl[i]+1);
		else printf("0");
		if (i == nl - 1) printf("\n");
		else printf(" ");
	}
	return 0;
}

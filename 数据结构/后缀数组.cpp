//untested
#define val first
#define id second
void sort_suffix(int s[],int n,int rk[]) {
	static pair <long long,int> sa[maxn];//用于后缀数组排序
	for (int i=1;i<=n;i++) {
		sa[i].id = i;
		sa[i].val = s[i];
	}
	sort(sa+1,sa+1+n);
	for (int i=1;i<=n;i++) rk[sa[i].id] = i;
	for (int d=1;d<=n;d<<=1) {
		for (int i=1;i<=n;i++) {
			sa[i].val = rk[sa[i].id] * (n+1) + ((i+d<=n)?rk[sa[i+d].id]:0);
		}
		sort(sa+1,sa+1+n);
		for (int i=1;i<=n;i++) rk[sa[i].id] = i;
	}
}

#include <bits/stdc++.h>
using std::swap;
//don't using namespace std
int a[100005];
void sort(int l,int r) {
	int i = l;
	int j = r;
	int base = a[l+rand()%(r-l+1)];
	while (i <= j) {
		while (a[i] < base) i++;
		while (a[j] > base) j--;
		if (i <= j) {
			swap(a[i],a[j]);
			i++;
			j--;
		}
	}
	if (l < j) sort(l,j);
	if (i < r) sort(i,r);
}
int read() {
	int f = 1;
	char c = getchar();
	int ret = 0;
	while (!(c >= '0' && c <= '9')) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >='0' && c <= '9') {
		ret = ret * 10 + c - '0';
		c = getchar();
	}
	return ret * f;
}
int main() {
	srand((unsigned)time(0));
	int n = read();
	for (int i=0;i<n;i++) a[i] = read();
	sort(0,n-1);
	for (int i=0;i<n;i++) printf("%d ",a[i]);
	return 0;
}

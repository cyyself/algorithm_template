#include <bits/stdc++.h>
using namespace std;
char a[11000005];
char b[22000010];
int  p[22000010];
int lena,lenb;
int main() {
	scanf("%s",a);
	lena = strlen(a);
	b[0] = '$';
	b[1] = '#';
	int j = 2;
	for (int i=0;i<lena;i++) {
		b[j++] = a[i];
		b[j++] = '#';
	}
	b[j] = '\0';
	lenb = strlen(b);
	int ans = -1;
	int id;
	int mx = 0;
	for (int i=1;i < lenb;i++) {
		if (i < mx) p[i] = min(p[2*id-i],mx - i);
		else p[i] = 1;
		while (b[i-p[i]] == b[i+p[i]]) p[i] ++;
		if (mx < i + p[i]) {
			id = i;
			mx = i + p[i];
		}
		ans = max(ans,p[i]-1);
	}
	printf("%d\n",ans);
	return 0;
}

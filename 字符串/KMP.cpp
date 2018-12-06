//Luogu P3375：给出两个字符串T和P，其中P为T的子串，求出P在T中所有出现的位置。
#include <bits/stdc++.h>
char T[1000005];
char P[1000005];
int jump[1000005];
int n,m;
void getnext() {
	jump[1] = 0;
	int k = 0;
	for (int i=2;i<=m;i++) {
		while (k != 0 && P[i] != P[k+1]) k = jump[k];
		if (P[i] == P[k+1]) k ++;
		jump[i] = k;
	}
}
int main() {
	scanf("%s",T+1);
	scanf("%s",P+1);
	n = strlen(T+1);
	m = strlen(P+1);
	getnext();
	int k = 0;
	for (int i=1;i<=n;i++) {
		while (k != 0 && T[i] != P[k+1]) k = jump[k];
		if (T[i] == P[k+1]) k++;
		if (k == m) {
			printf("%d\n",i-m+1);
		}
	}
	for (int i=1;i<=m;i++) {
		if (i != 1) printf(" ");
		printf("%d",jump[i]);
	}
	printf("\n");
	return 0;
}

//Luogu P3375：给出两个字符串T和P，其中P为T的子串，求出P在T中所有出现的位置。
#include <bits/stdc++.h>
char T[1000005];
char P[1000005];
int jump[1000005];
int n,m;
void getnext() {
	jump[0] = -1;
	int k = -1;
	for (int i=1;i<m;i++) {
		while (k != -1 && P[i] != P[k+1]) k = jump[k];
		if (P[i] == P[k+1]) k ++;
		jump[i] = k;
	}
}
int main() {
	scanf("%s",T);
	scanf("%s",P);
	n = strlen(T);
	m = strlen(P);
	getnext();
	int k = -1;
	for (int i=0;i<n;i++) {
		while (k != -1 && T[i] != P[k+1]) k = jump[k];
		if (T[i] == P[k+1]) k++;
		if (k == m - 1) {
			printf("%d\n",i-m+2);
		}
	}
	for (int i=0;i<m;i++) {
		if (i != 0) printf(" ");
		printf("%d",jump[i]+1);
	}
	printf("\n");
	return 0;
}

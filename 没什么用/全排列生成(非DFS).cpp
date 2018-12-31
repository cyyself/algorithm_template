#include <bits/stdc++.h>
namespace cyy {
	bool next_permutation(int *a,int *b) {
		b --;
		int* p = b;
		while (p != a && *(p - 1) >= *p) p --;
		if (p == a) return false;
		for (int* p1 = b;p1>=p;p1--) {
			if (*p1 > *(p-1)) {
				std::swap(*p1,*(p-1));
				break;
			}
		}
		std::sort(p,b+1);
		return true;
	}
};
int main() {
	int a[10],b[10];
	for (int i=1;i<=10;i++) a[i-1] = i,b[i-1] = i;
	do {
		for (int i=0;i<10;i++) if (a[i] != b[i]) {
			printf("error\n");
		}
		cyy::next_permutation(a,a+10);
	}
	while (std::next_permutation(b,b+10));
	return 0;
}

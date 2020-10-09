#include <bits/stdc++.h>
using namespace std;
int ask(int x) {
	printf("%d\n",x);
	fflush(stdout);
	int res;
	scanf("%d",&res);
	return res;
}
int main() {
	int l = 1, r = 1000;
	while (l <= r) {
		int mid = (l + r) >> 1;
		int res = ask(mid);
		if (res == 0) {
			break;
		}
		else if (res == -1) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	return 0;
}
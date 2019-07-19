//给定n个整数（数字可能重复），求在这些数中选取任意个，使得他们的异或和最大。
#include <bits/stdc++.h>
using namespace std;
struct LB {
	long long r[63];
	LB() {
		memset(r,0,sizeof(r));
	}
	LB(const LB &b) {
		for (int i=0;i<63;i++) r[i] = b.r[i];
	}
	bool insert(long long x) {
		for (int i=62;i>=0;i--) {
			if ((x >> i) & 1) {
				if (r[i] == 0) {
					r[i] = x;
					return true;
				}
				else x ^= r[i];
			}
		}
		return false;
	}
	bool check(long long x) {
		for (int i=62;i>=0;i--) {
			if ((x >> i) & 1) {
				if (r[i] == 0) return false;
				x ^= r[i];
			}
		}
		return true;
	}
	long long query_max(long long ret = 0) {//自定义初始值
		for (int i=62;i>=0;i--) ret = max(ret,ret^r[i]);
		return ret;
	}
	void merge(const LB &b) {
		for (int i=0;i<=62;i++) insert(b.r[i]);
	}
};
int main() {
	LB A;
	int n;
	scanf("%d",&n);
	while (n --) {
		long long x;
		scanf("%lld",&x);
		A.insert(x);
	}
	cout << A.query_max() << endl;
	return 0;
}

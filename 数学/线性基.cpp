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
	static LB intersect(const LB &a,const LB &b) {
		LB all,d,ret;
		for (int i=63;i>=0;i--) {
			all.r[i] = a.r[i];
			d.r[i] = 1 << i;
		}
		for (int i=63;i>=0;i--) if (b.r[i]) {
			long long v = b.r[i],k = 0;
			bool flag = true;
			for (int j=63;j>=0;j--) if ((v >> j) & 1) {
				if (all.r[j]) { v ^= all.r[j]; k ^= d.r[j];}
				else { flag = false; all.r[j] = v; d.r[j] = k; break; }
			}
			if (flag) {
				long long tmp = 0;
				for (int j=63;j>=0;j--) if ((k >> j) & 1) tmp ^= a.r[j];
				ret.insert(tmp);
			}
		}
		return ret;
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

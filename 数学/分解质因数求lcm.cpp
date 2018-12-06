/*
通常我们可用a*b/gcd(a,b)求lcm，但许多题目会遇到需要取模的情况，而mod运算只在加、减、乘中满足结合律，因此需要用分解质因数的方法求lcm（最小公倍数）
该方法很简单，求出每个数的质因数，对于相同的质因数，我们求出每个数的该质因数的个数，然后把这些不同数的相同质因数中各自取数量最大的归为一个集合，把每个最大质因数集合相乘，便得到了lcm。
具体请百度“分解质因数求最小公倍数”，看数学方法就行
*/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
struct zys{
	int n;//这个质因数
	int s;//这个质因数的数量
	zys():n(0),s(0){}
};
vector <zys> l;
void fjzys(int num) {
	zys curr;
	//短除法，我们在用小的数一遍遍除的时候其实也就把非质数筛掉了，比如2除完不可能再被4整除。
	for (int i=2;i<=num;i++) while (num % i == 0) {
		//此时i是num的一个质因数
		num /= i;
		if (i == curr.n) curr.s ++;
		else {
			if (curr.n != 0) l.push_back(curr);
			curr.n = i;
			curr.s = 1;
		}
	}
	if (curr.n != 0) l.push_back(curr);
}
inline void outputfjzys(int num){//这个函数仅供学习分解质因数过程使用，在程序中没有调用
	for (int i=2;i<=num;i++) {
		while(num % i == 0) {
			printf("%d ",i);
			num /= i;
		}
	}
	printf("\n");
}
inline bool comp(const zys &a,const zys &b) {
	if (a.n < b.n) return true;
	if (a.n == b.n && a.s > b.s) return true;
	return false;
}
long long qpow(long long di,long long zhi,long long mod) {
	if (zhi == 0) return 1 % mod;
	if (zhi == 1) return di % mod;
	long long ret = qpow(di,zhi/2,mod) % mod;
	ret = (ret * ret) % mod;
	if (zhi % 2) ret = ret * (di % mod);
	return ret % mod;
}
int main() {
	int n,q;//q为取mod的值
	scanf("%d%d",&n,&q);
	int MAX = 0;
	for (int i=0;i<n;i++) {
		int t;
		scanf("%d",&t);
		fjzys(t);
		MAX = max(t,MAX);
	}
	if (l.size() != 0) {
		sort(l.begin(),l.end(),comp);
		long long lcm = qpow(l[0].n,l[0].s,q);
		for (int i=1;i<l.size();i++) {
			if (l[i].n == l[i-1].n) continue;
			lcm = (lcm * qpow(l[i].n,l[i].s,q))%q;
		}
		printf("%lld\n",lcm);
	}
	else {
		//那么输入的数一定都是1或0了
		printf("%d\n",MAX);
	}
	return 0;
}
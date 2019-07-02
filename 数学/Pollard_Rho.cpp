//POJ 2429 给出两个数的gcd和lcm，求这两个数，多解时输出和最小的解
#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;
long long gcd(long long a,long long b) {
	if (b == 0) return a;
	return gcd(b,a%b);
}
long long mul(long long a,long long b,long long mod){
	long long ret=0;
	while(b) {
		if(b & 1) {
			ret += a;
			ret %= mod;
		}
		a <<= 1;
		a %= mod;
		b >>= 1;
	}
	return ret;
}
long long pow(long long a,long long b,long long mod) {
	long long ret = 1;
	while(b) {
		if(b & 1) ret = mul(ret,a,mod);
		a = mul(a,a,mod);
		b >>= 1;
	}
	return ret;
}
bool check(long long a,long long n){
	long long x = n - 1;
	int t = 0;
	while((x & 1) == 0) {
		x >>= 1;
		t ++;
	}
	x = pow(a,x,n);
	long long y;
	for(int i=1;i<=t;i++) {
		y = mul(x,x,n);
		if(y == 1 && x != 1 && x != n - 1) return true;
		x = y;
	}
	if(y != 1) return true;
	return false;
}
bool Miller_Rabin(long long n) {
	if(n == 2) return true;
	if(n == 1 || !(n & 1)) return false;
	const int arr[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
	for(int i = 0; i < 12; i++) {
		if (arr[i] >= n) break;
		if(check(arr[i], n)) return false;
	}
	return true;
}
long long Pollard_rho(long long n,int c) {
	long long i=1,k=2,x,y,d;
	y = x = rand() % n;
	while (true) {
		i ++;
		x = (mul(x,x,n) + c) % n;
		d = gcd(y-x,n);
		if (d > 1 && d < n) return d;
		if (y == x) break;
		if (i == k) {
			y = x;
			k <<= 1;
		}
	}
	return true;
}
void factorize(long long n,map<long long,int> &cnt,int c = 107) {
	if (n == 1) return;
	if (Miller_Rabin(n)) {
		cnt[n] ++;
		return;
	}
	long long p = n;
	while (p >= n) p = Pollard_rho(p,c--);
	factorize(p,cnt,c);
	factorize(n/p,cnt,c);
}
long long g,l,n,a,b;
map <long long,int> cnt;
void dfs(map<long long,int>::iterator it,long long val) {
	if (it == cnt.end()) {
		long long cur_a = val * g;
		long long cur_b = (n / val) * g;
		//printf("(debug)%lld %lld\n",cur_a,cur_b);
		if (cur_a + cur_b < a + b && gcd(cur_a,cur_b) == g) {
			a = min(cur_a,cur_b);
			b = max(cur_a,cur_b);
		}
	}
	else {
		map<long long,int>::iterator nit = it;
		nit ++;
		for (int i=0;i<=it->second;i++) {
			dfs(nit,val);
			val *= it->first;
		}
	}
}
int main() {
	while (scanf("%lld%lld",&g,&l) == 2) {
		n = l / g;
		cnt.clear();
		factorize(n,cnt);
		/*
		printf("-----DEBUG BEGIN-----\n");
		for (auto x:cnt) printf("%lld %d\n",x.first,x.second);
		printf("-----DEBUG  END -----\n");
		*/
		a = b = 0x3f3f3f3f3f3f3f3f;
		dfs(cnt.begin(),1);
		printf("%lld %lld\n",a,b);
	}
	return 0;
}

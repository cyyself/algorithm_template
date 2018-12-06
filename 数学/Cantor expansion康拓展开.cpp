#include <bits/stdc++.h>
using namespace std;
long long getcantor(int arr[],int len) {
	long long xs = 1;//系数
	for (int i=2;i<=len-1;i++) xs *= i;
	long long ret = 0;
	for (int i=0;i<len;i++) {
		int a = 0;//这个数在未出现的元素(即后面的元素中的排名)，从0开始计算
		//a可以当做在这个数后面有多少个数比它小
		for (int j=i+1;j<len;j++) if (arr[j] < arr[i]) a++;
		ret += xs * a;
		if (i != len - 1) xs /= len-1-i;
	}
	return ret;
}
int a[15];
int main() {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		a[i] = i + 1;
	}
	do {
		printf("Cantor=%lld\t",getcantor(a,n));
		for (int i=0;i<n;i++) printf("%d\t",a[i]);
		printf("\n");
	} while (next_permutation(a,a+n));
	return 0;
}

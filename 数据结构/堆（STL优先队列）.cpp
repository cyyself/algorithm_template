//堆就是优先队列的数据结构
//洛谷P3378 【模板】堆
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
struct shuju {
	int value;
	friend bool operator < (const shuju &a,const shuju &b) {
		if (a.value > b.value) return true;
		return false;
	}
};
priority_queue <shuju> q;
int main() {
	int n;
	scanf("%d",&n);
	while(n--) {
		int o;
		scanf("%d",&o);
		switch(o) {
			case 1:
				int x;
				scanf("%d",&x);
				q.push((shuju){x});
			break;
			case 2:
				printf("%d\n",q.top().value);
			break;
			case 3:
				q.pop();
			break;
		}
	}
	return 0;
}
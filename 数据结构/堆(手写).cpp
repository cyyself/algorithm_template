//Luogu P3378:https://www.luogu.org/problemnew/show/P3378
#include <bits/stdc++.h>
using std::swap;
class pq {
	public:
		void init() {
			size = 0;
		}
		void push(int x) {
			arr[++size] = x;
			shift_up(size);
		}
		int top() {
			return arr[1];
		}
		void pop() {
			swap(arr[1],arr[size]);
			size --;
			shift_down(1);
		}
	private:
		int arr[1000005];
		int size;
		void shift_up(int node) {
			while ( (node >> 1) >= 1) {
				int T = node >> 1;//父节点
				if (arr[node] < arr[T]) swap(arr[node],arr[T]);//小根堆，如果自己比父节点小，就交换
				else break;
				node = T;
			}
		}
		void shift_down(int node) {
			while ( (node << 1) <= size) {
				int T = node << 1;//它的左子节点
				if (T+1 <= size && arr[T+1] < arr[T]) T = T+1;//右子节点存在且更小时，选择右子节点
				if (arr[node] > arr[T]) swap(arr[node],arr[T]);//小根堆，如果自己比子节点大，就交换
				else break;
				node = T;
			}
		}
}q;
int main() {
	q.init();
	int n;
	scanf("%d",&n);
	while(n--) {
		int o;
		scanf("%d",&o);
		switch(o) {
			case 1:
				int x;
				scanf("%d",&x);
				q.push(x);
				break;
			case 2:
				printf("%d\n",q.top());
				break;
			case 3:
				q.pop();
				break;
		}
	}
	return 0;
}

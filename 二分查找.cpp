#include <iostream>
#include <vector>
using namespace std;
int main(){
	int n;
	cin >> n;
	vector <int> array;
	for (int i=0;i<n;i++){
		int t;
		cin >> t;
		array.push_back(t);
	}
	int key;//要查找的数
	cin >> key;
	int left = 0, right = n-1;
	while(left <= right){//防止没找到的情况陷入死循环
		int mid = (left + right) / 2;
		if (array[mid] < key) left = mid + 1;//array[mid]值太小了，把二分区间左边调整到当前查找数字的右边
		else if (array[mid] > key) right = mid - 1;//array[mid]值太大了，把二分区间右边调整到当前查找数字的左边
			else {
				cout << "Postion:" << mid << endl;//输出位置
				break;
			}
	}
	return 0;
}
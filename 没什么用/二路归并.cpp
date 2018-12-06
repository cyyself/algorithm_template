#include <iostream>
#include <vector>
using namespace std;
int main(){
	int a,b;
	cin >> a >> b;
	vector <int> set1;
	vector <int> set2;
	vector <int> result;
	for (int i=0;i<a;i++){
		int temp;
		cin >> temp;
	 	set1.push_back(temp);
	}
	for (int i=0;i<b;i++){
		int temp;
		cin >> temp;
		set2.push_back(temp);
	}
	//输入完成
	int i = 0;//set1的位置
	int j = 0;//set2的位置
	while(i != set1.size() || j != set2.size()){
		if (i == set1.size()){
			result.push_back(set2[j]);
			j++;
			continue;
		}
		if (j == set2.size()){
			result.push_back(set1[i]);
			i++;
			continue;
		}
		if (set1[i] < set2[j]){
			result.push_back(set1[i]);
			i++;
		}
		else{
			result.push_back(set2[j]);
			j++;
		}
	}
	for (vector<int>::iterator i=result.begin();i != result.end();i++){
		cout << *i << endl;
	}
	return 0;
}


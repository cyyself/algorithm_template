//邻接矩阵
#include <iostream>
using namespace std;
int main(){
	int matrix[20][20];
	memset(matrix,0x7f,sizeof(matrix));//若处理数据时需要相加，请使用0x3f
	//需要注意的是，0x7f并不是int的最大值
	//注意，输入时应考虑数组越界问题
	int n;
	cin >> n;
	for (int i=0;i<n;i++){
		int start,end,weight;
		cin >> start >> end >> weight;
		matrix[start][end] = weight;//有向图，若为无向图请uncomment下一行
		//matrix[start][end] = weight;
	}
	while (true){
		//在这里，你可以输入数据来查询
		int start,end;
		cin >> start >> end;
		cout << start << "->" << end << " weight=" << matrix[start][end] << endl;
	}
	//使用control+c退出
	return 0;
}
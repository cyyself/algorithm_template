#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Edge{
	int u,v,w;
	Edge(int _u,int _v,int _w):u(_u),v(_v),w(_w){}
	Edge(){}
};
Edge e[200005];
int family[5005];//记录这个节点的根节点 
int find(int member){
	if (family[member] == member) return member;
	else {
		family[member] = find(family[member]);//记忆化 
		return family[member];
	}
}
bool comp(const Edge &a,const Edge &b){
	if (a.w < b.w) return true;
	return false;
}
int main() {
	int N,M;
	cin >> N >> M;
	for (int i=1;i<=N;i++) family[i] = i;//初始化并查集 
	for (int i=0;i<M;i++) {
		int X,Y,Z;
		cin >> X >> Y >> Z;
		e[i] = Edge(X,Y,Z);
	}
	sort(e,e+M,comp);
	int k = 0;//记录连起来的边数 
	int tot = 0;//已经连起来的边权 
	for (int i=0;i<M;i++) {
		if (find(e[i].u) != find(e[i].v)) {
			family[find(e[i].u)] = find(e[i].v);//把e[i].u和e[i].v连起来 
			tot += e[i].w;
			k++;
		}
		if (k == N - 1) break;
	}
	if (k != N - 1) cout << "orz" << endl;
	else cout << tot << endl;
	return 0;
}

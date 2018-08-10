/*
题目源自POJ 2104
http://poj.org/problem?id=2104
由于指针TLE，非指针版本在此https://github.com/cyyself/OILife/blob/master/POJ/2104%20-%20K-th%20Number.cpp

参考资料：
https://www.bilibili.com/video/av4619406
https://blog.csdn.net/creatorx/article/details/75446472

我自己在网上看了许多主席树的代码，但都觉得不是很通俗易懂，后来看了一篇文章和一个视频才算有所了解。
自己写了一个用指针的版本，并且代码中有大量注释，希望能对大家有帮助。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct DATA {
	int v;
	int pos;
	friend bool operator < (const DATA &a,const DATA &b) {
		return a.v < b.v;
	}
}d[100005];
int rk[100005];//输入数据各个数字的值对应的rank，做离散化（为了方便就不用unique+cnt的方法了）
struct node {
	node *l;
	node *r;
	int sum;//树上存储每个节点的sum
};
node *root[100005];
void push_up(node *n) {
	n->sum = n->l->sum + n->r->sum;
}
node* create_and_copy_node(node *src) {//复制这个节点的信息，返回一个新创建的指针
	node *ret = new node;
	ret->l = src->l;
	ret->r = src->r;
	ret->sum = src->sum;
	return ret;
}
void insert(node *n,int l,int r,int pos) {//由于是单点增加，所以只需要传入pos参数就行了
	if (l == r) {
		n->sum ++;
	}
	else {
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			//要修改的节点在左子树
			n->l = create_and_copy_node(n->l);//每当我们需要修改时，创建一个新的节点，并复制之前的信息
			insert(n->l,l,mid,pos);
		}
		else {
			n->r = create_and_copy_node(n->r);
			insert(n->r,mid+1,r,pos);
		}
		//因为是单点修改，不存在那种判断修改的区间是两个的情况了（实际上这种情况主席树也可以做）
		push_up(n);
	}
}
int query(node *x,node *y,int l,int r,int k) {//找到前缀和之差等于k的位置
	int cur = y->l->sum - x->l->sum;
	if (l == r) return l;
	else {
		int mid = (l + r) >> 1;
		if (k <= cur) {
			//答案在左子树
			return query(x->l,y->l,l,mid,k);
		}
		else {
			//答案在右子树
			return query(x->r,y->r,mid+1,r,k-cur);
		}
	}
}
/*
首先我们先对输入的数据进行离散化，将数字的值对应到它本身的排名。
我们构造一棵线段树，存储离散后的n个元素出现的次数。
例如有个排名为i的元素出现一次，我们就在线段树的i位置+1
但是一共会插入n个元素，如果每次构造一棵线段树显然MLE。
这时候我们就使用主席树，先复制原来的那棵线段树的节点指针。
因为线段树单点修改每次修改只会修改一条链（只需要新创建log n数量级的节点），
所以我们对于没有修改的部分可以继续用之前的指针，
来减少内存占用，这便是主席树。
*/
int read() {
	int ret = 0;
	int f = 1;
	char c = getchar();
	while (!(c >= '0' && c <= '9')) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		ret *= 10;
		ret += c - '0';
		c = getchar();
	}
	return ret * f;
}
int main() {
	int n,m;
	n = read();
	m = read();
	for (int i=1;i<=n;i++) {
		d[i].v = read();
		d[i].pos = i;
	}
	sort(d+1,d+1+n);
	for (int i=1;i<=n;i++) rk[d[i].pos] = i;//把原始数据中输入的位置对应到rank

	//构造一个sum为0的root[0]，因为主席树查询时可能出现之前时间的另一棵树不存在的情况
	root[0] = new node;
	root[0]->l = root[0];
	root[0]->r = root[0];
	root[0]->sum = 0;

	for (int i=1;i<=n;i++) {
		//先复制一遍之前的节点
		root[i] = create_and_copy_node(root[i-1]);
		insert(root[i],1,n,rk[i]);
	}

	while (m--) {
		int x,y,k;
		x = read();
		y = read();
		k = read();
		int pos = query(root[x-1],root[y],1,n,k);
		printf("%d\n",d[pos].v);
	}
	return 0;
}

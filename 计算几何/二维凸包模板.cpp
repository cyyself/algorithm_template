//HDU 1392
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int n;
struct pos {
	int x,y;
	friend bool operator < (const pos &a,const pos &b) {
		return a.y < b.y || (a.y == b.y && a.x < b.x);
	}
}p[105];
struct stack {//不用STL的原因是STL不能输出栈的次顶元素
	pos a[105];
	int t;
	inline void init() {
		t = -1;
	}
	inline void push(pos i) {
		a[++t] = i;
	}
	inline void pop() {
		t--;
	}
	inline pos top() {
		return a[t];
	}
	inline pos sec() {//次顶
		return a[t-1];
	}
	inline bool available() {
		return t > 0;//至少有两个元素
	}
	inline int size() {
		return t+1;
	}
	inline int topindex() {
		return t;
	}
}s;
inline bool judge(const pos &e,const pos &c,const pos &s) {
	return (e.x - s.x) * (c.y - s.y) - (c.x - s.x) * (e.y - s.y) >= 0;
}
void gerham() {
	sort(p,p+n);
	s.init();
	for (int i=0;i<min(2,n);i++) s.push(p[i]);
	if (n > 2) {
		for (int i=2;i<n;i++) {
			while (s.available() && judge(p[i],s.top(),s.sec())) s.pop();
			s.push(p[i]);
		}
		int len = s.size();
		//这里cyy的写法和许多人不一样，请注意
        //大多数人是用topindex作为len，后面用topindex加以判断
		s.push(p[n-2]);
		for (int i=n-3;i>=0;i--) {
			while (s.size() > len && judge(p[i],s.top(),s.sec())) s.pop();
			s.push(p[i]);
		}
	}
	else s.push(p[0]);
}
inline double dis(const pos &a,const pos &b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
int main() {
	while (scanf("%d",&n) == 1) {
		if (n == 0) break;
		for (int i=0;i<n;i++) scanf("%d%d",&p[i].x,&p[i].y);
		gerham();
		double ans = 0;
		if (s.size() > 2) {
			if (s.size() > 3) 
				for (int i=0;i<s.size()-1;i++) ans += dis(s.a[i],s.a[i+1]);
			else ans += dis(s.a[0],s.a[1]);
		}
		//由于第一个点会在最后再次入栈，所以做到s.size()-1
		printf("%0.2lf\n",ans);
	}
	return 0;
}
//HDU 1392
#include <bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
#define y first
#define x second
int n;
pair <int,int> p[105];
class mystack : public stack<PII> {
public:
	PII sec() {
		PII tmp = top();
		pop();
		PII sec = top();
		push(tmp);
		return sec;
	}
};
inline bool judge(const PII &e,const PII &c,const PII &s) {
	return (e.x - s.x) * (c.y - s.y) - (c.x - s.x) * (e.y - s.y) >= 0;
}
void graham(vector <PII> &res) {
	sort(p,p+n);
	mystack s;
	for (int i=0;i<min(2,n);i++) s.push(p[i]);
	if (n > 2) {
		for (int i=2;i<n;i++) {
			while (s.size()>=2 && judge(p[i],s.top(),s.sec())) s.pop();
			s.push(p[i]);
		}
		int len = s.size();
		s.push(p[n-2]);
		for (int i=n-3;i>=0;i--) {
			while ((int)s.size() > len && judge(p[i],s.top(),s.sec())) s.pop();
			s.push(p[i]);
		}
	}
	else s.push(p[0]);
	res.clear();
	while (!s.empty()) {
		res.push_back(s.top());
		s.pop();
	}
}
inline double dis(const PII &a,const PII &b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
int main() {
	while (scanf("%d",&n) == 1) {
		if (n == 0) break;
		for (int i=0;i<n;i++) scanf("%d%d",&p[i].x,&p[i].y);
		vector <PII> res; 
		graham(res);
		double ans = 0;
		if (res.size() > 2) {
			if (res.size() > 3) 
				for (int i=0;i<(int)res.size()-1;i++) ans += dis(res[i],res[i+1]);
			else ans += dis(res[0],res[1]);
		}
		printf("%0.2lf\n",ans);
	}
	return 0;
}

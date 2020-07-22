#include <bits/stdc++.h>
using namespace std;
namespace Geometry {
	const double eps = 1e-8;
	bool eq(double x,double y) {
		return abs(x-y) < eps;
	}
	int sgn(double x) {
		if (eq(x,0)) return 0;
		else return x>0?1:-1;
	}
	struct Point {
		double x,y;
		Point() {
			x = 0;
			y = 0;
		}
		Point(double _x,double _y) {
			x = _x;
			y = _y;
		}
		friend Point operator + (const Point &a,const Point &b) {
			return Point(a.x+b.x,a.y+b.y);
		}
		friend Point operator - (const Point &a,const Point &b) {
			return Point(a.x-b.x,a.y-b.y);
		}
		friend double operator * (const Point &a,const Point &b) {
			return a.x * b.x + a.y * b.y;
		}
		friend double operator ^ (const Point &a,const Point &b) {
			return a.x * b.y - a.y * b.x;//cross product
		}
		friend Point operator * (double k,Point p) {
			return Point(p.x*k,p.y*k);
		}
	};
	struct Line {
		Point u,v;
		Point d;
		double deg;
		Line() {
			deg = 0;
		}
		Line(const Point &_u,const Point &_v) {
			u = _u;
			v = _v;
			d = v - u;
			deg = atan2(d.y,d.x);
		}
		friend bool operator < (const Line &a,const Line &b) {
			if (eq(a.deg,b.deg)) return sgn((a.v-a.u) ^ (b.v-a.u)) > 0;
			//第二个确实是a.u不是b.u，这里没打错
			return a.deg < b.deg;
		}
	};
	template <typename T> 
	class mydeque : public deque <T> {
	public:
		T front_sec() {
			T tmp = this->front();
			this->pop_front();
			T res = this->front();
			this->push_front(tmp);
			return res;
		}
		T back_sec() {
			T tmp = this->back();
			this->pop_back();
			T res = this->back();
			this->push_back(tmp);
			return res;
		}
	};
	Point inter(Line a,Line b) {
		Point c = b.u - a.u;
		return b.u + ((c^a.d) / (a.d^b.d)) * b.d;
	}
	bool check(Point p,Line l) {
		return sgn(l.d ^ (p-l.u)) > 0;//点在直线左侧
	}
	void HPI(vector<Line> lines,vector <Point> &result) {
		result.clear();
		sort(lines.begin(),lines.end());
		vector <Line> lines;
		auto last_line = lines_in[0];
		for (auto x:lines_in) {
			if (!eq(x.deg,last_line.deg)) lines.push_back(last_line);
			last_line = x;
		}
		lines.push_back(last_line);
		if (lines.size() < 3) return;
		mydeque <Line> q;
		for (int i=0;i<lines.size();i++) {
			while (q.size() >= 2 && !check(inter(q.back_sec(),q.back()),lines[i])) q.pop_back();
			while (q.size() >= 2 && !check(inter(q.front_sec(),q.front()),lines[i])) q.pop_front();
			q.push_back(lines[i]);
		}
		while (q.size() >= 2 && !check(inter(q.back_sec(),q.back()),q.front())) q.pop_back();
		while (q.size() >= 2 && !check(inter(q.front_sec(),q.front()),q.back())) q.pop_front();
		Line fi = q.front();
		q.pop_front();
		Line last = fi;
		while (!q.empty()) {
			auto cur = q.front();
			q.pop_front();
			result.push_back(inter(last,cur));
			if (q.empty()) {
				result.push_back(inter(cur,fi));
			}
			last = cur;
		}
	}
	double poly_area(const vector <Point> &p) {//p需按照极角排序
		if (p.size() < 3) return 0;
		//Point fi = *p.begin();
		double sum = 0;
		for (int i=0;i<p.size();i++) {
			sum += p[i] ^ p[(i+1)%p.size()];
		}
		return sum / 2;
	}
}
using namespace Geometry;
int main() {
	for (int cas=1;cas<=1;cas++) {
		//给出n个多边形
		int n;
		scanf("%d",&n);
		vector <Line> lines;
		while (n --) {
			int m;
			scanf("%d",&m);
			vector <Point> tmp;
			for (int i=0;i<m;i++) {
				double x,y;
				scanf("%lf%lf",&x,&y);
				tmp.push_back({x,y});
			}
			for (int i=0;i<m;i++) {
				lines.push_back(Line(tmp[i],tmp[(i+1)%m]));
			}
		}
		vector<Point> result;
		HPI(lines,result);
		printf("%0.3f\n",poly_area(result));
	}
	return 0;
}

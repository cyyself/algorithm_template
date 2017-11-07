struct Matrix {
	long long num[105][105];
	int h,w;//高，宽 
	Matrix() {
		memset(num,0,sizeof(num));
	}
	Matrix (int _h,int _w) {
		h = _h;
		w = _w;
		memset(num,0,sizeof(num));
	}
	Matrix operator * (const Matrix &b) {
		//https://zh.wikipedia.org/wiki/%E7%9F%A9%E9%99%A3%E4%B9%98%E6%B3%95
		//当调用c = a * b时，c就是返回结果，其自身是a，b就是b
		//注意，不能用*= 
		//需要确保a.w == b.h 
		Matrix tmp(h,b.w);
		for (int i=0;i<h;i++)
			for (int j=0;j<b.w;j++) {
				for (int k=0;k < w;k++) {
					tmp.num[i][j] += (num[i][k] * b.num[k][j]);
					tmp.num[i][j] %= 1000000007;
				}
			}
		return tmp;
	}
	Matrix pow(long long b) {
		Matrix a(h,w);
		Matrix tmp(h,w);
		memcpy(a.num,num,sizeof(num));
		if (b == 1) return a;
		tmp = a.pow(b/2);
		if (b % 2 == 1) return (tmp * tmp) * a;
		else return tmp * tmp;
	}
};

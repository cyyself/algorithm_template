const double pi = acos((double)-1);
const int maxn = 1<<22;//2e6
namespace fft {
	complex <double> omega[maxn];
	void init(int n) {
		for (int i=0;i<n;i++) {
			omega[i] = complex<double>(cos(2*pi*i/n),sin(2*pi*i/n));
		}
	}
	void transform(complex<double> *a,int n,bool inv) {
		int k = 0;
		while ((1 << k) < n) k ++;
		for (int i=0;i<n;i++) {
			int t = 0;
			for (int j=0;j<k;j++) if (i & (1 << j)) t |= (1 << (k - j - 1));
			if (i < t) swap(a[i],a[t]);
		}
		for (int l=2;l<=n;l*=2) {
			int m = l / 2;
			for (auto *p=a;p < a + n;p += l) {
				for (int i=0;i<m;i++) {
					complex<double> t = (inv?conj(omega[n/l*i]):omega[n/l*i]) * p[m+i];
					p[m+i] = p[i] - t;
					p[i] += t;
				}
			}
		}
	}
	void dft(complex<double> *a,int n) {
		transform(a,n,false);
	}
	void idft(complex<double> *a,int n) {
		transform(a,n,true);
		for (int i=0;i<n;i++) a[i] /= n;
	}
}
struct poly: public vector <int> {
	friend poly operator * (const poly &a,const poly &b) {
		int n = 1;
		while (n < a.size() + b.size()) n <<= 1;
		static complex <double> c1[maxn],c2[maxn];
		for (int i=0;i<a.size();i++) c1[i] = complex<double>(a[i],0);
		for (int i=a.size();i<n;i++) c1[i] = complex<double>(0,0);
		for (int i=0;i<b.size();i++) c2[i] = complex<double>(b[i],0);
		for (int i=b.size();i<n;i++) c2[i] = complex<double>(0,0);
		fft::init(n);
		fft::dft(c1,n);
		fft::dft(c2,n);
		for (int i=0;i<n;i++) c1[i] *= c2[i];
		fft::idft(c1,n);
		poly res;
		for (int i=0;i<a.size()+b.size()-1;i++) res.push_back((int)floor(c1[i].real()+0.5));
		return res;
	}
};

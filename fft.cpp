//attribution cp-algorithms

namespace fft {
	const int maxn = 1 << 21, magic = 500;

	typedef double ftype;
	typedef complex<ftype> point;

	point w[maxn];
	const ftype pi = acos(-1);
	bool initiated = 0;
	void init() {
		if(!initiated) {
			for(int i = 1; i < maxn; i *= 2) {
				for(int j = 0; j < i; j++) {
					w[i + j] = polar(ftype(1), pi * j / i);
				}
			}
			initiated = 1;
		}
	}
	template<typename T>
	void fft(T *in, point *out, int n, int k = 1) {
		if(n == 1) {
			*out = *in;
		} else {
			n /= 2;
			fft(in, out, n, 2 * k);
			fft(in + k, out + n, n, 2 * k);
			for(int i = 0; i < n; i++) {
				auto t = out[i + n] * w[i + n];
				out[i + n] = out[i] - t;
				out[i] += t;
			}
		}
	}
	
	template<typename T>
	void mul_slow(vector<T> &a, const vector<T> &b) {
		vector<T> res(a.size() + b.size() - 1);
		for(size_t i = 0; i < a.size(); i++) {
			for(size_t j = 0; j < b.size(); j++) {
				res[i + j] += a[i] * b[j];
			}
		}
		a = res;
	}
	
	
	template<typename T>
	void mul(vector<T> &a, const vector<T> &b) {
		init();
		if(min(a.size(), b.size()) < magic) {
			mul_slow(a, b);
			return;
		}
		
		static const int shift = 15, mask = (1 << shift) - 1;
		size_t n = a.size() + b.size() - 1;
		while(__builtin_popcount(n) != 1) {
			n++;
		}
		a.resize(n);
		static point A[maxn], B[maxn];
		static point C[maxn], D[maxn];
		for(size_t i = 0; i < n; i++) {
			A[i] = point(a[i] & mask, a[i] >> shift);
			if(i < b.size()) {
				B[i] = point(b[i] & mask, b[i] >> shift);
			} else {
				B[i] = 0;
			}
		}
		fft(A, C, n); fft(B, D, n);
		for(size_t i = 0; i < n; i++) {
			point c0 = C[i] + conj(C[(n - i) % n]);
			point c1 = C[i] - conj(C[(n - i) % n]);
			point d0 = D[i] + conj(D[(n - i) % n]);
			point d1 = D[i] - conj(D[(n - i) % n]);
			A[i] = c0 * d0 - point(0, 1) * c1 * d1;
			B[i] = c0 * d1 + d0 * c1;
		}
		fft(A, C, n); fft(B, D, n);
		reverse(C + 1, C + n);
		reverse(D + 1, D + n);
		int t = 4 * n;
		for(size_t i = 0; i < n; i++) {
			int64_t A0 = llround(real(C[i]) / t);
			T A1 = llround(imag(D[i]) / t);
			T A2 = llround(imag(C[i]) / t);
			a[i] = A0 + (A1 << shift) + (A2 << 2 * shift);
		}
		return;
	}
}
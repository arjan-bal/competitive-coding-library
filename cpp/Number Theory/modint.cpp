// attributaion: cp-algorithms.com
template<typename T>
T bpow(T x, int64_t n) {
	return n ? n % 2 ? x * bpow(x, n - 1) : bpow(x * x, n / 2) : T(1);
}

template<int m>
struct modular {
	int64_t r;
	modular() : r(0) {}
	modular(int64_t rr) : r(rr) {if(abs(r) >= m) r %= m; if(r < 0) r += m;}
	modular inv() const {return bpow(*this, m - 2);}
	modular operator * (const modular &t) const {return (r * t.r) % m;}
	modular operator / (const modular &t) const {return *this * t.inv();}
	modular operator += (const modular &t) {r += t.r; if(r >= m) r -= m; return *this;}
	modular operator -= (const modular &t) {r -= t.r; if(r < 0) r += m; return *this;}
	modular operator + (const modular &t) const {return modular(*this) += t;}
	modular operator - (const modular &t) const {return modular(*this) -= t;}
	modular operator *= (const modular &t) {return *this = *this * t;}
	modular operator /= (const modular &t) {return *this = *this / t;}
	
	bool operator == (const modular &t) const {return r == t.r;}
	bool operator != (const modular &t) const {return r != t.r;}
	
	operator int64_t() const {return r;}
};
template<int T>
istream& operator >> (istream &in, modular<T> &x) {
	return in >> x.r;
}

const int mod = 1e9 + 7;

typedef modular<mod> modint;
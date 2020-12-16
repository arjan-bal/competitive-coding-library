// attributaion: cp-algorithms.com
template<typename T>
T bpow(T x, size_t n) {
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
 
vector<modint> fac, ifac;
 
void prefac(int N)
{
    fac.resize(N);
    ifac.resize(N);
	fac[0]=1;
	
    for (int i = 1; i < N; ++i) {
        fac[i] = modint(i) * fac[i-1];
    }
 
	ifac[N - 1] = fac[N-1].inv();
	for (int i = N - 2; i >= 0; --i) {
        ifac[i] = modint(i + 1) * ifac[i+1];
    }
}
 
modint npr(int n, int r)
{
	if (r > n)
		return 0;
	return fac[n] * ifac[n - r];
}
 
modint ncr(int n, int r)
{
	if (r > n)
		return 0;
	return npr(n, r) * ifac[r];
}
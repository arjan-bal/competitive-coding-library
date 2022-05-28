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
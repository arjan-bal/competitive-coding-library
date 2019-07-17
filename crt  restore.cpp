//attributation: https://www.hackerrank.com/rest/contests/w23/challenges/sasha-and-swaps-ii/hackers/ffao/download_solution
long long crt(const std::vector< std::pair<int, int> >& a, int mod) {
	long long res = 0;
	long long mult = 1;

	int SZ = a.size();
	std::vector<int> x(SZ);
	for (int i = 0; i<SZ; ++i) {
		x[i] = a[i].first;
		for (int j = 0; j<i; ++j) {
			long long cur = (x[i] - x[j]) * 1ll * modInv(a[j].second,a[i].second);
			x[i] = (int)(cur % a[i].second);
			if (x[i] < 0) x[i] += a[i].second;
		}
		res = (res + mult * 1ll * x[i]);
		mult = (mult * 1ll * a[i].second);
		if (mod != -1) {
			res %= mod;
			mult %= mod;
		}
	}

	return res;
}
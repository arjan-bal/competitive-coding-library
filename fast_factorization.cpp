namespace ffac{
	long double op = 0.0;
	int p = 0;
	bool first_run=1;
	const int base[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

	//taken from cp-algorithms.com

	const int N1=1e6;

	vector<int> lp(N1+1, 0), prime;

	void seive()
	{
	    for(int i=2; i<=N1; ++i){
	        if(lp[i]==0){
	            lp[i]=i;
	            prime.push_back(i);
	        }
	        for(auto j:prime){
	            if(j>lp[i] || i*j>N1) break;
	            lp[i*j]=j;
	        }
	    }
	}


	inline ll mul(ll a, ll b, ll MOD)
	{
	    if ((MOD < 3037000500LL))
	        return ((a * b) % MOD);
	    long double res = a;
	    res *= b;
	    ll c = (ll)(res * op);
	    a *= b;
	    a -= c * MOD;
	    if (a >= MOD) a -= MOD;
	    if (a < 0) a += MOD;
	    return a;
	}

	inline ll expo(ll x, ll n, ll m)
	{
	    ll res = 1;
	    while (n){
	        if (n & 1) res = mul(res, x, m);
	        x = mul(x, x, m);
	        n >>= 1;
	    }
	    return (res % m);
	}

	inline bool miller_rabin(ll p)
	{
	    if (p <= N1) return (lp[p]==p);
	    if ((p + 1) & 1) return false;
	    for (int i = 1; i < 50; i++){
	        if (!(p % prime[i])) return false;
	    }

	    ll a, m, x, s = p - 1, y = p - 1;
	    op = (long double)1 / p, s = s >> __builtin_ctzll(s);

	    for (int i = 0; i < 7; i++){
	        x = s, a = (base[i] % y) + 1;
	        m = expo(a, x, p);
	        while ((x != y) && (m != 1) && (m != y))
	            m = mul(m, m, p), x <<= 1;
	        if ((m != y) && !(x & 1)) return false;
	    }
	    return true;
	}

	inline ll rho(ll n)
	{
	    if(n==1 or miller_rabin(n)) return n;
	    if(n%2==0) return 2;
	    ll x = (rand()*rand())%(n-2)+2;
	    ll y = x;
	    ll c = (rand()*rand())%(n-1)+1;
	    ll d = 1;
	    while(d==1){
	        x = (expo(x,2,n)+c+n)%n;
	        y = (expo(y,2,n)+c+n)%n;
	        y = (expo(y,2,n)+c+n)%n;
	        d = __gcd(abs(x-y),n);
	        if(d==n) return rho(n);
	    }
	    return d;
	}

	//returns prime factorisation in the form {p1, f1} pairs, n=product(pi^fi)
	inline vector<pii> getfac(ll n)
	{
	    if(first_run){
	        seive();
	        first_run=0;
	    }
	    ll x=n;
	    ll dv = n;
	    vector<ll> prmDiv;
	    
	    while(n!=1){
	        dv = rho(n);
	        n = n/dv;
	        if(miller_rabin(dv)){
	            prmDiv.push_back(dv);
	        }
	        else{
	            for(ll i=2; i*i<=dv; i++){
	                if(dv%i==0){
	                    prmDiv.push_back(i);
	                    while(dv%i==0)
	                        dv/=i;
	                }
	            }
	            if(dv>1) prmDiv.push_back(dv);
	        }
	    }
	    
	    sort(all(prmDiv));
	    prmDiv.erase( unique(all(prmDiv)), prmDiv.end());
	    vector<pii> fac;

	    for(auto it : prmDiv){
	        fac.pb({it, 0});
	        while(x%it==0)
	            ++fac.back().ss, x/=it;
	    }
	    return fac;
	}
}
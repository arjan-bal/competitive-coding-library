mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
/*
	taken from: https://discuss.codechef.com/t/mdswin-editorial/44120
	miller_rabin to quickly check if a number is prime
	SPRP is a proven list of witnesses that can check prime for
	number upto 1e18
*/

inline ll mul(ll a, ll b, ll mod) 
{ 
	a %= mod;
	b %= mod;
	if(mod < 2e9) return a*b%mod;
    ll res = 0; 
    while (b > 0){ 
        if (b % 2 == 1) res = (res + a) % mod; 
        a = (a * 2) % mod; 
        b /= 2; 
    }  
    return res % mod; 
} 

inline ll power(ll x, ll n, ll m)
{
    ll res = 1;
    while (n){
        if (n & 1) res = mul(res, x, m);
        x = mul(x, x, m);
        n >>= 1;
    }
    return (res % m);
}

ll SPRP[7] = {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL};
bool miller_rabin(ll p, int t = 7)		//t = 7 for SPRP base
{
    if(p < 4) return (p > 1);
    if(!(p & 1LL)) return false;
    ll x = p - 1;
    int e = __builtin_ctzll(x);
    x >>= e;
    while(t--)
    {
        //ll witness = (rng() % (p-3)) + 2;	//Using random witness
        ll witness = SPRP[t];
        witness = power(witness%p, x, p);
        if(witness <= 1) continue;
        for(int i = 0; i<e && witness != p-1; i++)
            witness = mul(witness, witness, p);
        if(witness != p-1) return false;
    }
    return true;
}

namespace ffac{
	bool first_run=1;
	
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

	inline ll rho(ll n)
	{
	    if(n==1 or miller_rabin(n)) return n;
	    if(n%2==0) return 2;
	    ll x = rng()%(n-2)+2;
	    ll y = x;
	    ll c = rng()%(n-1)+1;
	    ll d = 1;
	    while(d==1){
	        x = (power(x,2,n)+c+n)%n;
	        y = (power(y,2,n)+c+n)%n;
	        y = (power(y,2,n)+c+n)%n;
	        d = __gcd(abs(x-y),n);
	        if(d==n) return rho(n);
	    }
	    return d;
	}

	//returns prime factors
	inline vll factorize(ll n)
	{
	    if(first_run){
	        seive();
	        first_run=0;
	    }	    
	    ll dv = n;
	    vector<ll> prmDiv;	    
	    while(n>1){
	    	bool p=0;
	        if(n<=N1) dv=lp[n], p=1;
	        else dv = rho(n);
	        n = n/dv;
	        if(p || miller_rabin(dv)) prmDiv.push_back(dv);
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
	    return prmDiv;
	}
}
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
	if(mod <= 2e9) return a*b%mod;
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
    while(t--){
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
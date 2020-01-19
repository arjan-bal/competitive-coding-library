/*
	taken from: https://discuss.codechef.com/t/mdswin-editorial/44120
	Rabin_miller to quickly check if a number is prime
	SPRP is a proven list of witnesses that can check prime for
	number upto 1e18
*/

ll SPRP[7] = {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL};
bool RabinMiller(ll p, int t = 7)		//t = 7 for SPRP base
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
            witness = (witness * witness) % p;
        if(witness != p-1) return false;
    }
    return true;
}
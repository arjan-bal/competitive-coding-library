ll power(ll x, ll y, ll m)
{
    if (y==0)    return 1;
    ll p=power(x, y/2, m)%m;
    p=(p*p)%m; 
    return (y%2==0)?p:(x*p)%m;
}

ll modInverse(ll a, ll m)
{
    return power(a, m-2, m);
}

//return x s.t a^x=b mod(prime)
int discreteLog(int a, int b, int mod)
{
	if(b==1) return 0;
	int middle=sqrt(mod)+1;
	
	unordered_map<int, int> rem;
	rem.reserve(middle);
	rem.max_load_factor(.25);

	int inv=modInverse(a, mod);
	int cur=1;

	for(int r=0; r<middle; ++r){
		rem[1LL*cur*b%mod]=r;
		cur=1LL*cur*inv%mod;
	}

	int po=power(a, middle, mod);
	cur=1;

	for(int p=0; p<=middle; ++p){
		if(rem.count(cur)) return p*middle+rem[cur];
		cur=1LL*cur*po%mod;
	}

	return -1;
}
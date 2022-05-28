ll power(ll x, ll y, ll m)
{
    if (y==0)    return 1;
    ll p=power(x, y/2, m)%m;
    p=(p*p)%m; 
    return (y%2==0)?p:(x*p)%m;
}

int jacobi(ll n, ll k)
{
    assert(k>0 && k%2==1);
    n%=k;
    int sig=1;
    while(n){
        int r=k%8;
        while(n%2==0){
            n/=2;
            if(r==3 || r==5) sig=-sig;
        }
        swap(n, k);
        if(n%4==k%4 && k%4==3) sig=-sig;
        n%=k;
    }
    if(k==1) return sig;
    return 0;
}

bool isprime(ll p)
{
	if(p==2) return 1;
	if(p%2==0 || p<=1) return 0;
	int itr=10;
	while(itr--){
		ll a=1LL*rand()*rand()%p;
		while(!a) a=1LL*rand()*rand()%p;
		if(__gcd(a, p)!=1) return 0;
		ll j=jacobi(a, p);
		if(!j) return 0;
		if(j<0) j+=p;
		if(power(a, (p>>1), p)!=j) return 0;
	}
	return 1;
}
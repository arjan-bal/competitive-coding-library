ll power(ll x, ll y, ll m)
{
    if (y==0) return 1;
    ll p=power(x, y>>1, m)%m;
    p=p*p%m; 
    return (y&1)?(x*p)%m:p;
}
ll modInverse(ll a, ll m)
{ return power(a, m-2, m); }

/*
        creates rolling hash on vector with elements in [1, 28]
        Query hash of segment [l, r]
        To check if palindrome, compare query(l, r)==query(l, r, 1)
*/

struct rollingHash{
	const int mod=1000000459;
	int n;
	vi hsh[2];
	vll ip29, p29;

	void pre(vi &vec, vi &hsh)
	{
		hsh.resize(n);
		hsh[0]=vec[0];
	    for(int i=1; i<n; hsh[i]=(hsh[i-1]+p29[i]*vec[i])%mod, ++i);
	}

	rollingHash(vi vec, bool rev=0)
	{
		n=vec.size();
		ip29.resize(n);	p29.resize(n);
		p29[0]=1;

		for(int i=1; i<n; p29[i]=29*p29[i-1]%mod, ++i);	    
	    ip29[n-1]=modInverse(p29[n-1], mod);
	    for(int i=n-2; i>=0; ip29[i]=29*ip29[i+1]%mod, --i);

	    pre(vec, hsh[0]);	    
	    if(!rev) return ;	    
	    reverse(all(vec));
	    pre(vec, hsh[1]);
	    reverse(all(hsh[1]));
	}

	int query(int l, int r, bool rev=0)
	{	
		if(!rev) return l ? (hsh[0][r]-hsh[0][l-1]+mod)*ip29[l]%mod : hsh[0][r];
	    return r<n-1 ?  (hsh[1][l]-hsh[1][r+1]+mod)*ip29[n-1-r]%mod : hsh[1][l];
	}
};
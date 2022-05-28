ll gex(ll a, ll b, ll &x, ll &y)
{
	if(!a){
		x=0;
		y=1;
		return b;
	}

	ll x1, y1;
	ll g=gex(b%a, a, x1, y1);
	x=y1-(b/a)*x1;
	y=x1;
	return g;
}

ll inv(ll a, ll m)
{
	ll x, y;
	ll g=gex(a, m, x, y);
	assert(g==1);
	return (x%m+m)%m;
}

ll combine(vector<int> &num, vector<int> &rem)
{
    ll prod=1;
    for(auto i:num) prod*=i;   
    int n=rem.size();
    ll ans=0, pp;
    for(int i=0; i<n; ++i){
        pp=prod/num[i];
        ans=(ans+rem[i]*pp*inv(pp, num[i]))%prod;
    }
    return ans;
}
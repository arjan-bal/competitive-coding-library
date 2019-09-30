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
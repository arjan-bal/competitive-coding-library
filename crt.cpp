ll gex(ll a, ll b, ll &x, ll &y)
{
	if(b==0){
		x=1;
		y=0;
		return a;
	}

	ll x1, y1;
	ll g=gex(b, a%b, x1, y1);
	x=y1;
	y=x1-(a/b)*y1;
	return g;
}

ll inv(ll a, ll b)
{
	ll x1, y1;
	ll g=gex(b, a%b, x1, y1);
	return (y1+b)%b;
}

ll combine(vector<int> &num, vector<int> &rem)
{

    ll prod=1;
    for(auto i:num) prod*=i;   
    int n=rem.size();
    ll ans=0, pp;
    for(int i=0; i<n; ++i){
        pp=prod/num[i];
        ans+=rem[i]*pp*inv(pp, num[i]);
        ans%=prod;
    }
    return ans;
}
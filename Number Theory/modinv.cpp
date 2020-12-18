ll power(ll x, ll y, ll m)
{
    if(!y) return 1;
    ll p=power(x, y>>1, m)%m;
    p=p*p%m; 
    return (y&1)?(x*p)%m:p;
}
ll modInverse(ll a, ll m)
{ return power(a, m-2, m); }
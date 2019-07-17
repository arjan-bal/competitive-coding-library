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
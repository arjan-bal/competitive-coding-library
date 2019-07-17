ll xor3(ll a, ll b)
{
    ll ans=0, three=1, trm;
    while(a|b){
        trm=(a+b)%3;
        ans+=trm*three;
        three*=3;
        a/=3;
        b/=3;
    }
    return ans%p2;
}

ll dxor3(ll a, ll b)
{
    ll ans=0, three=1, trm;
    while(a|b){
        trm=((a-b)%3+3)%3;
        ans+=trm*three;
        three*=3;
        a/=3;
        b/=3;
    }
    return ans%p2;
}
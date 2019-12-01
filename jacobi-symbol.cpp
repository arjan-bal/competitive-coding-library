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
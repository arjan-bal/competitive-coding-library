void precal()
{
    p27[0]=1;
    for(int i=1; i<N; ++i){
        p27[i]=p27[i-1]*27LL%mod;
    }

    fhash[0]=(t[0]-'a'+1);
    for(int i=1; i<n2; ++i){
        fhash[i]=1LL*p27[i]*(t[i]-'a'+1)%mod;
        add(fhash[i], fhash[i-1]);
    }

    ip27[N-1]=modInverse(p27[N-1], mod);

    for(int i=N-2; i>=0; --i){
        ip27[i]=27LL*ip27[i+1]%mod;
    }

    return ;
}

int calhash(int l, int r)
{
    if(l==0) return fhash[r];
    int ans=fhash[r];
    sub(ans, fhash[l-1]);
    return 1LL*ans*ip27[l]%mod;
}
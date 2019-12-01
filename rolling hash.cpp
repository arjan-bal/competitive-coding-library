const int N=1e6+1, mod=1000000459;
ll p29[N], ip29[N];
int n;

// vec is of size n, and has numbers in [1, 28]
// if string, can replace vec[i] with s[i]-'a'+1

void precal()
{
    fhash[0]=vec[0];
    p29[0]=1;

    for(int i=1; i<n; ++i){
    	p29[i]=p29[i-1]*29%mod;
        fhash[i]=(fhash[i-1]+p29[i]*vec[i])%mod;
    }

    ip29[n-1]=modInverse(p29[n-1], mod);

    for(int i=n-2; i>=0; --i)
        ip29[i]=29*ip29[i+1]%mod;
}

int calhash(int l, int r)
{
    if(l==0) return fhash[r];
    int ans=fhash[r]-fhash[l-1];
    if(ans<0) ans+=mod;
    return ans*ip29[l]%mod;
}
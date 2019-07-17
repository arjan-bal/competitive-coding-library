const ll mod = 100003;

const ll mod0 = 1484783617;
const ll root0 = 270076864;
const ll iroot0 = 1400602088;

const ll mod1 = 1572864001;
const ll root1 = 682289494;
const ll iroot1 = 1238769373;

const ll root_pw = 1 << 22;

#define Imod0mod1 898779447LL
#define Imod1mod0 636335819LL

#define chinese(a1,m1,a2,m2) ((a1 * I##m2##m1 % m1 * m2 + a2 * I##m1##m2 % m2 * m1) % (m1 * m2))

ll power(ll x, ll y, ll m)
{
    if (y==0)    return 1;
    ll p=power(x, y/2, m)%m;
    p=(p*p)%m; 
    return (y%2==0)?p:(x*p)%m;
}

ll inverse(ll a, ll m)
{
     return power(a, m-2, m);
}

void fft(vector<ll> & a, bool invert, ll mod, ll root, ll root_1) {
    ll n = a.size();

    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (ll len = 2; len <= n; len <<= 1) {
        ll wlen = invert ? root_1 : root;
        for (ll i = len; i < root_pw; i <<= 1)
            wlen = (ll)(1LL * wlen * wlen % mod);

        for (ll i = 0; i < n; i += len) {
            ll w = 1;
            for (ll j = 0; j < len / 2; j++) {
                ll u = a[i+j], v = (ll)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (ll)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        ll n_1 = inverse(n, mod);
        for (ll & x : a)
            x = (ll)(1LL * x * n_1 % mod);
    }
}

vector<ll> multiply(vector<ll> a, vector<ll> b, ll mod, ll root, ll root_1) {

    fft(a, false, mod, root, root_1);
    fft(b, false, mod, root, root_1);
    ll n=a.size();
    for (ll i = 0; i < n; i++)
        a[i] = (1LL*a[i]*b[i])%mod;
    fft(a, true, mod, root, root_1);
    return a;
}

vector<ll> mul(vector<ll> a, vector<ll> b) {
    ll n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    a.resize(n, 0);
    b.resize(n, 0);

    vector<ll> c0=multiply(a, b, mod0, root0, iroot0);
    vector<ll> c1=multiply(a, b, mod1, root1, iroot1);
    vector<ll> c(n);
    fr(i, n){
		ll t = chinese(c0[i],mod0,c1[i],mod1);
        if (t < 0) t += 1LL*mod0*mod1;
        c[i] = t % mod;    	
    }
    return c;
}
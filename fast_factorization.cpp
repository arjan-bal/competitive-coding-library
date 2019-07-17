#define MAX 1000010
#define isprime(x) prm::miller_rabin(x)
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl


bitset <MAX> flag;
long double op = 0.0;
int p = 0, prime[78777];
const int base[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

void Sieve()
{
    int i, j, x;
    for (i = 3; i < MAX; i += 2)
        flag[i] = true;
    for (i = 3, flag[2] = true; (i * i) < MAX; i += 2)
    {
        if (flag[i])
        {
            for (j = (i * i), x = i << 1; j < MAX; j += x)
            {
                flag[j] = false;
            }
        }
    }

    for (i = 2; i < MAX; i++)
    {
        if (flag[i])
            prime[p++] = i;
    }
}


inline long long mul(long long a, long long b, long long MOD)
{
    if ((MOD < 3037000500LL))
        return ((a * b) % MOD);
    long double res = a;
    res *= b;
    long long c = (long long)(res * op);
    a *= b;
    a -= c * MOD;
    if (a >= MOD)
        a -= MOD;
    if (a < 0)
        a += MOD;
    return a;
}

inline long long expo(long long x, long long n, long long m)
{
    long long res = 1;

    while (n)
    {
        if (n & 1)
            res = mul(res, x, m);
        x = mul(x, x, m);
        n >>= 1;
    }

    return (res % m);
}

inline bool miller_rabin(long long p)
{
    if (p < MAX)
        return flag[p];
    if ((p + 1) & 1)
        return false;
    for (int i = 1; i < 50; i++)  /// basic iterations
    {
        if (!(p % prime[i]))
            return false;
    }

    long long a, m, x, s = p - 1, y = p - 1;
    op = (long double)1 / p, s = s >> __builtin_ctzll(s);

    for (int i = 0; i < 7; i++)
    {
        x = s, a = (base[i] % y) + 1;
        m = expo(a, x, p);
        while ((x != y) && (m != 1) && (m != y))
            m = mul(m, m, p), x <<= 1;
        if ((m != y) && !(x & 1))
            return false;
    }
    return true;
}

inline long long countdiv(long long n)
{
    int i, j, c;
    long long x, res = 1;
    for (i = 0; i < p; i++)
    {
        x = prime[i];
        if ((x * x * x) > n)
            break;

        c = 1;
        while (!(n % x))
            c++, n /= x;
        res *= c;
    }

    if (miller_rabin(n))
        res <<= 1;
    else if (n > 1)
    {
        x = sqrt((long double)0.95 + n); /// may be change to sqrtl() ?
        if ((x * x) == n && miller_rabin(x))
            res *= 3;
        else
            res <<= 2;
    }

    return res;
}
inline long long rho(long long n)
{
    if(n==1 or miller_rabin(n))
        return n;
    if(n%2==0)
        return 2;
    long long x = (rand()*rand())%(n-2)+2;
    long long y = x;
    long long c = (rand()*rand())%(n-1)+1;
    long long d = 1;
    while(d==1)
    {
        x = (expo(x,2,n)+c+n)%n;
        y = (expo(y,2,n)+c+n)%n;
        y = (expo(y,2,n)+c+n)%n;
        d = __gcd(abs(x-y),n);
        if(d==n)
            return rho(n);
    }
    return d;
}
inline void getfac(long long n)
{
    ll x=n;
    long long dv = n;
    vector<long long>prmDiv;
    /// start
    while(n!=1)
    {
        dv = rho(n);
        n = n/dv;
        if(miller_rabin(dv))
        {
            prmDiv.push_back(dv);
        }
        else
        {
            for(long long i=2; i*i<=dv; i++)
            {
                if(dv%i==0)
                {
                    prmDiv.push_back(i);
                    while(dv%i==0)
                    {
                        dv/=i;
                    }
                }
            }
            if(dv>1)
                prmDiv.push_back(dv);
        }
    }
    sort(prmDiv.begin(),prmDiv.end());
    //prnv(prmDiv);
    prmDiv.erase( unique( prmDiv.begin(), prmDiv.end() ), prmDiv.end() );
    for(auto it : prmDiv)
    {
        fac.pb({it, 0});
        while(x%it==0) ++fac.back().ss, x/=it;
    }
    return ;
}
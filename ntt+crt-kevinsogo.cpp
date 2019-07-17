#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define fo(i,a,b) dfo(int,i,a,b)
#define fr(i,n) dfr(int,i,n)
#define fe(i,a,b) dfe(int,i,a,b)
#define fq(i,n) dfq(int,i,n)
#define nfo(i,a,b) dfo(,i,a,b)
#define nfr(i,n) dfr(,i,n)
#define nfe(i,a,b) dfe(,i,a,b)
#define nfq(i,n) dfq(,i,n)
#define dfo(d,i,a,b) for (d i = (a); i < (b); i++)
#define dfr(d,i,n) dfo(d,i,0,n)
#define dfe(d,i,a,b) for (d i = (a); i <= (b); i++)
#define dfq(d,i,n) dfe(d,i,1,n)
#define ffo(i,a,b) dffo(int,i,a,b)
#define ffr(i,n) dffr(int,i,n)
#define ffe(i,a,b) dffe(int,i,a,b)
#define ffq(i,n) dffq(int,i,n)
#define nffo(i,a,b) dffo(,i,a,b)
#define nffr(i,n) dffr(,i,n)
#define nffe(i,a,b) dffe(,i,a,b)
#define nffq(i,n) dffq(,i,n)
#define dffo(d,i,a,b) for (d i = (b)-1; i >= (a); i--)
#define dffr(d,i,n) dffo(d,i,0,n)
#define dffe(d,i,a,b) for (d i = (b); i >= (a); i--)
#define dffq(d,i,n) dffe(d,i,1,n)
#define ll long long
#define alok(n,t) ((t*)malloc((n)*sizeof(t)))
#define pf printf
#define sf scanf
#define pln pf("\n")

#define mod 100003

#define MOD0 1484783617LL
#define ROOT0 270076864LL

#define MOD1 1572864001LL
#define ROOT1 682289494LL

#define IMOD0MOD1 898779447LL
#define IMOD1MOD0 636335819LL

#define SH 22

ll ROOTS0[SH+1];
ll ROOTS1[SH+1];
ll IROOTS0[SH+1];
ll IROOTS1[SH+1];

ll *A = alok(811111, ll);
ll *B = alok(811111, ll);
ll *C0 = alok(811111, ll);
ll *C1 = alok(811111, ll);

void fft(ll *A, int m, int ms, ll *rs, int MOD) {
    if (!ms) return;
    for (int k = 0; k < m; k++) C1[k] = A[k];
    int cc = 0;
    for (int k = 0; k < m; k += 2) A[cc++] = C1[k];
    for (int k = 1; k < m; k += 2) A[cc++] = C1[k];
    m >>= 1;
    ll r = rs[ms--];
    fft(A  ,m,ms,rs,MOD);
    fft(A+m,m,ms,rs,MOD);
    ll pr = 1;
    for (int k = 0, km = m; k < m; k++, km++) {
        ll fE = A[k], fO = A[km]*pr;
        A[k ] = (fE + fO) % MOD;
        A[km] = (fE - fO) % MOD;
        pr = pr * r % MOD;
    }  
}

ll x, y;
void egcd(ll a, ll b) {
    if (!b) {
        x = 1;
        y = 0;
    } else {
        egcd(b, a % b);
        ll t = x - (a / b) * y;
        x = y;
        y = t;
    }
}
ll inv(ll a, ll n) {
    egcd(a, n);
    return x % n;
}

#define chinese(a1,m1,a2,m2) ((a1 * I##m2##m1 % m1 * m2 + a2 * I##m1##m2 % m2 * m1) % (m1 * m2))

#define mulp(res,rc,C,MOD,ROOTS,IROOTS) do {\
    fft(A,res,rc,ROOTS,MOD);\
    fft(B,res,rc,ROOTS,MOD);\
    fr(i,res) A[i] = A[i] * B[i] % MOD;\
    fft(A,res,rc,IROOTS,MOD);\
    ll iv = inv(res,MOD);\
    fr(i,res) C[i] = A[i] * iv % MOD;\
} while (0)

int res;
ll *mul(ll *A_, int m, ll *B_, int n) {
    if (m <= 20000 / n) {
        res = m + n - 1;
        ll *C = alok(res, ll);
        fr(i,res) C[i] = 0;
        fr(i,m) fr(j,n) C[i + j] = (C[i + j] + A_[i] * B_[j]) % mod;
        return C;
    } else {
        res = m + n + 2;
        res |= res >> 1;
        res |= res >> 2;
        res |= res >> 4;
        res |= res >> 8;
        res |= res >> 16;
        res ^= res >> 1;
        res <<= 1;
        int rc = 0;
        while (1 << rc != res) rc++;
        fr(i,res) A[i] = B[i] = 0;
        fr(i,m) A[i] = A_[i];
        fr(i,n) B[i] = B_[i];
        mulp(res, rc, C0, MOD0, ROOTS0, IROOTS0);
        fr(i,res) A[i] = B[i] = 0;
        fr(i,m) A[i] = A_[i];
        fr(i,n) B[i] = B_[i];
        mulp(res, rc, C1, MOD1, ROOTS1, IROOTS1);
        res = m + n - 1;
        ll *C = alok(res, ll);
        fr(i,res) {
            ll t = chinese(C0[i],MOD0,C1[i],MOD1);
            if (t < 0) t += MOD0*MOD1;
            C[i] = t % mod;
        }
        return C;
    }
}
ll *V = alok(111111, ll);
ll *get(int i, int j) {
    if (j - i == 1) {
        res = 2;
        ll *t = alok(2, ll);
        t[0] = V[i];
        t[1] = 1;
        return t;
    }
    int k = i + j >> 1;
    ll *A = get(i,k);
    int m = res;
    ll *B = get(k,j);
    int n = res;
    return mul(A, m, B, n);
}
int main() {
    ROOTS0[SH] = ROOT0;
    ROOTS1[SH] = ROOT1;
    IROOTS0[SH] = inv(ROOT0,MOD0);
    IROOTS1[SH] = inv(ROOT1,MOD1);
    ffr(i,SH) {
        ROOTS0[i] = ROOTS0[i+1] * ROOTS0[i+1] % MOD0;
        ROOTS1[i] = ROOTS1[i+1] * ROOTS1[i+1] % MOD1;
        IROOTS0[i] = IROOTS0[i+1] * IROOTS0[i+1] % MOD0;
        IROOTS1[i] = IROOTS1[i+1] * IROOTS1[i+1] % MOD1;
    }
    int n;
    sf("%d", &n);
    fr(i,n) sf("%lld", V + i);
    ll *W = get(0,n);
    int q;
    sf("%d", &q);
    while (q--) {
        int k;
        sf("%d", &k);
        ll s = W[n-k] % mod;
        if (s < 0) s += mod;
        pf("%lld\n", s);
    }
}
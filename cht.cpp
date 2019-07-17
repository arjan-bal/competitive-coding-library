#include <bits/stdc++.h>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define eb emplace_back
#define lwr lower_bound
#define upr upper_bound
#define ssort stable_sort
#define pq priority_queue
#define umap unordered_map
#define all(x) x.begin(),x.end()
#define clr(a,b) memset(a,b,sizeof a)
#define fr(i,n) for(int i=0; i<n;++i)
#define fr1(i,n) for(int i=1; i<=n; ++i)
#define precise(x) cout<<fixed<<setprecision(x)
#define prn(x) cout<<x<<"\n"
#define prn2(x, y) cout<<x<<" "<<y<<"\n"
#define prn3(x, y, z) cout<<x<<" "<<y<<" "<<z<<"\n"
#define prn4(x, y, z, a) cout<<x<<" "<<y<<" "<<z<<" "<<a<<"\n"

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd; 
typedef vector<int> vi;
typedef vector<long> vl;
typedef vector<char> vc;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<double> vd;
typedef vector<string> vs;
typedef vector<pii> vpii;
typedef vector<pil> vpil;
typedef vector<pli> vpli;
typedef vector<pll> vpll;

/*
for autocomplete
continue
*/

int n;

const int N=3*1e5;

ll q[N], a[N], b[N], r[N], d[N], mod=1e9+7, inf=1e18;

int B, en;

typedef pll line;

line arr[N];

vector<line> hull;

void prnhull()
{
    for(auto i:hull) prn2(i.ff, i.ss);
        cout<<"\n";
}

ll val(line l, ll x) { return l.ff*x+l.ss; }

double ovrtake(line l1, line l2)
{
    double num=l2.ss-l1.ss, den=l1.ff-l2.ff;
    return num/den;
}

void add_line(line l)
{
    int n;
    while((n=hull.size())>=2)
        if(ovrtake(l, hull[n-2])<=ovrtake(hull[n-1], hull[n-2])) hull.ppb();
        else break;
    hull.pb(l);
    return ;
}

void build(int st)
{
    hull.clear();
    en=min(st+B, n);
    for(int i=n-1; i>=en; --i) add_line(arr[i]);
}

ll get(ll x)
{
    if(hull.empty()) return inf;
    if(hull.size()==1) return val(hull[0], x);
    if(val(hull[0], x)<=val(hull[1], x)) return val(hull[0], x);
    int n=hull.size();
    if(val(hull[n-1], x)<=val(hull[n-2], x)) return val(hull[n-1], x);
    int en=n-2, st=1, mid;
    ll v1;
    while(st<=en){
        mid=(st+en)/2, v1=val(hull[mid], x);
        if(v1<=val(hull[mid-1], x))
            if(v1<=val(hull[mid+1], x)) return v1;
            else st=mid+1;
        else en=mid-1;
    }
    return v1;
}

ll solve(int idx, ll pt)
{
    ll bst=inf;
    for(int i=idx; i<en; ++i){
        bst=min(bst, val(arr[i], pt));
    }
    return min(bst, get(pt));
}

int main()
{
    freopen("in.txt" , "r" , stdin) ;
    //freopen("out.txt" , "w" , stdout) ;
    ios_base::sync_with_stdio(false);
    cin>>n;

    fr(i, n){
        cin>>q[i]>>a[i]>>b[i]>>r[i]>>d[i];
        arr[i].ff=i;
        arr[i].ss=r[i];
    }

    B=sqrt(n+1);

    ll ans=0;

    fr(i, n){
        if(i%B==0){
            build(i);
        }

        ll sp=q[i]+i*d[i]-solve(i, d[i]);
        ll k=(sp-a[i])/b[i];
        if(k<=0) continue;
        k%=mod;
        ll trm=(sp-a[i])%mod;
        ans+=k*trm%mod;
        if(ans>=mod) ans-=mod; 
        trm=((k*(k+1))/2)%mod;
        trm=trm*b[i]%mod;
        ans-=trm;
        if(ans<0) ans+=mod;
    }

    cout<<ans;

    return 0;
}
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

const int N=21;

int dp[1<<N][N];

int arr[1<<N];

int neg(int mask)
{
    fr(i, N){
        mask^=(1<<i);
    }
    return mask;
}

int cal(int mask, int idx)
{
    if(idx<0) return arr[mask];
    if(dp[mask][idx]!=-1) return dp[mask][idx];
    int ans=cal(mask, idx-1);
    if((mask>>idx)&1) ans+=(((1<<idx)^mask), idx-1);
    return dp[mask][idx]=ans; 
}

void solve()
{
    clr(dp, -1);
    clr(arr, 0);
    int n;
    cin>>n;

    fr(i, n){
        int x;
        cin>>x;
        ++arr[x];
    }

    ll ans=0;

    fr(i, (1<<N)){
        ans+=cal(neg(i), N-1);
    }

    cout<<ans<<"\n";
}

int main()
{
    freopen("in.txt" , "r" , stdin) ;
    //freopen("out.txt" , "w" , stdout) ;
    ios_base::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define mp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define ppb(x) pop_back(x)
#define ppf(x) pop_front(x)
#define clr(a,b) memset(a,b,sizeof a)
#define x first
#define y second
#define umap unordered_map
#define fr(i,n) for(int i=0;i<n;++i)
#define lwr(x) lower_bound(x)
#define upr(x) upper_bound(x)
#define priority_queue pq

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long, int> pli;
typedef pair<int, long> pil;
typedef pair<long, long> pll;
typedef vector<int> vi;
typedef vector<long> vl;
typedef vector<char> vc;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<double> vd;

/*primes*/
//ll p1=1e6+3, p2=1616161, p3=3959297, p4=7393931;
//freopen("in.txt" , "r" , stdin) ;
//freopen("out.txt" , "w" , stdout) ;

typedef pair<double, double> pt;

vector<pt> Sx;

struct compare_y{
	bool operator()(const pt &p1, const pt &p2)
	{
		if(p1.y!=p2.y) return p1.y<p2.y;
		return p1.x<p2.x;
	}
};

double dist(pt p1, pt p2)
{
	return sqrtl((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

int main()
{
    ios_base::sync_with_stdio(false);
    freopen("in.txt" , "r" , stdin) ;
    int n;
    double inf=1e16;
    cin>>n;
    Sx.resize(n);
    fr(i, n){
    	cin>>Sx[i].x>>Sx[i].y;
    }

    sort(all(Sx));
    set<pt, compare_y> Sy;
    double ans=inf;
    int tail=0;

    for(int i=0; i<n; ++i){

    	while(Sx[i].x-Sx[tail].x>=ans){
    		Sy.erase(Sx[tail]);
    		++tail;
    	}

    	auto it1=Sy.lwr(mp(-inf, Sx[i].y-ans));
    	auto it2=Sy.lwr(mp(-inf, Sx[i].y+ans));
    	while(it1!=it2){
    		ans=min(ans, dist(*it1, Sx[i]));
    		++it1;
    	}
    	Sy.insert(Sx[i]);
    }

    cout<<ans;

    return 0;
}
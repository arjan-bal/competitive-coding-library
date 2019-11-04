/*
Author: Arjan Singh Bal, IIITM Gwalior
"Everything in this world is magic, except to the magician"
*/

#include                        <bits/stdc++.h>
#ifdef LOCAL
#include                        "pprint.hpp"
#endif

using namespace std;

template <typename Arg1>
void prn(Arg1&& arg1)
{
    cout<<arg1<<"\n";
}
template <typename Arg1, typename... Args>
void prn(Arg1&& arg1, Args&&... args)
{
    cout<<arg1<<" "; prn(args...);
}

template <typename Arg1>
void read(Arg1&& arg1)
{
    cin>>arg1 ;
}
template <typename Arg1, typename... Args>
void read(Arg1&& arg1, Args&&... args)
{
    cin>>arg1; read(args...);
}

#define ll                      long long
#define pii                     pair<int, int>
#define pli                     pair<ll, int>
#define pil                     pair<int, ll>
#define pll                     pair<ll, ll>
#define pdd                     pair<double, double>
#define vi                      vector<int>
#define vc                      vector<char>
#define vll                     vector<ll>
#define vb                      vector<bool>
#define vd                      vector<double>
#define vs                      vector<string>
#define ff                      first
#define ss                      second
#define pb                      push_back
#define eb                      emplace_back
#define ppb                     pop_back
#define pf                      push_front
#define ppf                     pop_front
#define vpii                    vector<pii>
#define umap                    unordered_map
#define all(x)                  x.begin(),x.end()
#define clr(a,b)                memset(a,b,sizeof a)
#define fr(i,n)                 for(int i=0; i<n;++i)
#define fr1(i,n)                for(int i=1; i<=n; ++i)
#define precise(x)              cout<<fixed<<setprecision(x)


int main()
{
	#ifdef LOCAL
	//freopen("in.txt" , "r" , stdin);
	//freopen("out.txt" , "w" , stdout);
	#else	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	#endif
	
	
	return 0;
}
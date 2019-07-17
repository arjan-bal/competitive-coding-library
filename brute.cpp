#include <bits/stdc++.h>
#define prn(x) for(auto ii:x) cout<<ii<<" "; cout<<"\n"
#define all(x) x.begin(), x.end()
#define ll long long
#define pb push_back
#define vi vector<int>
 
using namespace std;
 
const int N1=2000;
 
int arr[N1];
 
ll n, k;
int mod, num=0, den=0;
 
vector<vi> vec;

ll power(ll x, ll y, ll m)
{
    if (y==0)    return 1;
    ll p=power(x, y/2, m)%m;
    p=(p*p)%m; 
    return (y%2==0)?p:(x*p)%m;
}

ll modInverse(ll a, ll m)
{
    return power(a, m-2, m);
}

void inversion(vi &vec)
{
	int n=vec.size();
	for(int i=0; i<n; ++i){
		for(int j=i+1; j<n; ++j){
			if(vec[i]<=vec[j]) continue;
			++num;
			if(num==mod) num=0;
		}
	}
}
 
void cal(int idx){
	if(idx==n*k){
		for(auto &i:vec) inversion(i);
		++den;
		if(den==mod) den=0;
		return ;
	}
	int n1=vec.size();
	for(int i=0; i<n1; ++i){
		vec[i].pb(arr[idx%n]);
		cal(idx+1);
		vec[i].pop_back();
	}
	vec.pb({arr[idx%n]});
	cal(idx+1);
	vec.pop_back();
	return ;
}

int main()
{
	freopen("in.txt" , "r" , stdin) ;
	//freopen("out.txt" , "w" , stdout) ;
	//ios_base::sync_with_stdio(false); 
	cin>>n>>k>>mod;
	for(int i=0; i<n; ++i){
		cin>>arr[i];
	}
	cal(0);
	cout<<num*modInverse(den, mod)%mod;
	return 0;
}
#include 						<bits/stdc++.h>
#define ll						long long
#define pii 					pair<int, int>
#define pli 					pair<ll, int> 
#define pil 					pair<int, ll>
#define pll 					pair<ll, ll>
#define dub 					double
#define pdd						pair<dub, dub>
#define vi 						vector<int>
#define vl 						vector<long>
#define vc 						vector<cha>
#define vll 					vector<ll>
#define vb 						vector<bool>
#define vd 						vector<dub>
#define vs 						vector<string>
#define vpii 					vector<pii>
#define vpil 					vector<pil>
#define vpli 					vector<pli>
#define vpll 					vector<pll>
#define ff 						first
#define ss 						second
#define mp 						make_pair
#define pb 						push_back
#define ppb 					pop_back
#define pf 						push_front
#define ppf 					pop_front
#define eb 						emplace_back
#define lwr 					lower_bound
#define upr 					upper_bound
#define pq 						priority_queue
#define umap 					unordered_map
#define all(x) 					x.begin(),x.end()
#define clr(a,b) 				memset(a,b,sizeof a)
#define fr(i,n) 				for(int i=0; i<n;++i)
#define fr1(i,n) 				for(int i=1; i<=n; ++i)
#define precise(x) 				cout<<fixed<<setprecision(x)
#define prn(x) 					cout<<x<<"\n"
#define prn2(x, y) 				cout<<x<<" "<<y<<"\n"
#define prn3(x, y, z) 			cout<<x<<" "<<y<<" "<<z<<"\n"
#define prn4(x, y, z, a)		cout<<x<<" "<<y<<" "<<z<<" "<<a<<"\n"
#define prnv(x) for(auto zkw:x) cout<<zkw<<" "; cout<<"\n"

using namespace std;

//refference: https://discuss.codechef.com/questions/65993/rng-editorial

int mod=1e9+7;

vi neg(vi vec)
{
	int n=vec.size();
	for(int i=1; i<n; i+=2){
		vec[i]=mod-vec[i];
	}
	return vec;
}

vi mul(vi &v1, vi &v2)
{
	int n1=v1.size(), n2=v2.size();
	vi ret(n1+n2-1);
	fr(i, n1){
		fr(j, n2){
			ret[i+j]=(ret[i+j]+1LL*v1[i]*v2[j])%mod;
		}
	}
	return ret;
}

int cal(vi &rec, vi &base, int trm)
{
	int n=rec.size();
	if(trm<n) return base[trm];
	vi Q(n+1);
	Q[0]=1;

	for(int i=1; i<=n; ++i){
		Q[i]=mod-rec[i-1];
	}

	vi Q1=neg(Q);
	Q=mul(Q, Q1);

	base.resize(2*n);

	for(int i=n; i<2*n; ++i){
		for(int j=1; j<=n; ++j){
			base[i]=(base[i]+1LL*base[i-j]*rec[j-1])%mod;
		}
	}

	if(trm%2){
		for(int i=0; i<n; ++i){
			base[i]=base[2*i+1];
		}
	}
	else{
		for(int i=0; i<n; ++i){
			base[i]=base[2*i];
		}
	}

	base.resize(n);
	trm/=2;

	for(int i=0; i<n; ++i){
		rec[i]=mod-Q[2*i+2];
	}

	return cal(rec, base, trm);
}

int main()
{
	//freopen("in.txt" , "r" , stdin) ;
	//freopen("out.txt" , "w" , stdout) ;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	vi rec(2, 1);
	vi base={0, 1};
	cout<<cal(rec, base, 100)<<" ";
	return 0;
}
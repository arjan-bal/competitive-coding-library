#include <bits/stdc++.h>
#define pb push_back
#define all(x) x.begin(), x.end()
#define pii pair<int, int>

using namespace std;

int n;

const int N=1001;

bool arr[N][N];
int n1[N][N]={}, n0[N][N]={};

auto st=clock();

inline double ctime()
{
	return double(clock()-st)/CLOCKS_PER_SEC;
}

struct node{
	int i1, j1, i2, j2;
	bool operator==(node n2)
	{
		return (i1==n2.i1 && i2==n2.i2
			&& j1==n2.j1 && j2==n2.j2);
	}
};

node usd1[N][N];
vector<node> ans, vec;

node getRandom()
{
	int ht=rand()%(n/10)+1, wid=rand()%(n/8)+1;
	int ci=rand()%(n-ht)+1, cj=rand()%(n-wid)+1;
	return {ci, cj, ci+ht-1, cj+wid-1};
}

inline int area(node n1)
{
	return (n1.i2-n1.i1+1)*(n1.j2-n1.j1+1);
}

inline int score(node n)
{
	int a1=n1[n.i2][n.j2]-n1[n.i1-1][n.j2]-n1[n.i2][n.j1-1]+n1[n.i1-1][n.j1-1];
	int a0=n0[n.i2][n.j2]-n0[n.i1-1][n.j2]-n0[n.i2][n.j1-1]+n0[n.i1-1][n.j1-1];
	return abs(a1-a0);
}

double acceptanceProbability(double cScore, double nScore, double T)
{
	double x=(nScore-cScore)/T;
	return exp(x);
}

int cal(node n)
{
	vec.clear();
	int di=n.i2-n.i1+1, dj=n.j2-n.j1+1;
	for(auto i:ans){
		if(i==usd1[di][dj]) continue;
		if(n.i2<i.i1 || i.i2<n.i1) vec.pb(i);
		else if(n.j2<i.j1 || i.j2<n.j1) vec.pb(i);
	}
	vec.pb(n);
	int ret=0;
	for(auto i:vec){
		ret+=score(i);
	}
	return ret;
}

void apply(node n)
{
	int di=n.i2-n.i1+1, dj=n.j2-n.j1+1;
	usd1[di][dj]=n;
	ans=vec;
}

void anneal()
{
	double skip_time = ctime();
    double used_time = skip_time;
    double timeout=1.8;
    double max_temperature=1, min_temperature=1e-4;
	mt19937 rnd;
	uniform_real_distribution<double> dist(0, 1);
	int currentScore=0, itr=100;
	while(ctime()<timeout){

		double T=(1.0 - (used_time - skip_time) / (timeout - skip_time))
          * (max_temperature - min_temperature) + min_temperature;
		for(int ii=0; ii<itr; ++ii){
			node newSol=getRandom();
			int newScore=cal(newSol);
			double ap=acceptanceProbability(currentScore, newScore, T);
			if(ap>dist(rnd)){
				apply(newSol);
				currentScore=newScore;
			}
		}	
	}
	return ;
}

int main()
{
	//freopen("in.txt" , "r" , stdin) ;
	//freopen("out.txt" , "w" , stdout) ;
	ios_base::sync_with_stdio(false);
	//srand(236);
	cin>>n;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			cin>>arr[i][j];
			usd1[i][j]={0, 0, 0, 0};
		}
	}

	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			n1[i][j]=n1[i-1][j]+n1[i][j-1]-n1[i-1][j-1]+(arr[i][j]==1);
			n0[i][j]=n0[i-1][j]+n0[i][j-1]-n0[i-1][j-1]+(arr[i][j]==0);
		}
	}

	anneal();

	cout<<ans.size()<<"\n";
	for(auto i:ans){
		cout<<i.i1<<" "<<i.j1<<" "<<i.i2<<" "<<i.j2<<"\n";
	}

	//cerr<<"done!";

	return 0;
}
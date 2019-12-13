int n, m;
const int N=1e5+1;

vi a, b;
vi adj[N];
umap<int, bool> seen;

void init()
{
    a.resize(n, -1);
    b.resize(m+1, -1);
}

bool match(int idx)N
{
    for(auto i:adj[idx]){
        if(seen[i] || i==a[idx]) continue;
        seen[i]=1;
        if(b[i]==-1){
            b[i]=idx;
            a[idx]=i;
            return 1;
        }
        if(match(b[i])){
            b[i]=idx;
            a[idx]=i;
            return 1;
        }
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n>>m;
    init();
    int x;
    int ans=0;
    fr(i, n){
        cin>>x;
        for(int j=1; j*j<=x && j<=m; ++j){
            if(x%j) continue;
            adj[i].pb(j);
            if(x/j<=m) adj[i].pb(x/j);
        }
        if(x<=m) adj[i].pb(x);
        seen.clear();
        ans+=match(i);
    }
    cout<<ans;
    return 0;
}

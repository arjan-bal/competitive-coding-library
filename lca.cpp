const int level=20;

int par[N][level]={}, depth[N]={};

void precom(int n)
{
    int mid;
    for (int i=1; i<level; i++){
        for (int node=1; node<=n; ++node){
            mid=par[node][i-1];
            if (mid) par[node][i]=par[mid][i-1];
        }
    }
}
 
int lca(int u, int v)
{
    if (depth[v]<depth[u]) swap(u, v); 
    int diff=depth[v]-depth[u];
    for (int i=0; i<level; i++)
        if ((1<<i)&diff) v=par[v][i]; 
    if (u==v) return u;
    for (int i=level-1; i>=0; --i)
        if (par[u][i] != par[v][i]){
            u=par[u][i];
            v=par[v][i];
        } 
    return par[u][0];
}
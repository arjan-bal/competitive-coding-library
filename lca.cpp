const int level = 18;

int par[level][N]={}, depth[N]={};

void precom(int n)
{
    int mid;
    for (int i = 1; i < level; i++) {
        for (int node = 1; node <= n; ++node) {
            mid = par[i - 1][node];
            if (mid) par[i][node] = par[i - 1][mid];
        }
    }
}
 
int lca(int u, int v)
{
    if (depth[v] < depth[u]) swap(u, v);     
    int diff = depth[v] - depth[u];
    
    for (int i=0; i<level; i++)
        if ((1 << i) & diff) v = par[i][v]; 
    
    if (u==v) return u;
    
    for (int i = level - 1; i >= 0; --i)
        if (par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        } 
    return par[0][u];
}
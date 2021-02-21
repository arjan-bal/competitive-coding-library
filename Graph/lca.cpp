/*
    Expects vertices to be numbered [1, n]
    Expects adj list of correct size to be present globally
*/

const int level = 18;

int par[level][N] = {};
vector<int> depth;

void precom(int n)
{
	assert((1 << level) >= n);
    depth.assign(n + 1, 0);
    depth[1] = 0;
    queue<int> q;
    q.push(1);

    auto populate = [&](int cur, int p) {
        par[0][cur] = p;
        depth[cur] = depth[p] + 1;
        int prevParent = p;
        
        for (int j = 1; j < level && prevParent; ++j)
            prevParent = par[j][cur] = par[j - 1][prevParent];
    };

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto i : adj[cur]) {
            if (i == par[0][cur]) continue;
            populate(i, cur);
            q.push(i);
        }
    }
}
 
int lca(int u, int v)
{
    if (depth[v] < depth[u]) swap(u, v);     
    int diff = depth[v] - depth[u];
    
    for (int i = 0; i < level; i++)
        if ((1 << i) & diff) v = par[i][v]; 
    
    if (u == v) return u;
    
    for (int i = level - 1; i >= 0; --i)
        if (par[i][u] != par[i][v]) {
          u = par[i][u];
          v = par[i][v];
        } 
    return par[0][u];
}
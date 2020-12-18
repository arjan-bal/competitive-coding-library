// return empty vector if cycle detected
// assumes nodes numbered from [1, n], can change lims for [0, n] in for loop
vector<int> findTopSort(int n, vector<int> *adj)
{
    trace(n);
    vector<bool> inProcess(n + 1, 0), seen(n + 1, 0);
    vector<int> topo;
    bool cycleFound = 0;

    function<void(int)> dfs = [&](int cur) {
        inProcess[cur] = 1;
        for(auto child : adj[cur]) {
            if (seen[child]) {
                continue;
            } else if (inProcess[child]) {
                cycleFound = 1;
            } else {
                dfs(child);
            }
        }
        inProcess[cur] = 0;
        seen[cur] = 1;
        topo.pb(cur);
    };

    for (int i = 1; i <= n; ++i) {
        if (seen[i]) {
            continue;
        }
        dfs(i);
    }

    if (cycleFound) {
        topo.clear();
    }
    return topo;
}
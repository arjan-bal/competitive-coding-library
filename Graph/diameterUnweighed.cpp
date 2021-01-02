int findDiameter(int n, int &a, int &b)
{
    auto bfs = [&](int src, vi &dist) {
        queue<int> q;
        int cur = 1;
        q.push(src);
        dist[src] = 0;

        while (!q.empty()) {
            src = q.front();
            q.pop();
            for (auto i : adj[src]) {
                if (dist[i] != -1) continue;
                q.push(i);
                dist[i] = dist[src] + 1;
            }
        }
        return src;
    };
    
    vector<int> dist(n + 1, -1);
    a = bfs(1, dist);
    fill(all(dist), -1);
    b = bfs(a, dist);
    return dist[b];
}

int findDiameter(int n, int &a, int &b)
{
    queue<int> q;
    int cur = 1;
    vector<int> dist(n + 1, -1);
    q.push(cur);
    dist[cur] = 0;

    while (!q.empty()) {
        cur = q.front();
        q.pop();
        for (auto i : adj[cur]) {
            if (dist[i] != -1) {
                continue;
            }
            q.push(i);
            dist[i] = dist[cur] + 1;
        }
    }

    a = cur;
    fill(all(dist), -1);
    q.push(cur);
    dist[cur] = 0;

    while (!q.empty()) {
        cur = q.front();
        q.pop();
        for (auto i : adj[cur]) {
            if (dist[i] != -1) {
                continue;
            }
            q.push(i);
            dist[i] = dist[cur] + 1;
        }
    }
    b = cur;
    return dist[b];
}

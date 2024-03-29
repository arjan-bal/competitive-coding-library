Segtree st;

// taken from cp-algorithms.com
vector<int> parent, depth, heavy, head, pos, path;
int cur_pos;
vector<int> adj[N];
int n;

int dfs(int v) {
  int size = 1;
  int max_c_size = 0;
  for (int c : adj[v]) {
    if (c == parent[v])
      continue;
    parent[c] = v;
    depth[c] = depth[v] + 1;
    int c_size = dfs(c);
    size += c_size;
    if (c_size > max_c_size)
      max_c_size = c_size, heavy[v] = c;
  }
  return size;
}

void decompose(int v, int h) {
  head[v] = h;
	path.push_back(v);
  pos[v] = cur_pos++;
  if (heavy[v] != -1)
    decompose(heavy[v], h);
  for (int c : adj[v])
    if (c == parent[v] || c == heavy[v])
      continue;
    else
      decompose(c, c);
}



void init() {
  parent.resize(n + 1);
  depth.resize(n + 1);
  heavy.resize(n + 1, -1);
  head.resize(n + 1);
  pos.resize(n + 1);
  cur_pos = 0;

  dfs(1);
  decompose(1, 0);
}

// check return type for overflow
int query(int a, int b) {
  int res = 0;
  for (; head[a] != head[b]; b = parent[head[b]]) {
    if (depth[head[a]] > depth[head[b]])
      swap(a, b);
    int cur_heavy_path_max = st.query(pos[head[b]], pos[b]);
    res = max(res, cur_heavy_path_max);
  }
  if (depth[a] > depth[b]) swap(a, b);
  int last_heavy_path_max = st.query(pos[a], pos[b]);
  res = max(res, last_heavy_path_max);
  return res;
}

void update(int a, int b) {
  for (; head[a] != head[b]; b = parent[head[b]]) {
    if (depth[head[a]] > depth[head[b]]) swap(a, b);
    st.update(pos[head[b]], pos[b]);
  }
  if (depth[a] > depth[b]) swap(a, b);
  st.update(pos[a], pos[b]);
}
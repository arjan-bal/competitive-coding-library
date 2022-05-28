/*
	Finds Euler Path / Cycle in O(M + N)
	Remember to call reset before finding answer
	Path will be present in ans
	ans will contain the edge ids of the path
 */

int n, m;

vector<pair<int, int>> edges;
vector<bool> used;
vector<int> ans, pos;
vector<int> adj[N];

void reset()
{
	ans.clear();
	pos.assign(n + 1, 0);
	used.assign(m, 0);
}

// returns other side of edge
int getOther(int id, int v) 
{
	return edges[id].first ^ edges[id].second ^ v;
}

// finds euler path/cycle ending at v
// for cycle check that oddCount in checkEuler is 0
void dfs(int v) 
{
	// need to keep pos array since we might
	// visit v again, wouldn't want to start over
	while(pos[v] < (int)adj[v].size()) {
		int id = adj[v][pos[v]];
		pos[v]++;
		if (used[id]) continue;
		used[id] = 1;
		dfs(getOther(id, v));
		ans.pb(id);
	}
}

vector<int> getVertices(int ending, vector<int> edges)
{
	vector<int> path;
	reverse(all(edges));
	int cur = ending;
	ans.pb(cur);

	for (auto i : edges) {
		cur = getOther(i, cur);
		path.pb(cur);
	}

	reverse(all(path));
	return path;
}

void checkEuler(int src)
{
	int oddCount = 0;
	for (int i = 1; i <= n; ++i) {
		bool parity = 0;
		for (auto j : adj[i]) {
			parity ^= !used[j];
		}
		if (parity && i != src) ++oddCount;
	}
	
	if (oddCount > 1) return ;
	// oddCount of 1 => src is definately odd parity
	// since sum of degrees of all vertices is even = 2 * |E|
	// oddCount 0 => Euler Cycle
	dfs(src);
}
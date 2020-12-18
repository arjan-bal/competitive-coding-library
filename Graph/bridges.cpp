/*
	N: Number of Vertices
	M: Number of Edges
	adj should contain neighbours of the form: {Vertex no., Edge no.}
	After running dfs(1), isBridge[i] will be one if Edge number 'i' is a bridge
	NOTE:
	always ctr>=1 since disc relies on it being 0 only for undiscovered vertices
*/

int disc[N], low[N], parent[N];
bool isBridge[M];
vector<pair<int, int>> adj[N];

void dfs(int cur)
{
	disc[cur] = low[cur] = ctr++;
	
	for(auto i : adj[cur]) {
		if (i.first == parent[cur]) 
			continue;
		if (disc[i.first]) {
			low[cur] = min(low[cur], disc[i.first]);
			continue;
		}
		parent[i.first] = cur;
		dfs(i.first);
		if (low[i.first] <= low[cur]) {
			low[cur] = low[i.first];
		} else if(low[i.first] > disc[cur]) {
			isBridge[i.second]=1;
		}
	}
}
 
vector<int> component;
vector<vector<int>> nadj; 

void dfs1(int cur)
{
	component[cur] = ctr;
	for (auto i : adj[cur]) {
		if (isBridge[i.second] || component[i.first])
			continue;
		dfs1(i.first);
	}
}

void makeBridgeTree(int n)
{
	ctr = 0;
	component.assign(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		if (component[i])
			continue;
		++ctr;
		dfs1(i);
	}
	
	nadj.assign(ctr + 1, vector<int>());

	for (int i = 1; i <= n; ++i) {
		int &ci = component[i];
		for (auto j : adj[i]) {
			int &cj = component[j.first];
			if (ci == cj)
				continue;
			nadj[ci].push_back(cj);
		}
	}
}

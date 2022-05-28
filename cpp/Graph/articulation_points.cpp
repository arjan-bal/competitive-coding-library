/*
	N: Number of Vertices
	M: Number of Edges
	adj should contain neighbours of the form: {Vertex no., Edge no.}
	After running dfs(1), isArt[i] will be one if Vertex number 'i' is an articulation point
	NOTE:
	always ctr>=1 since disc relies on it being 0 only for undiscovered vertices
*/

int disc[N], low[N], parent[N], child[N];
bool isArt[M];
vector<pair<int, int>> adj[N];
int ctr = 1;

void dfs(int cur)
{
	disc[cur] = low[cur] = ctr++;
	child[cur] = 0;
	
	for(auto i : adj[cur]) {
		if (i.first == parent[cur]) 
			continue;
		if (disc[i.first]) {
			low[cur] = min(low[cur], disc[i.first]);
			continue;
		} 
		child[cur]++;
		parent[i.first] = cur;
		dfs(i.first);
		low[cur] = min(low[cur], low[i.first]);
		if (parent[cur] && low[i.ff] >= low[cur]) {
			isArt[cur] = 1;
		}
	}
	if (!parent[cur] && child[cur] > 1) {
		isArt[cur] = 1;
	}
}
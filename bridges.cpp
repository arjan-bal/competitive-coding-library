int disc[N], low[N], parent[N];
bool isbrg[M];
vpii adj[N];

void dfs(int cur)
{
	disc[cur]=low[cur]=ctr++;
	for(auto i:adj[cur]){
		if(i.ff==parent[cur]) continue;
		if(disc[i.ff]){
			low[cur]=min(low[cur], disc[i.ff]);
			continue;
		}
		parent[i.ff]=cur;
		dfs(i.ff);
		if(low[i.ff]<=low[cur]) low[cur]=low[i.ff];
		else if(low[i.ff]>disc[cur]) isbrg[i.ss]=1;
	}
}

//take ctr>=1
 
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
		else isbrg[i.ss]=1, ++cnt;
	}
	return ;
}
 
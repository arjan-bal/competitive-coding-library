bool blocked[N]={};
int subtree[N], maxtree[N];

inline void solveTree(int cen)
{
	
	return ;
}

vi comp;
inline void calSub(int cur, int p)
{
	subtree[cur]=1;
	maxtree[cur]=0;
	for(auto i:adj[cur]){
		if(i==p || blocked[i]) continue;
		calSub(i, cur);
		subtree[cur]+=subtree[i];
		maxtree[cur]=max(maxtree[cur], subtree[i]);
	}
	comp.pb(cur);
	return ;
}

inline void go(int entry)
{
	comp.clear();
	calSub(entry, -1);
	int cen=entry, n1=comp.size();
	for(auto i:comp){
		maxtree[i]=max(maxtree[i], n1-subtree[i]);
		if(maxtree[i]<maxtree[cen]) cen=i;
	}

	//prn(cen);

	solveTree(cen);
	blocked[cen]=1;

	for(auto i:adj[cen]){
		if(blocked[i]) continue;
		go(i);
	}
}

//go(1)
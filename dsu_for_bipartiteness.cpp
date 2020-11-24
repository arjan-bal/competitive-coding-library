struct DSU{
	int n, components;
	bool bipartite;
	vi par, sz;
	vector<bool> toggle;

	DSU(int _n)
	{
		n=components=_n;
		sz.assign(n+1, 1);
		par.resize(n+1);
		iota(all(par), 0);
		bipartite = true;
		toggle.assign(n + 1, false);
	}
	
	pair<int, bool> root(int x)
	{ 
		bool tog = toggle[x];
		while (x != par[x]) {
			x = par[x];
			tog ^= toggle[x];
		}
		return {x, tog};	
	}
	
	bool merge(int a, int b)
	{
		if (!bipartite)
			return false;
		pii res1 = root(a), res2 = root(b);
		int x1 = res1.ff, x2 = res2.ff;
		bool ca = res1.ss, cb = res2.ss;
		if(x1 == x2) {
			if (ca == cb) {
				bipartite = false;
			}
			return false;
		}
		if(sz[x2]>sz[x1]) 
			swap(x1, x2);
		par[x2]=x1; sz[x1]+=sz[x2];
		toggle[x2] = toggle[x2] ^ (ca == cb);
		--components;
		return true;
	}
};
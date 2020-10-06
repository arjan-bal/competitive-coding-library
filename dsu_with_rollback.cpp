struct DSU{
	int n, components;
	vi par, sz;
	vector<pii> stak;

	DSU(int _n)
	{
		n=components=_n;
		sz.assign(n+1, 1);
		par.resize(n+1);
		iota(all(par), 0);
	}
	
	int root(int x)
	{ 
		while (x != par[x]) {
			x = par[x];
		}
		return x;	
	}

	int getVersion()
	{
		return stak.size();
	}

	void rollback(int target)
	{
		assert(target <= stak.size());
		while (stak.size() > target) {
			int a = stak.back().ff, b = stak.back().ss;
			stak.pop_back();
			++components;
			sz[a] -= sz[b];
			par[b] = b;
		}
	}
	
	bool merge(int x1, int x2)
	{
		x1 = root(x1), x2 = root(x2);
		if(x1==x2) {
			return false;
		}
		if(sz[x2]>sz[x1]) 
			swap(x1, x2);
		stak.pb({x1, x2});
		par[x2]=x1; sz[x1]+=sz[x2];
		--components;
		return true;
	}
};
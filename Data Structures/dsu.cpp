struct DSU{
	int n, components;
	vi par, sz;
	int root(int x)
	{ return x==par[x]?x:(par[x]=root(par[x]));	}
	bool merge(int x1, int x2)
	{
		x1=root(x1), x2=root(x2);
		if(x1==x2) return false;
		if(sz[x2]>sz[x1]) swap(x1, x2);
		par[x2]=x1; sz[x1]+=sz[x2];
		--components;
		return true;
	}
	DSU(int _n)
	{
		n=components=_n;
		sz.assign(n+1, 1);
		par.resize(n+1);
		iota(all(par), 0);
	}
};
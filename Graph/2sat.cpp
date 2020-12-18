namespace two_sat{
	const int N=2e6+1;
	vi adj[N], radj[N], topo;
	bool seen[N]={};
	int comp[N]={};

	void add(int a, int b)
	{
		adj[a].pb(b);
		radj[b].pb(a);
	}

	void add_or(int a, int b)
	{
		add((a^1), b);
		add((b^1), a);
	}

	void add_xor(int a, int b)
	{
		add(a, (b^1));
		add(b, (a^1));
		add((a^1), b);
		add((b^1), a);
	}

	void force_true(int a)
	{
		add((a^1), a);
	}

	void dfs1(int cur)
	{
		seen[cur]=1;
		for(auto i:adj[cur])
			if(!seen[i]) dfs1(i);
		topo.pb(cur);
	}

	void dfs2(int cur, int c)
	{
		comp[cur]=c;
		for(auto i:radj[cur])
			if(!comp[i]) dfs2(i, c);
	}

	bool solve(int n, vi &sol)
	{
		int n1=(n<<1);
		fr(i, n1)
			if(!seen[i]) dfs1(i);

		reverse(all(topo));
		int ctr=1;

		for(auto i:topo)
			if(!comp[i]) dfs2(i, ctr++);
		
		for(int i=0; i<n1; i+=2)
			if(comp[i]==comp[i|1]) return 0;
			else sol.pb(comp[i]>comp[i|1]);
		
		return 1;
	}
}
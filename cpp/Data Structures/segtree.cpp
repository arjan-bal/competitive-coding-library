struct Segtree {
	typedef int base;
    typedef int qbase;
	int L, R;
	vector<base> tree;

	inline base unite(base n1, base n2)
	{
		return n1 + n2;
	}

	inline void build(int st, int en, int node)
	{
		if (st == en) {
			tree[node] = vec[st];
			return ;
		}
		
		int mid = (st + en) >> 1, cl = (node << 1), cr = (cl | 1);
		
		build(st, mid, cl);
		build(mid + 1, en, cr);
		
		tree[node] = unite(tree[cl], tree[cr]);
	}

	Segtree(int l, int r) : L(l), R(r)
	{
		tree.resize((R - L  +  1)  <<  2, 0);
		build(L, R, 1);
	}

	inline void update(int st, int en, int node, int idx, base nv)
	{
		if (st > idx || en < idx) return ;
		
		if (st == en) {
			tree[node] += nv;
			return ;
		}
		
		int mid = (st + en) >> 1, cl = (node << 1), cr = (cl | 1);
		
		update(st, mid, cl, idx, nv);
		update(mid + 1, en, cr, idx, nv);
		
		tree[node] = unite(tree[cl], tree[cr]);
	}

	inline qbase query(int st, int en, int node, int l, int r)
	{
		if (st >= l && en <= r) return tree[node];
		
		int mid = (st + en) >> 1, cl = (node << 1), cr = (cl | 1);
		
		if (r <= mid) return query(st, mid, cl, l, r);
		if (l > mid) return query(mid + 1, en, cr, l, r);
		return query(st, mid, cl, l, r) + query(mid + 1, en, cr, l, r);
	}

	void dfs(int st, int en, int node)
	{
		if (st == en) {
			trace(st, tree[node]);
			return ;
		}

		trace(st, en, tree[node]);
		int mid = (st + en) >> 1, cl = (node << 1), cr = (cl | 1);
		dfs(st, mid, cl);
		dfs(mid + 1, en, cr);
	}
	
	void show()
	{
		dfs(L, R, 1);
	}

        qbase query(int l, int r) { return query(L, R, 1, l, r); }

        void update(int idx, base nv)
	{
		update(L, R, 1, idx, nv);
	}
};



//lazy propogation

struct Segtree {
	typedef int base;
    typedef int qbase;
	int L, R;
	vector<base> tree;
	vector<int> lazy;

	inline base unite(base n1, base n2)
	{
		return n1 + n2;
	}

	inline void build(int st, int en, int node)
	{
		if (st == en) {
			tree[node] = vec[st];
			return ;
		}
		
		int mid = (st + en) >> 1, cl = (node << 1), cr = (cl | 1);		
		build(st, mid, cl);
		build(mid + 1, en, cr);		
		tree[node] = unite(tree[cl], tree[cr]);
	}

	Segtree(int l, int r) : L(l), R(r)
	{
		tree.resize((R - L  +  1)  <<  2, 0);
		lazy.resize((R - L  +  1)  <<  2, 0);
		build(L, R, 1);
	}

	inline void push(int st, int en, int node)
	{
		tree[node] += (en - st + 1) * lazy[node];		
		if (st != en) {
			int cl = (node << 1), cr = (cl | 1);
			lazy[cl] += lazy[node];
			lazy[cr] += lazy[node];
		}		
		lazy[node] = 0;
	}

	inline void update(int st, int en, int node, int l, int r, base nv)
	{
		if (lazy[node]) push(st, en, node);		
		if (st>r || en<l) return ;
		
		if (st >= l && en <= r) {
			lazy[node] = nv;
			push(st, en, node);
			return ;
		}
		
		int mid = (st + en) >> 1, cl = (node << 1), cr = (cl | 1);
		
		update(st, mid, cl, l, r, nv);
		update(mid + 1, en, cr, l, r, nv);		
		tree[node] = unite(tree[cl], tree[cr]);
	}

	inline qbase query(int st, int en, int node, int l, int r)
	{
		if (lazy[node]) push(st, en, node);
		if (st > r || en < l) return 0;		
		if (st >= l && en <= r) return tree[node];		
		int mid = (st + en) >> 1, cl = (node << 1), cr = (cl | 1);		
		return query(st, mid, cl, l, r) + query(mid + 1, en, cr, l, r);
	}

	void dfs(int st, int en, int node)
	{
		if (lazy[node]) push(st, en, node);		
		if (st == en) {
			trace(st, tree[node]);
			return ;
		}

		trace(st, en, tree[node]);
		int mid = (st + en) >> 1, cl = (node << 1), cr = (cl | 1);
		dfs(st, mid, cl);
		dfs(mid + 1, en, cr);
	}

	void update(int l, int r, base nv)
	{
		update(L, R, 1, l, r, nv);
	}

	qbase query(int l, int r)
	{
		return query(L, R, 1, l, r);
	}

	void show()
	{
		dfs(L, R, 1);
	}
};

inline int unite(int n1, int n2)
{
	return n1+n2;
}

inline void build(int st, int en, int node)
{
	if(st==en){
		tree[node]=vec[st];
		return ;
	}
	int mid=(st+en)>>1, cl=(node<<1), cr=(cl|1);
	build(st, mid, cl);
	build(mid+1, en, cr);
	tree[node]=unite(tree[cl], tree[cr]);
}

inline void update(int st, int en, int node, int idx, int nv)
{
	if(st>idx || en<idx) return ;
	if(st==en){
		tree[node]+=nv;
		return ;
	}
	int mid=(st+en)>>1, cl=(node<<1), cr=(cl|1);
	update(st, mid, cl, idx, nv);
	update(mid+1, en, cr, idx, nv);
	tree[node]=unite(tree[cl], tree[cr]);
}

inline int query(int st, int en, int node, int l, int r)
{
	if(st>r || en<l) return 0;
	if(st>=l && en<=r) return tree[node];
	int mid=(st+en)>>1, cl=(node<<1), cr=(cl|1);
	return query(st, mid, cl, l, r)+query(mid+1, en, cr, l, r);
}

//lazy propogation

inline void push(int st, int en, int node)
{
	tree[node]+=lazy[node];
	if(st!=en){
		int cl=(node<<1), cr=(cl|1)
		lazy[cl]+=lazy[node];
		lazy[cr]+=lazy[node];
	}
	lazy[node]=0;
}

inline void update(int st, int en, int node, int l, int r, int nv)
{
	if(lazy[node]) push(st, en, node);
	if(st>r || en<l) return ;
	if(st>=l && en<=r){
		lazy[node]=nv;
		push(st, en, node);
		return ;
	}
	int mid=(st+en)>>1, cl=(node<<1), cr=(cl|1);
	update(st, mid, cl, l, r, nv);
	update(mid+1, en, cr, l, r, nv);
	tree[node]=unite(tree[cl], tree[cr]);
}

inline int query(int st, int en, int node, int l, int r)
{
	if(lazy[node]) push(st, en, node);
	if(st>r || en<l) return 0;
	if(st>=l && en<=r) return tree[node];
	int mid=(st+en)>>1, cl=(node<<1), cr=(cl|1);
	return query(st, mid, cl, l, r)+query(mid+1, en, cr, l, r);
}
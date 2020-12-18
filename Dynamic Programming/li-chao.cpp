void insert(int st, int en, int node, pll nw)
{
	int mid=(st+en)/2;
	bool l=eval(nw, st)<eval(tree[node], st);
	bool m=eval(nw, mid)<eval(tree[node], mid);
	if(m){
		swap(nw, tree[node]);
	}
	if(st+1==en) return ;
	if(l!=m) insert(st, mid, 2*node, nw);
	else insert(mid, en, 2*node+1, nw);
}

ll qry(int st, int en, int node, ll pt)
{
	int mid=(st+en)/2;
	ll tmp=eval(tree[node], pt);
	if(st+1==en) return tmp;
	if(pt<=mid){
		return min(tmp, qry(st, mid, 2*node, pt));
	}
	else return min(tmp, qry(mid, en, 2*node+1, pt));
}
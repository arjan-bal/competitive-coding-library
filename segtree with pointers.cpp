struct node{
	node *l=0, *r=0;
	int val=0;
};

typedef node* pnode;

inline void build(int st, int en, pnode &cur)
{
	cur=new node;
	if(st==en){
		cur.val=arr[st];
		return ;
	}
	int mid=((st+en)>>1);
	build(st, mid, cur->l);
	build(mid+1, en, cur->r);
	cur.val=cur->l->val+cur->r->val;
}

inline int valf(pnode x)
{
	if(!x) return 0;
	return x->val;
}

inline void update(int st, int en, pnode &cur, int idx, int nv)
{
	if(st>idx || en<idx) return ;
	if(!cur) cur=new node;
	if(st==en){
		cur->val+=nv;
		return ;
	}
	int mid=((st+en)>>1);
	if(idx<=mid) update(st, mid, cur->l, idx, nv);
	else update(mid+1, en, cur->r, idx, nv);
	cur->val=valf(cur->l)+valf(cur->r);
}

inline int query(int st, int en, pnode cur, int l, int r)
{
	if(st>r || en<l || !cur) return 0;
	if(st>=l && en<=r) return cur->val;
	int mid=((st+en)>>1);
	return query(st, mid, cur->l, l, r)+query(mid+1, en, cur->r, l, r);
}

//lazy propogation

struct node{
	node *l=0, *r=0;
	int val=0, lazy=0;
};

inline void push(int st, int en, pnode &cur)
{
	int lazy=cur->lazy;
	cur->val+=lazy;
	if(st!=en){
		if(!cur->l) cur->l=new node;
		cur->l->lazy+=lazy;
		if(!cur->r) cur->r=new node;
		cur->r->lazy+=lazy;
	}
	cur->lazy=0;
	return ;
}

inline void update(int st, int en, pnode &cur, int l, int r, int nv)
{
	if(cur && cur->lazy) push(st, en, cur);	
	if(st>r || en<l) return ;
	if(!cur) cur=new node;
	if(st>=l && en<=r){
		cur->lazy+=nv;
		push(st, en, cur);
		return ;
	}
	int mid=((st+en)>>1);
	if(l<=mid) update(st, mid, cur->l, l, r, nv);
	if(r>mid) update(mid+1, en, cur->r, l, r, nv);
	cur->val=valf(cur->l)+valf(cur->r);
}

inline int query(int st, int en, pnode &cur, int l, int r)
{
	if(cur && cur->lazy) push(st, en, cur);
	if(st>r || en<l) return 0;
	if(!cur) return 0;
	if(st>=l && en<=r) return cur->val;
	int mid=((st+en)>>1);
	return query(st, mid, cur->l, l, r)+query(mid+1, en, cur->r, l, r);
}
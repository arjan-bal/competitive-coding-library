mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node{
	int prior=rng(), val, size=1;
	node *l=0, *r=0;
	node(int v)
	{
		val=v;		
	}
};

typedef node* pnode;
int sz(pnode t)
{ return t?t->size:0; }

void update(pnode t)
{
	if(!t) return ;
	t->size = sz(t->l)+1+sz(t->r);
}

void split(pnode t,pnode &l,pnode &r, int key){
    if(!t) l=r=0;
    else if(t->val<=key) split(t->r,t->r,r,key), l=t;
    else split(t->l,l,t->l,key), r=t;    
    update(t);
}

void merge(pnode &t, pnode l, pnode r)
{
    if(!l) t=r;
    else if(!r) t=l;
    else if(l->prior>r->prior) merge(l->r, l->r, r), t=l;
    else merge(r->l, l, r->l), t=r;
    update(t);
}

void disp(pnode root)
{
	if(!root) return ;
	disp(root->l);
	cout<<root->val<<" ";
	disp(root->r);
	return ;
}

void insert(pnode &t, pnode &x)		//insert of implicit treap also works, but slower
{
	if(!t) t=x;
	else if(x->prior > t->prior) split(t, x->l, x->r, x->val), t=x;
	else if(x->val<=t->val) insert(t->l, x);
	else insert(t->r, x);
	update(t);
}

void erase(pnode &t, int val)
{
	if(!t) return ;
	if(val < t->val) erase(t->l, val);
	else if(val> t->val) erase(t->r, val);
	else {pnode tmp=t; merge(t, t->l, t->r); free(tmp);}
	update(t);
}

bool find(pnode &t, int val)
{
	if(!t) return 0;
	if(val<t->val) return find(t->l, val);
	if(val>t->val) return find(t->r, val);
	return 1;
}

int less_than(pnode t, ll x)	//elem <=x
{
	if(!t) return 0;
	if(t->val<x) return sz(t->l)+1+less_than(t->r, x);
	if(t->val==x) return sz(t->l)+1;
	return less_than(t->l, x); 
}

ll kth(pnode t, int k)		//kth smallest
{
	if(sz(t->l)+1==k) return t->val;
	if(k<=sz(t->l)) return kth(t->l, k);
	return kth(t->r, k-1-sz(t->l));
}

pnode root=0;

int main()
{
    ios_base::sync_with_stdio(false);
    int x;
    fr(i, 5){
    	cin>>x;
    	node *tmp=new node(x);
    	insert(root, tmp);
    	disp(root);
    	cout<<"\n";
    }
    return 0;
}
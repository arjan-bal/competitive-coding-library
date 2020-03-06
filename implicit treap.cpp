mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node{
	int prior=rng(), val, size=1;
	node *l=0, *r=0;
	node(int v):val(v){}
};

typedef node* pnode;

#define sz(t) (t?t->size:0)

inline void update(pnode t)
{
	if(t) t->size = sz(t->l)+1+sz(t->r);
}

//l=[0, key), r=[key, n)
inline void split(pnode t,pnode &l,pnode &r, int key, int add=0)
{		
    if(!t) return void(l=r=0);
    int cur_key=add+sz(t->l);
    if(key<=cur_key) split(t->l, l, t->l, key, add), r=t;
    else split(t->r, t->r, r, key, add+1+sz(t->l)), l=t;    
    update(t);
}

inline void merge(pnode &t, pnode l, pnode r)
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
	disp(root->l);	cout<<root->val<<" ";	disp(root->r);
	return ;
}

inline void insert(pnode &t, pnode &x, int pos)
{
	if(!t) return void(t=x);
	pnode t1=0, t2=0;
	split(t, t1, t2, pos);
	merge(t1, t1, x);
	merge(t, t1, t2);
}

inline void erase(pnode &t, int pos)
{
	if(!t) return ;
	if(sz(t->l)+1==pos) {node *tmp=t; merge(t, t->l, t->r); free(tmp);}
	else if(pos<=sz(t->l)) erase(t->l, pos);
	else erase(t->r, pos-sz(t->l)-1);
}

// pnode root=0;
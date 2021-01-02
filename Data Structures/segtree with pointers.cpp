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
	int mid=(st+en)>>1;
	build(st, mid, cur->l);
	build(mid+1, en, cur->r);
	cur.val=cur->l->val+cur->r->val;
}

#define valf(x) (x?x->val:0)

inline void update(int st, int en, pnode &cur, int idx, int nv)
{
	if(st>idx || en<idx) return ;
	if(!cur) cur=new node;
	if(st==en){
		cur->val+=nv;
		return ;
	}
	int mid=(st+en)>>1;
	if(idx<=mid) update(st, mid, cur->l, idx, nv);
	else update(mid+1, en, cur->r, idx, nv);
	cur->val=valf(cur->l)+valf(cur->r);
}

inline int query(int st, int en, pnode cur, int l, int r)
{
	if(st>r || en<l || !cur) return 0;
	if(st>=l && en<=r) return cur->val;
	int mid=(st+en)>>1;
	return query(st, mid, cur->l, l, r)+query(mid+1, en, cur->r, l, r);
}

//lazy propogation
// Attribution: https://codeforces.com/contest/1469/submission/102594210

struct Node {
    Node* l = 0; Node* r = 0;
    ll L, R;
    ll sum, lazy;
    
    Node(ll X, ll Y) {
        L = X; R = Y;
        sum = 0; lazy = 0;
    }
 
    void initChildren() {
        int mid = (L + R) >> 1;
        l = new Node(L, mid);
        r = new Node(mid + 1, R);
    }
 
    void push() {
        sum = sum + lazy * (R - L + 1);
        if (L != R && lazy != 0) {
            if (!l) initChildren();
            l->lazy += lazy; r->lazy += lazy;
        }
        lazy = 0;
    }
 
    void pull() {
        if (L != R && l) sum = l->sum + r->sum;
    }
 
    ll query(int lo, int hi) {
        if (hi < L || lo > R) return 0;
        push();
        if (lo >= L && hi <= R) return sum;
        if (!l) initChildren();
        return l->query(lo, hi) + r->query(lo, hi);
    }
 
    void update(int lo, int hi, ll del) {
        push();
        if (hi < L || R < lo) return;
        if (lo <= L && R <= hi) {
            lazy = del;
            push();
            return;
        }
        if (l == NULL) initChildren();
        l->update(lo, hi, del);
        r->update(lo, hi, del);
        pull();
    }
};
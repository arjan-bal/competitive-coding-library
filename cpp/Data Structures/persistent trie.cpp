#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define mp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define ppb(x) pop_back(x)
#define ppf(x) pop_front(x)
#define clr(a,b) memset(a,b,sizeof a)
#define ff first
#define ss second
#define umap unordered_map
#define fr(i,n) for(int i=0;i<n;++i)
#define fr1(i,n) for(int i=1; i<=n; ++i)
#define lwr(x) lower_bound(x)
#define upr(x) upper_bound(x)
#define pq priority_queue

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long, int> pli;
typedef pair<int, long> pil;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd; 
typedef vector<int> vi;
typedef vector<long> vl;
typedef vector<char> vc;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<double> vd;

/*primes*/
//ll p1=1e6+3, p2=1616161, p3=3959297, p4=7393931;
//freopen("in.txt" , "r" , stdin) ;
//freopen("out.txt" , "w" , stdout) ;

int n, q, num, tkn=0;

struct Node {
  int f;
  Node* child[2] = {};
  Node() : f(0) {}
};

vector<Node*> roots;

void init()
{
    roots.resize(n+1);
    roots[0] = new Node;
}

int cans;

typedef Node* pnode;

int tf(pnode cur)
{
    if(!cur) return 0;
    return cur->f;
}

void insert(pnode &naya, pnode purana, int lvl)
{
    if(lvl==-1){
        naya->f=tf(purana)+1;
        return ;
    }
    if((1<<lvl)&num){
        naya->child[1] = new Node;
        naya->child[0]=(purana?purana->child[0]:NULL);

        if(purana) purana=purana->child[1];
        insert(naya->child[1], purana, lvl-1);
        naya->f=tf(naya->child[0])+tf(naya->child[1]);
        return ;
    }
    naya->child[0] = new Node;
    naya->child[1]=(purana?purana->child[1]:NULL);

    if(purana) purana=purana->child[0];
    insert(naya->child[0], purana, lvl-1);
    naya->f=tf(naya->child[0])+tf(naya->child[1]);
    return ;
}

void maxpos(pnode l, pnode r, int lvl)
{
    if(lvl==-1) return ;
    int cur=0;
    if((1<<lvl)&num){
        if(r) cur+=tf(r->child[0]);
        if(l) cur-=tf(l->child[0]);
        if(cur){
            cans|=(1<<lvl);
            if(l) l=l->child[0];
            if(r) r=r->child[0];
            maxpos(l, r, lvl-1);
        }
        else{
            if(l) l=l->child[1];
            if(r) r=r->child[1];
            maxpos(l, r, lvl-1);
        }
    }
    else{
        if(r) cur+=tf(r->child[1]);
        if(l) cur-=tf(l->child[1]);
        if(cur){
            cans|=(1<<lvl);
            if(l) l=l->child[1];
            if(r) r=r->child[1];
            maxpos(l, r, lvl-1);
        }
        else{
            if(l) l=l->child[0];
            if(r) r=r->child[0];
            maxpos(l, r, lvl-1);
        }
    }
    return ;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n>>q;
        init();

        int x;
        fr1(i, n){
            cin>>num;
            roots[i] = new Node;
            insert(roots[i], roots[i-1], 14);
        }
        
        int l, r;
        fr(i, q){
            cin>>num>>l>>r;
            cans=0;
            maxpos(roots[l-1], roots[r], 14);
            cout<<cans<<"\n";
        }        
    }
    return 0;
}

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
#define lwr(x) lower_bound(x)
#define upr(x) upper_bound(x)
#define priority_queue pq

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long, int> pli;
typedef pair<int, long> pil;
typedef pair<long, long> pll;
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

double pi=2.*acos(0);

double radian(double dgre){ return (pi*dgre)/180.; }

double degree(double rad){ return (180*rad)/pi; }

struct vktr{
    double x, y, z;
    vktr(double x=0, double y=0, double z=0):x(x), y(y), z(z){}
    double length(void){ return sqrtl(x*x+y*y+z*z); }
    void prn(void){ cout<<x<<"i + "<<y<<"j + "<<z<<"k\n"; }
};

double norm(vktr v){ return sqrtl(v.x*v.x+v.y*v.y+v.z*v.z); }

typedef vktr point;

struct line{
    point p1, p2;
    double a, b, c;		//ax+by=c
    line(point p1, point p2):p1(p1), p2(p2)
    {a=p2.y-p1.y; b=p1.x-p2.x; c=a*p1.x+b*p1.y; }
};

vktr operator-(vktr v1, vktr v2){ return vktr(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z); }

vktr operator+(vktr v1, vktr v2){ return vktr(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z); }

double operator|(vktr v1, vktr v2){ return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z; }

vktr operator*(vktr v1, vktr v2)
{
    double x=v1.y*v2.z-v1.z*v2.y,
    y=v1.z*v2.x-v1.x*v2.z,
    z=v1.x*v2.y-v1.y*v2.x;
    return vktr(x, y, z);
}

vktr operator*(vktr v, double d){ return vktr(d*v.x, d*v.y, d*v.z); }

vktr operator*(double d, vktr v){ return vktr(d*v.x, d*v.y, d*v.z); }

bool operator==(vktr v1, vktr v2)
{
	if(v1.x==v2.x && v1.y==v2.y && v1.z==v2.z) return 1;
	return 0;
}

bool operator!=(vktr v1, vktr v2){ return !(v1==v2); }

bool liescollinear(point P, point Q, point R){		//2D 
    if(P.x==Q.x){ //vertical segment
        if(min(P.y, Q.y)<=R.y && max(P.y, Q.y)>=R.y) return true;
        else return false;
    }
    else{
        if(min(P.x, Q.x)<=R.x && max(P.x, Q.x)>=R.x) return true;
        else return false;
    }
}

bool isParallel(line l1, line l2)
{
	return l1.a*l2.b-l2.a*l1.b==0;
}

point line2lineIntersect(line l1, line l2)
{
	double det=l1.a*l2.b-l2.a*l1.b;
	return point( (l2.b*l1.c-l1.b*l2.c)/det, (l1.a*l2.c-l2.a*l1.c)/det );
}

bool lies(point P, point Q, point R){		//lies on line segment
 if( (Q - P)*(R - P) != vktr(0, 0, 0) ) return false;
 else return liescollinear(P, Q, R);
}

double distPointLine(line l1, point p){ return norm((l1.p2-l1.p1)*(p-l1.p1))/norm(l1.p2-l1.p1); }


vktr rotateCW(vktr v, double theta)     //2D; theta in radian
{ return vktr(v.x*cos(theta)-v.y*sin(theta), v.x*sin(theta)+v.y*cos(theta), 0); }

double cross2D(vktr v1, vktr v2)  		//value retuned is only z component as x & y=0 in cross prod
{ return v1.x*v2.y - v1.y*v2.x; }

bool isCW(point p1, point p2, point p3)		//2D
{ return cross2D(p1-p2, p3-p2)>0; }

bool isConvex(const vector<point> &vertices)
{
	int n=vertices.size();
	bool first=isCW(vertices[0], vertices[1], vertices[3]);
	for(int i=1; i<n; ++i){
		if(isCW(vertices[i], vertices[(i+1)%n], vertices[(i+2)%n]) != first) return 0;
	}
	return 1;
}

double polygonArea(const vector<point> &vertices)
{
	int n=vertices.size();
	double ans=0;
	for(int i=1; i+1<n; ++i){
		ans+=cross2D(vertices[i]-vertices[0], vertices[i+1]-vertices[0]);
	}
	return abs(ans/2.0);
}

int main()
{
    ios_base::sync_with_stdio(false);
    freopen("in.txt" , "r" , stdin) ;
    int n;
    cin>>n;
    vector<point> vec;
    double x, y;
    int idx=0;

    fr(i, n){
    	cin>>x>>y;
    	vec.pb(point(x, y));
    	if(x<vec[idx].x || (x==vec[idx].x && y>vec[idx].y)){
    		idx=i;
    	}
    }
    vb taken(n, 0);
    taken[idx]=1;
    vector<point> hull;
    hull.pb(vec[idx]);
    int flag=1;
    point prev;
    int nxt;
    int ctr=10;
    while(1){
    	flag=0;
    	prev=hull.back();
    	fr(i, n){
    		if(taken[i]) continue;
    		nxt=i;
    		flag=1;
    		break;
    	}
    	if(flag==0) break;
    	for(int i=nxt+1; i<n; ++i){
    		if(vec[i]==prev) continue;
    		if(isCW(prev, vec[nxt], vec[i])) continue;
    		nxt=i;
    	}
    	if(taken[nxt]) break;
    	taken[nxt]=1;
    	hull.pb(vec[nxt]);
    }

    for(auto i:hull) cout<<i.x<<" "<<i.y<<"\n";
    return 0;
}
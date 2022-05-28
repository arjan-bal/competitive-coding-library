/*
	attribution: https://www.hackerrank.com/rest/contests/master/challenges/weird-queries/hackers/ShikChen/download_solution?primary=true
	Expected complexity: O(n)
*/
const int N=1e5 + 5;
const double eps=1e-6;

struct P { double x,y; } p[N],q[3];
double dis2( P a, P b ) { return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y); }
P operator -( P a, P b ) { return (P){a.x-b.x,a.y-b.y}; }
P operator +( P a, P b ) { return (P){a.x+b.x,a.y+b.y}; }
P operator /( P a, double b ) { return (P){a.x/b,a.y/b}; }
double abs2( P a ) { return a.x*a.x+a.y*a.y; }
double dot( P a, P b ) { return a.x*b.x+a.y*b.y; }
double X( P a, P b ) { return a.x*b.y-a.y*b.x; }
double X( P a, P b, P c ) { return X(b-a,c-a); }
struct C {
    P o; double r2;
    C() { o.x=o.y=r2=0; }
    C( P a ) { o=a; r2=0; }
    C( P a, P b ) { o=(a+b)/2; r2=dis2(o,a); }
    C( P a, P b, P c ) {
        double i,j,k,A=2*X(a,b,c)*X(a,b,c);
        i=abs2(b-c)*dot(a-b,a-c);
        j=abs2(a-c)*dot(b-a,b-c);
        k=abs2(a-b)*dot(c-a,c-b);
        o.x=(i*a.x+j*b.x+k*c.x)/A;
        o.y=(i*a.y+j*b.y+k*c.y)/A;
        r2=dis2(o,a);
    }
    bool cover( P a ) { return dis2(o,a)<=r2+eps; }
};
C MEC( int n, int m ) {
    C mec;
    if ( m==1 ) mec=C(q[0]);
    else if ( m==2 ) mec=C(q[0],q[1]);
    else if ( m==3 ) return C(q[0],q[1],q[2]);
    for ( int i=0; i<n; i++ )
        if ( !mec.cover(p[i]) ) {
            q[m]=p[i];
            mec=MEC(i,m+1);
        }
    return mec;
}
// Ensure all n points are in p[]
// ans = MEC(n, 0)

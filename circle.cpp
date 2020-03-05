//attribution: https://www.hackerrank.com/rest/contests/master/challenges/weird-queries/hackers/ShikChen/download_solution?primary=true
struct circle{
	double abs2(pt a) { return a.x*a.x+a.y*a.y; }
	const double eps=1e-6;
    pt o; double r2;
    circle() { o.x=o.y=r2=0; }
    circle(pt a) { o=a; r2=0; }
    circle(pt a, pt b) { o=(a+b)/2; r2=dist2(o,a); }
    circle(pt a, pt b, pt c) {
        double i, j, k, A=2*cross(b-a, c-a)*cross(b-a, c-a);
        i=abs2(b-c)*dot(a-b, a-c);
        j=abs2(a-c)*dot(b-a, b-c);
        k=abs2(a-b)*dot(c-a, c-b);
        o.x=(i*a.x+j*b.x+k*c.x)/A;
        o.y=(i*a.y+j*b.y+k*c.y)/A;
        r2=dist2(o,a);
    }
    bool cover(pt a) { return dist2(o,a)<=r2+eps; }
};
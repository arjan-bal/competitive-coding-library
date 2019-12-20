namespace geometry{
	#define base double
	struct pt{
		base x, y;
	};

	const double pi=2.*acos(0);

	double radian(double dgre){ return (pi*dgre)/180;}
	double degree(double rad){ return (180*rad)/pi;}
	base dist2(pt p){ return p.x*p.x + p.y*p.y;}
	double dist(pt p){ return sqrtl(dist2(p));}
	pt operator-(pt p1, pt p2){return {p1.x-p2.x, p1.y-p2.y};}
	pt operator+(pt p1, pt p2){return {p1.x+p2.x, p1.y+p2.y};}
	pt operator*(pt p, base d){return {p.x*d, p.y*d};}
	pt operator*(base d, pt p){return {p.x*d, p.y*d};}
	pt operator/(pt p, base d){return {p.x/d, p.y/d};}
	pt operator/(base d, pt p){return {p.x/d, p.y/d};}
	base cross(pt p1, pt p2){return p1.x*p2.y - p1.y*p2.x;}

	bool isParallel(pt a, pt b, pt c, pt d)
	{
		return cross(b-a, d-c)==0;
	}

	bool isColinear(pt a, pt b, pt c)
	{
		return cross(a-b, a-c)==0;
	}

	bool isColinear(pt a, pt b, pt c, pt d)
	{
		return isColinear(a, b, c) && isColinear(b, c, d);
	}

	bool isLeft(pt p1, pt p2, pt p3)
	{ 
		return cross(p1-p2, p3-p2)<0;
	}

	bool oppositeSides(pt a, pt b, pt c, pt d)
	{
	    return isLeft(a, b, c)!=isLeft(a, b, d);
	}

	bool isBetween(pt a, pt b, pt c)
	{
	    return min(a.x, b.x)<=c.x && c.x<=max(a.x, b.x) && min(a.y, b.y)<=c.y && c.y<=max(a.y,b.y);
	}

	/*
	   1:intersects at 1 pt
	   0:doesn't intersect
	  -1:intersects at oo points
	*/
	int lineIntersection(pt a, pt b, pt c, pt d, pt &res)
	{
		if(cross(b-a, d-c)){
			res=c-(d-c)*cross(b-a, c-a)/cross(b-a, d-c);
			return 1;
		}
		return -isColinear(a, b, c, d);
	}

	bool segmentIntersect(pt a, pt b, pt c, pt d)
	{
	    if(isColinear(a, b, c) && isBetween(a, b, c)) return 1;
	    if(isColinear(a, b, d) && isBetween(a, b, d)) return 1;
	    if(isColinear(c, d, a) && isBetween(c, d, a)) return 1;
	    if(isColinear(c, d, b) && isBetween(c, d, b)) return 1;
	    return oppositeSides(a, b, c, d) && oppositeSides(c, d, a, b);
	}
}

bool isConvex(vector<pt> &vertices)
{
	bool first=isLeft(vertices[0], vertices[1], vertices[3]);
	for(int i=1; i<vertices.size(); ++i)
		if(isLeft(vertices[i], vertices[(i+1)%n], vertices[(i+2)%n]) != first) return 0;
	return 1;
}

double polygonArea(vector<pt> &vertices)
{
	double ans=0;
	for(int i=1; i+1<vertices.size(); ++i)
		ans+=cross(vertices[i]-vertices[0], vertices[i+1]-vertices[0]);
	return abs(ans/2.0);
}

//for 3D
pt rotateCWx(pt v, double theta){return {v.x, v.y*cos(theta)-v.z*sin(theta), v.y*sin(theta)+v.z*cos(theta)};}
pt rotateCWy(pt v, double theta){return {v.z*sin(theta)+v.x*cos(theta), v.y, v.z*cos(theta)-v.x*sin(theta)};}
pt rotateCWz(pt v, double theta){return {v.x*cos(theta)-v.y*sin(theta), v.x*sin(theta)+v.y*cos(theta), v.z};}
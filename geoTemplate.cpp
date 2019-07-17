double pi=2.*acos(0);

double radian(double dgre){ return (pi*dgre)/180.; }

double degree(double rad){ return (180*rad)/pi; }

struct vktr{
    double x, y, z;
    vktr(double x=0, double y=0, double z=0):x(x), y(y), z(z){}
    void prn(void){ cout<<x<<"i + "<<y<<"j + "<<z<<"k\n"; }
};

double norm(vktr v){ return sqrtl(v.x*v.x+v.y*v.y+v.z*v.z); }

double norm2(vktr v){ return v.x*v.x+v.y*v.y+v.z*v.z; }

typedef vktr point;

struct line{
    point p1, p2;
    double a, b, c;     //ax+by=c
    line(point p1, point p2):p1(p1), p2(p2)
    {a=p2.y-p1.y; b=p1.x-p2.x; c=a*p1.x+b*p1.y; }
    line(double a, double b, double c):a(a), b(b), c(c)
    {
        if(a==0){
            p1=point(1, c/b);
            p2=point(2, c/b);
            return ;
        }
        if(b==0){
            p1=point(c/a, 1);
            p2=point(c/a, 2);
            return ;
        }
        p1=point(1, (c-b)/a);
        p2=point(2, (c-2.*b)/a);
        return ;
    }

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


vktr rotateCWx(vktr v, double theta)     //around x axis
{ return vktr(v.x, v.y*cos(theta)-v.z*sin(theta), v.y*sin(theta)+v.z*cos(theta)); }

vktr rotateCWy(vktr v, double theta)     //around y axis
{ return vktr(v.z*sin(theta)+v.x*cos(theta), v.y, v.z*cos(theta)-v.x*sin(theta)); }

vktr rotateCWz(vktr v, double theta)     //around z axis
{ return vktr(v.x*cos(theta)-v.y*sin(theta), v.x*sin(theta)+v.y*cos(theta), v.z); }

double cross2D(vktr v1, vktr v2)  		//value retuned is only z component as x & y=0 in cross prod
{ return v1.x*v2.y - v1.y*v2.x; }

bool isCW(point p1, point p2, point p3)		//2D
{ return cross2D(p1-p2, p3-p2)>0; }

bool coolinear(point p1, point p2, point p3)
{ return cross2D(p1-p2, p3-p2)==0; }

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
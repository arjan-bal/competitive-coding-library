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
    line(point p1, point p2):p1(p1), p2(p2){}
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

double cross2D(vktr v1, vktr v2)        //value retuned is only z component as x & y=0 in cross prod
{ return v1.x*v2.y - v1.y*v2.x; }

bool lies(point P, point P1, point P2){
    if( cross2D(P1-P, P2-P)) return false;
    int x1=min(P1.x, P2.x), y1=min(P1.y, P2.y), x2=max(P1.x, P2.x), y2=max(P1.y, P2.y);
    return (P.x>=x1 && P.y>=y1 && P1.x<=x2 && P1.y<=y2);
}

double distPointLine(line l1, point p){ return norm((l1.p2-l1.p1)*(p-l1.p1))/norm(l1.p2-l1.p1); }


vktr rotateCW(vktr v, double theta)     //2D; theta in radian
{ return vktr(v.x*cos(theta)-v.y*sin(theta), v.x*sin(theta)+v.y*cos(theta), 0); }

bool isCW(point p1, point p2, point p3)		//2D
{ return cross2D(p1-p2, p3-p2)>0; }
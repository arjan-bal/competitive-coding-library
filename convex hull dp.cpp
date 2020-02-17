//mantains minimum hull
struct CHT{
    typedef pll line;
    double infy=1e40;

    vector<line> hull;

    #define val(l, x) (l.ffa*x+l.ss)

    double ovrtake(line l1, line l2)
    {
        if(l1.ff==l2.ff)
            if(l1.ss<l2.ss) return -infy;
            else return infy;
        return double(l2.ss-l1.ss)/(l1.ff-l2.ff);
    }

    //adds line only in decreasing slope
    void add_line(line l)
    {
        int n;
        while(hull.size()>=2)
            if((n=hull.size()) && ovrtake(l, hull[n-2])<=ovrtake(hull[n-1], hull[n-2])) hull.ppb();
            else break;
        hull.pb(l);
    }

    ll eval(ll x)
    {
        if(hull.empty()) return inf;
        if(hull.size()==1) return val(hull[0], x);
        int n=hull.size(), en=hull.size()-1, st=0, mid;
        while(st<=en)
            if((mid=(st+en)/2)==0 || val(hull[mid], x)<=val(hull[mid-1], x))
                if(mid+1==n || val(hull[mid], x)<=val(hull[mid+1], x)) return val(hull[mid], x);
                else st=mid+1;
            else en=mid-1;
        return 0;
    }
};
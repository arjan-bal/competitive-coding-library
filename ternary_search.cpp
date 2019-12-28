//for finding max
//reverse sign for min
double ts(double start, double end)
{
    double l = start, r = end;

    for(int i=0; i<200; i++) {
        double l1 = (l*2+r)/3;
        double l2 = (l+2*r)/3;
        if(func(l1) > func(l2)) r = l2; 
        else l = l1;
    }

    double x = l;
    return func(x);
}

int ternary_search(int l,int r, int x)
{
    if(r>=l)
    {
        int mid1 = l + (r-l)/3;
        int mid2 = r -  (r-l)/3;
        if(ar[mid1] == x)
            return mid1;
        if(ar[mid2] == x)
            return mid2;
        if(x<ar[mid1])
            return ternary_search(l,mid1-1,x);
        else if(x>ar[mid2])
            return ternary_search(mid2+1,r,x);
        else
            return ternary_search(mid1+1,mid2-1,x);

    }
    return -1;
}
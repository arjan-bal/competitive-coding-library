/*
	Reverse inequality for minimizing
	Haven't tested in contests yet
	Use binary serach while testing cost on mid and mid + 1 if working with integers 
*/

double ts(double start, double end)
{
    double l = start, r = end;

    for(int i=0; i<200; i++) {
        double l1 = (l * 2 + r) / 3;
        double l2 = (l + 2*r) / 3;
        if(func(l1) > func(l2)) r = l2; 
        else l = l1;
    }

    double x = l;
    return func(x);
}

// works faster than ternary version
inline ll ternarySearch(ll start, ll end)
{
    while (start < end) {
        ll mid = (start + end) / 2;
        if (cost(mid) > cost(mid + 1)) {
        	end = mid;
        } else {
        	start = mid + 1;
        }
    }
    return cost(start);
}

inline ll ternarySearch(ll start, ll end)
{
    while (start < end) {
        ll mid1 = start + (end - start) / 3;
        ll mid2 = end - (end - start) / 3;
        if (cost(mid1) > cost(mid2)) {
        	end = mid2 - 1; 
        } else {
        	start = mid1 + 1;
        }
    }
    return cost(start);
}

int ternary_search(int l,int r, int x)
{
    if(r>=l)
    {
        int mid1 = l + (r - l)/3;
        int mid2 = r -  (r - l)/3;
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
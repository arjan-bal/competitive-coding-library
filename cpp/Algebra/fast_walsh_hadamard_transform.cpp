#define poly vector<ll>

void FWHT(poly &P, bool inverse) {
    int n=P.size();
    for (int len = 1; 2 * len <= n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                ll u = P[i + j];
                ll v = P[i + len + j];
                if (!inverse) {
                    P[i + j] = u + v;
                    P[i + len + j] = u - v;
                } else {
                    P[i + j] = u + v;
                    P[i + len + j] = u - v;
                }                
            }
        }
    }

    // required only for xor
    if (inverse) {
        for (int i = 0; i < n; i++){
            assert(P[i]%n==0);
            P[i] = P[i]/n;
        }
    }
}

// n should be a power of 2
poly multiply(poly p1, poly p2)
{
    int n=p1.size();
    FWHT(p1, 0), FWHT(p2, 0);
    poly res(n);
    for(int i=0; i<n; ++i){
        res[i]=p1[i]*p2[i];
    }
    FWHT(res, 1);
    return res;
}

/*For and
T​2​​=​0 1​   
   1 1​​

(T​2​​​)−1​​=​−1 +1​
       +1 +0​

For or
T2=1 1
   1 0
(T2)-1=+0 +1
       +1 -1
*/
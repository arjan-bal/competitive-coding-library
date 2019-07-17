#define base ll

vector<base> FWHT(vector<base> P, bool inverse) {
    int n=P.size();
    for (int len = 1; 2 * len <= n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                ll u = P[i + j];
                ll v = P[i + len + j];
                P[i + j] = u + v;
                P[i + len + j] = u - v;
            }
        }
    }
    
    if (inverse) {
        for (int i = 0; i < n; i++){
            //if(P[i]%n) cout<<"danger!";
            P[i] = P[i]/n;
        }
    }

    return P;
}

vector<base> multiply(vector<base> &v1, vector<base> &v2)
{
    int n=v1.size();
    vector<base> p1=FWHT(v1, 0), p2=FWHT(v2, 0);
    vector<base> res(n);
    fr(i, n){
        res[i]=p1[i]*p2[i];
    }
    res=FWHT(res, 1);
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
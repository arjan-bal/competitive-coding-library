/*
	attribution: https://www.hackerrank.com/rest/contests/master/challenges/weird-queries/hackers/ShikChen/download_solution?primary=true
	Expected complexity: O(n)
*/
vector<pt> P;

circle MCC(int n, int m){
    circle ans;
    if(!m) random_shuffle(all(P));
    else if(m==1) ans=circle(P[0]);
    else if(m==2) ans=circle(P[0], P[1]);
    else if(m==3) return circle(P[0], P[1], P[2]);
    for(int i=m; i<n; ++i)
        if(!ans.cover(p[i])){
            swap(P[m], P[i])
            ans=MCC(i, m+1);
        }
    return ans;
}
// circle ans=MCC(vec.size(), 0);
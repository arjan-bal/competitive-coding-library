/*
	attribution: cp-algorithms.com
	necessary conditions:
	dp(i,j)= min k ≤ j {dp(i−1,k-1)+C(k,j)} 
	opt(i,j) ≤ opt(i,j+1)
*/

bool act=0;		//keep toggling active
int C[N][N];	//define cost function/matrix, proof usually involves C
int dp[2][N];

// compute dp[act][l] ... dp[act][r]
inline void compute(int l, int r, int optl, int optr)
{
	if(l > r) return;
    int mid = (l + r) >> 1, en = min(mid, optr), &best = dp[act][mid] = inf, cur, opt;

    for(int k = optl; k <= en; ++k) {
    	cur = dp[!act][k-1] + C[k][mid];
    	if(cur < best) best = cur, opt = k; 
    }

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
/*
	// 1 based indexing
	for(int groups=1; groups<=k; ++groups){
		act^=1;
		compute(groups, n, groups, n);
	}
*/
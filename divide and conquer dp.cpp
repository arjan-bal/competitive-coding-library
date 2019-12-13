//attribution: cp-algorithms.com

bool act=0;		//keep toggling active
long long C(int i, int j);	//define cost function, proof usually involves this
long long dp[2][N];

// compute dp[act][l], ... dp[act][r] (inclusive)
void compute(int l, int r, int optl, int optr)
{
    if(l > r) return;
    int mid = (l + r) >> 1;
    ll &best = dp[act][mid], cur;
    best = -inf;
    int opt = -1;

    for(int k = optl; k <= min(mid, optr); ++k) {
    	cur = dp[!act][k] + C(k, mid);
    	if(cur <= best) continue;
    	best = cur;
    	opt = k; 
    }

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
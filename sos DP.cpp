const int N=21;

int dp[1<<N][N];

int cal(int mask, int idx)
{
    if(idx<0) return arr[mask];
    if(dp[mask][idx]!=-1) return dp[mask][idx];
    int ans=cal(mask, idx-1);
    if((mask>>idx)&1) ans+=(((1<<idx)^mask), idx-1);
    return dp[mask][idx]=ans; 
}

for(int i = 0; i<(1<<N); ++i)
    F[i] = A[i];
for(int i = 0;i < N; ++i) for(int mask = 0; mask < (1<<N); ++mask){
    if(mask & (1<<i))
        F[mask] += F[mask^(1<<i)];
}
ll dp[m][m];
int r[m][m];
for(int j=0; j<m; j++){
	for(int i=m-1; i>=0; i--){
		dp[i][j]=INF;
		if(j<i+2){
			dp[i][j]=0ll;
		}
		if(j==i+2){
			dp[i][j]=a[j]-a[i];
			r[i][j]=i+1;
		}
		if(j>i+2){
			int lo=r[i][j-1];
			int hi=r[i+1][j];
			for(int k=lo; k<=hi; k++){
				if(dp[i][k]+dp[k][j]+a[j]-a[i]<dp[i][j]){
					dp[i][j]=dp[i][k]+dp[k][j]+a[j]-a[i];
					r[i][j]=k;
				}
			}
		}
	}
}
cout << dp[0][m-1] << endl;
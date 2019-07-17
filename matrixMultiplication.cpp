typedef vector<vector<ll>> matrix; 

void multiply(matrix &mat1, matrix &mat2)
{
	int n=mat1.size();
	ll mul[n][n], sum;
	for(int i=0; i<n; ++i)
	    for(int j=0; j<n; ++j){	
	    	sum=0;
	        for(int l=0; l<n; ++l) sum=(sum+mat1[i][l]*mat2[l][j])%mod;
	        mul[i][j]=sum;
	    }
	for(int i=0; i<n; ++i) 
		for(int j=0; j<n; ++j) mat1[i][j]=mul[i][j];
}

void power(matrix &res, ll ex)
{
	matrix M=res;
	--ex;
	while(ex>0){
		if(ex&1) multiply(res, M);
		multiply(M, M);
		ex>>=1;
	}
	return ;
}
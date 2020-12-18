typedef vector<vector<ll>> matrix; 

void reshape(matrix &mat, int n, int m)
{
	mat.resize(n);
	for(auto &i:mat) i.resize(m);
}

matrix operator*(matrix &mat1, matrix &mat2)
{
	int n1=mat1.size(), m1=mat1[0].size(), n2=mat2.size(), m2=mat2[0].size();
	assert(m1==n2);
	ll sum;
	matrix ret;
	reshape(ret, n1, m2);

	for(int i=0; i<n1; ++i)
	    for(int j=0; j<m2; ++j){	
	    	sum=0;
	        for(int l=0; l<m1; ++l) sum=(sum+mat1[i][l]*mat2[l][j])%mod;
	        ret[i][j]=sum;
	    }
	return ret;
}

matrix power(matrix res, ll ex)
{
	matrix tmp=res;
	--ex;
	while(ex>0){
		if(ex&1) res=res*tmp;
		tmp=tmp*tmp;
		ex>>=1;
	}
	return res;
}
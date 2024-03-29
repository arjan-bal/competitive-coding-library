typedef vector<vector<modint>> matrix; 

template<typename T>
void reshape(vector<vector<T>> &mat, int n, int m)
{
	mat.assign(n, vector<T>(m, T(0)));
}

template<typename T>
vector<vector<T>> operator*(vector<vector<T>> &mat1, vector<vector<T>> &mat2)
{
	int n1=mat1.size(), m1=mat1[0].size(), n2=mat2.size(), m2=mat2[0].size();
	assert(m1==n2);
	T sum;
	vector<vector<T>> ret;
	reshape(ret, n1, m2);

	for(int i=0; i<n1; ++i)
	    for(int j=0; j<m2; ++j){	
	    	sum=0;
	        for(int l=0; l<m1; ++l) sum=(sum+mat1[i][l]*mat2[l][j]);
	        ret[i][j]=sum;
	    }
	return ret;
}

template<typename T>
vector<vector<T>> power(vector<vector<T>> res, ll ex)
{
	auto tmp=res;
	--ex;
	while(ex>0){
		if(ex&1) res=res*tmp;
		tmp=tmp*tmp;
		ex>>=1;
	}
	return res;
}
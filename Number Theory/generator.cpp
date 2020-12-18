int generator(int p)
{	
	//find unique prime factors
	vector<int> fac;
	int x=p-1;
	while(x!=1){
		int f=lp[x];
		while(x%f==0) x/=f;
		fac.pb(f);
	}
	
	for(int g=2; g<p; ++g){
		bool flag=0;
		for(auto i:fac){
			if(power(g, (p-1)/i, p)==1){
				flag=1;
				break;
			}
		}
		if(!flag) return g; 
	}
	return -1;
}
const int N1=1e7;
vi lp(N1+1, 0), prime, mu(N1+1, 1);

void mobius()
{
	int a, b;
	for(int i=2; i<=N1; ++i){
		if(lp[i]==0){
			lp[i]=i;
			prime.pb(i);
		}
		for(auto j:prime){
			if(j>lp[i] || i*j>N1) break;
			lp[i*j]=j;
		}
		a=lp[i], b=i/lp[i];
		if(b==1) mu[i]=-1;
		else if(__gcd(a, b)!=1) mu[i]=0;
		else mu[i]=mu[a]*mu[b];
	}
}
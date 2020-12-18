//taken from cp-algorithms.com

const int N1=1e7;

vector<int> lp(N1+1, 0), prime;

void seive()
{
	for(int i=2; i<=N1; ++i){
		if(lp[i]==0){
			lp[i]=i;
			prime.push_back(i);
		}
		for(auto j:prime){
			if(j>lp[i] || i*j>N1) break;
			lp[i*j]=j;
		}
	}
}
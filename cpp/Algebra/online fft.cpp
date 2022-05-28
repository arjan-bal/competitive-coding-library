//attributation: Tanuj Khattar's slides on online FFT
//online FFT for solving recurrences of the form
//F(i)=sum(1<=j<i)F(j)*G(n-j)

void convolve(int l1, int r1, int l2, int r2)
{
	vll a(F+l1, F+r1+1), b(G+l2, G+r2+1);
	FFT::mul_big_mod(a, b, mod);
	for(int i=0; i<a.size(); ++i){
		add(F[l1+l2+i], a[i]);
	}
}

void generate(int n) 
{
	F[1]=1;
	for(int i=1; i<=n-1; ++i){

		add(F[i+1], F[i]*G[1]%mod);
		add(F[i+2], F[i]*G[2]%mod);

		for(int pw=2; i%pw==0 && pw+1<=n; pw*=2)
			convolve(i-pw, i-1, pw+1, min(2*pw, n));
	}
}
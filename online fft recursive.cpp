//add contributions of ans[l->mid] to ans[mid+1->r]
void solve(int l, int r)
{
	if(l==r) return ;

	int m=(l+r)/2;
	solve(l, m);

	int sz=r-l+1;
	vi a(ans+l, ans+m+1), b(numtree+1, numtree+sz+1);
	vi c=mult(a, b);

	for(int i=m+1; i<=r; ++i)
		add(ans[i], c[i-l-1]);

	solve(m+1, r);
	return ;
}
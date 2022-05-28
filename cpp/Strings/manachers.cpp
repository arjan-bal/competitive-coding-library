void manachers(string &s, vi &d1, vi &d2)
{
    int n=s.size();
    d1.resize(n);
    for (int i=0, l=0, r=-1; i<n; i++) {
        int k=(i>r) ? 1 : min(d1[l+r-i], r-i);
        while (i-k>=0 && i+k<n && s[i-k]==s[i+k]) k++;
        d1[i]=k--;
        if (i+k>r) l=i-k, r=i+k;
    }
    d2.resize(n);
    for (int i=0, l=0, r=-1; i<n; i++) {
        int k=(i>r) ? 0 : min(d2[l+r-i+1], r-i+1);
        while (i-k-1>=0 && i+k<n && s[i-k-1]==s[i+k]) k++;
        d2[i]=k--;
        if (i+k>r) l=i-k-1, r=i+k;
    }
}
inline int log(int x) {
    return 32 - __builtin_clz(x) - 1;
}

void preprocess(int n)
{
    for (int i = 0; i < n; i++)
        lookup[i][0] = i;
 
    for (int j=1; (1<<j)<=n; j++)
    {
        for (int i=0; (i+(1<<j)-1) < n; i++)
        { 
            if (arr[lookup[i][j-1]] < arr[lookup[i + (1<<(j-1))][j-1]])
                lookup[i][j] = lookup[i][j-1];
            else
                lookup[i][j] = lookup[i + (1 << (j-1))][j-1];      
        }
    }
}
 
// Returns minimum of arr[L..R]
int query(int L, int R)
{
    int j = log(R-L+1);
 
    if (arr[lookup[L][j]] <= arr[lookup[R - (1<<j) + 1][j]])
        return arr[lookup[L][j]];
 
   else return arr[lookup[R - (1<<j) + 1][j]];
}
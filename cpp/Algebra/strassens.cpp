#include "bits/stdc++.h"

using namespace std;

typedef int base;
typedef vector<vector<base>> matrix;

matrix zero_matrix(int n, int m)
{
	matrix ret(n);
	for (auto &i:ret) i.resize(m);
	return ret;
}

matrix submatrix(const matrix &mat, int i1, int i2, int j1, int j2)
{
    matrix ans = zero_matrix(i2 - i1, j2 - j1);
    for (int i = i1; i < i2; i++)
        for (int j = j1; j < j2; j++)
            ans[i - i1][j - j1] = mat[i][j];        
    return ans;
}


matrix expand(const matrix &mat)
{
    auto n = mat.size();
    auto m = mat[0].size();
    int t = 1;
    int p = max(n, m);
  
    while (t < p)
        t *= 2;
    p = t;
    matrix ans = zero_matrix(p, p);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        	ans[i][j] = mat[i][j];
    return ans;
}

void print(const matrix &grid)
{
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++)
            cout << grid[i][j] << ' ';
        cout << '\n';
    }
}

matrix operator+(const matrix &a, const matrix &b)
{
    matrix ans = zero_matrix(a.size(), a[0].size());
    for (int i = 0; i < a.size(); i++)
    	for (int j = 0; j < a[i].size(); j++)
            ans[i][j] = a[i][j] + b[i][j];
    return ans;
}

matrix operator-(const matrix &a,  const matrix &b)
{
    matrix ans = zero_matrix(a.size(), a[0].size());
    for (int i = 0; i < a.size(); i++)
    	for (int j = 0; j < a[i].size(); j++)
            ans[i][j] = a[i][j] - b[i][j];
    return ans;
}

matrix naive_multiply(const matrix &a, const matrix &b)
{
    int s = 0;
    matrix ans = zero_matrix(a.size(), b[0].size());
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < b[i].size(); j++){
            s = 0;
            for (int k = 0; k < a[i].size(); k++)
                s += a[i][k] * b[k][j];
            ans[i][j] = s;
        }
    }
    return ans;
}


matrix strassen(const matrix &m1, const matrix &m2)
{
    int s1 = m1.size();
    int s2 = m2.size();
    if (s1 > 2 && s2 > 2){
        matrix a = submatrix(m1, 0, s1 / 2, 0, s1/2), 
        b = submatrix(m1, 0, s1 / 2, s1 / 2, s1),
        c = submatrix(m1, s1 / 2, s1, 0, s1 / 2), 
        d = submatrix(m1, s1 / 2, s1, s1 / 2, s1), 
        e = submatrix(m2, 0, s2 / 2, 0, s2/2), 
        f = submatrix(m2, 0, s2 / 2, s2 / 2, s2), 
        g = submatrix(m2, s2 / 2, s2, 0, s2 / 2), 
        h = submatrix(m2, s2 / 2, s2, s2 / 2, s2),
        ans;


        matrix p1, p2, p3, p4, p5, p6, p7;
        p1 = strassen(a, f - h);
        p2 = strassen(a + b, h);
        p3 = strassen(c + d, e);
        p4 = strassen(d, g - e);
        p5 = strassen(a + d, e + h);
        p6 = strassen(b - d, g + h);
        p7 = strassen(a - c, e + f);
        matrix c1, c2, c3, c4;
        c1 = p5 + p4 + p6 - p2;
        c2 = p1 + p2;
        c3 = p3 + p4;
        c4 = p1 + p5 - p3 - p7;



        int flag1, flag2;
        for (int i = 0; i < m1.size(); i++){
            vector<base> row;
            if (i < m1.size() / 2)
                flag1 = 0;
            else
                flag1 = 1;
            for (int j = 0; j < m2[i].size(); j++)
                if (j < m2[i].size() / 2)
                    if (flag1 == 0) row.push_back(c1[i][j]);
                    else row.push_back(c3[i - m1.size() / 2][j]);
                else
                    if (flag1 == 0) row.push_back(c2[i][j - m2[i].size() / 2]);
                    else row.push_back(c4[i - m1.size() / 2][j - m2[i].size() / 2]);
            ans.push_back(row);
        }
        return ans;
    }
   	return naive_multiply(m1, m2);
}

int main()
{
    matrix v1, v2, v3;
    
    matrix matrix1 = {
    {1, 2, 3, 4}, 
    {5, 6, 7, 8}, 
    {9, 10, 11, 12},
    {1, 2, 3, 4}, 
    {5, 6, 7, 8}, 
    {9, 10, 11, 12}
    };				//4*6 matrix
    matrix matrix2 = {
    {13, 14, 15, 13, 14, 15}, 
    {16, 17, 18, 16, 17, 18}, 
    {19, 20, 21, 19, 20, 21}, 
    {22, 23, 24, 22, 23, 24}
    };				//6*4 matrix

    matrix m1, m2, m3, m4;
    m1 = expand(matrix1);
    m2 = expand(matrix2);
    
    v1 = submatrix(naive_multiply(m1, m2), 0, matrix1.size(), 0, matrix2[0].size());
    

    print(v1);
    cout << '\n';

    v2 = submatrix(strassen(m1, m2), 0, matrix1.size(), 0, matrix2[0].size());
    print(v2);

    return 0;
}
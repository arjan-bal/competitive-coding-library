// Attrribution: Neal Wu on Codeforces
// Warning: this only handles the case where # equations >= # variables and there is a valid solution.
template<typename float_t>
struct gaussian {
    int n;
    vector<vector<float_t>> coefficients;
    vector<float_t> values;
 
    gaussian(int _n = 0) {
        init(_n);
    }
 
    void init(int _n) {
        n = _n;
        coefficients = {};
        values = {};
    }
 
    void add_equation(const vector<float_t> &coefs, float_t value) {
        assert(int(coefs.size()) == n);
        coefficients.push_back(coefs);
        values.push_back(value);
    }
 
    void swap_rows(int a, int b) {
        swap(coefficients[a], coefficients[b]);
        swap(values[a], values[b]);
    }
 
    // Eliminates `coefficients[target][col]` by canceling the `target` row with the `source` row.
    void eliminate(int target, int source, int col, int start_col = 0) {
        if (coefficients[target][col] == 0)
            return;
 
        assert(coefficients[source][col] != 0);
        float_t ratio = coefficients[target][col] / coefficients[source][col];
 
        for (int i = start_col; i < n; i++)
            coefficients[target][i] -= coefficients[source][i] * ratio;
 
        coefficients[target][col] = 0;
        values[target] -= values[source] * ratio;
    }
 
    vector<float_t> solve() {
        int rows = int(coefficients.size());
        assert(rows >= n);
 
        for (int i = 0; i < n; i++) {
            int largest = i;
 
            for (int row = i + 1; row < rows; row++)
                if (coefficients[row][i] > coefficients[largest][i])
                    largest = row;
 
            swap_rows(largest, i);
 
            for (int row = i + 1; row < rows; row++)
                eliminate(row, i, i, i);
        }
 
        vector<float_t> answers(n, 0);
 
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < i; j++)
                assert(coefficients[i][j] == 0);
 
            float_t value = values[i];
 
            for (int j = i + 1; j < n; j++)
                value -= coefficients[i][j] * answers[j];
 
            answers[i] = value / coefficients[i][i];
        }
 
        return answers;
    }
};
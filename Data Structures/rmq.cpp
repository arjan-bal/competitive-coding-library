/// attribution: https://codeforces.com/contest/1314/submission/71724665
template<typename T, bool maximum_mode = false>
struct RMQ {
    int n = 0, levels = 0;
    vector<vector<T>> range_min;
 
    RMQ(const vector<T> &values = {}) {
        if (!values.empty())
            build(values);
    }
 
    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }
 
    static T better(T a, T b) {
        return maximum_mode ? max(a, b) : min(a, b);
    }
 
    void build(const vector<T> &values) {
        n = values.size();
        levels = largest_bit(n) + 1;
        range_min.resize(levels);
 
        for (int k = 0; k < levels; k++)
            range_min[k].resize(n - (1 << k) + 1);
 
        if (n > 0)
            range_min[0] = values;
 
        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                range_min[k][i] = better(range_min[k - 1][i], range_min[k - 1][i + (1 << (k - 1))]);
    }
 
    T query_value(int a, int b) const {
        assert(0 <= a && a <= b && b < n);
        int level = largest_bit(b - a + 1);
        return better(range_min[level][a], range_min[level][b + 1 - (1 << level)]);
    }
};
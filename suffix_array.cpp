///RMQ attribution: https://codeforces.com/contest/1314/submission/71724665
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

template<typename T_string>
struct suffix_array{
	int n, C;
	T_string str;
	vi p, rank, lcp;
	RMQ<int> rmq;

	void build_suffix_array()
	{
		if(C <= 256) str.pb(0);
		else str.pb(-1);

		++n;		
		p.resize(n);
		vi c(n);
		vi cnt(max(n, C), 0);

		if(C < 256){
			for(int i = 0; i < n; ++i)
				++cnt[str[i]];
			for(int i = 0; i < n; ++i)
				p[--cnt[str[i]]] = i;
		} else{
			iota(p.begin(), p.end(), 0);
			sort(all(p), [&](int a, int b){
				return str[a] < str[b];
			});
		}

		int classes = 1;
		c[p[0]] = 0;

		for(int i=1; i<n; ++i)
			c[p[i]] = str[p[i]] == str[p[i-1]] ? classes-1 : classes++;

		vi pn(n), cn(n);

		for(int len = 1; len < n && classes < n; len <<= 1){
			for(int i = 0; i < n; ++i)
				pn[i] = p[i] >= len ? p[i] - len : p[i] - len + n;
			
			fill(cnt.begin(), cnt.begin() + classes, 0);

			for(int i = 0; i < n; ++i)
				++cnt[c[pn[i]]];

			for(int i = 1; i < classes; ++i)
				cnt[i] += cnt[i-1];

			for(int i = n-1; i >= 0; --i)
				p[--cnt[c[pn[i]]]] = pn[i];

			cn[p[0]] = 0;
			classes = 1;
			pii prev = {c[p[0]], c[(p[0] + len) % n]};

			for(int i = 1; i < n; ++i){
				pii cur = {c[p[i]], c[(p[i] + len) % n]};
				cn[p[i]] = cur == prev ? classes - 1 : classes++;
				prev = cur;
			}
			c.swap(cn);
		}

		--n;
		str.ppb();
		p.erase(p.begin());
	}

	void build_lcp()
	{
		rank.resize(n);
	    for (int i = 0; i < n; ++i)
	        rank[p[i]] = i;

	    int k = 0;
	    lcp.resize(n-1, 0);
	    for (int i = 0; i < n; ++i) {
	        if (rank[i] == n - 1) {
	            k = 0;
	            continue;
	        }
	        int j = p[rank[i] + 1];
	        while(i + k < n && j + k < n && str[i+k] == str[j+k])
	            k++;
	        lcp[rank[i]] = k;
	        if(k) k--;
	    }
	}

	suffix_array(const T_string &_str, bool need_rmq = true, int _C = 256)
	{
		str = _str, C = _C, n = _str.size();
		build_suffix_array();
		if(need_rmq && n > 1) 
			build_lcp(), rmq.build(lcp);
	}

	// 0 indexing
	int get_lcp(int a, int b)
	{
		if(a == b) return n - a;
		a = rank[a], b = rank[b];
		if(a > b) swap(a, b);
		return rmq.query_value(a, b - 1);
	}

	int compare(int a, int b, int len)
	{
		int match = get_lcp(a, b);
		if(match >= len) return 0;
		if(a + match >= n || b + match >= n) return a > b ? -1 : 1;
		return str[a + match] > str[b + match] ? 1 : -1; 
	}
};
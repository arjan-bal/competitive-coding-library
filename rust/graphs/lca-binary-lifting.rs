
struct LCA {
    parent: Vec<Vec<usize>>,
    depth: Vec<usize>,
    log_n: usize,
    n: usize,
}

impl LCA {
    /*
       Adj list should be of size n + 1 and node numbers are in [1, n].
    */
    fn new(adj: &Vec<Vec<usize>>) -> LCA {
        let mut log_n = 1;
        let n = adj.len() - 1;
        while 1 << log_n < n {
            log_n += 1;
        }
        let mut depth = vec![0; n + 1];
        let mut parent = vec![vec![0; n + 1]; log_n];
        let mut q = VecDeque::new();
        q.push_back(1);

        let mut populate = |cur: usize, par: usize, parent: &mut Vec<Vec<usize>>| {
            parent[0][cur] = par;
            depth[cur] = depth[par] + 1;
            let mut prev_par = par;
            for j in 1..log_n {
                if prev_par == 0 {
                    break;
                }
                parent[j][cur] = parent[j - 1][prev_par];
                prev_par = parent[j][cur];
            }
        };

        while !q.is_empty() {
            let cur = q.pop_front().unwrap();
            for &child in &adj[cur] {
                if child == parent[0][cur] {
                    continue;
                }
                populate(child, cur, &mut parent);
                q.push_back(child);
            }
        }

        LCA {
            parent,
            depth,
            log_n,
            n,
        }
    }

    fn get_lca(&self, mut u: usize, mut v: usize) -> usize {
        if self.depth[v] < self.depth[u] {
            std::mem::swap(&mut u, &mut v);
        }

        let dif = self.depth[v] - self.depth[u];
        for i in 0..self.log_n {
            if (dif >> i) & 1 == 1 {
                v = self.parent[i][v];
            }
        }

        if u == v {
            return u;
        }

        for i in (0..self.log_n).rev() {
            if self.parent[i][u] != self.parent[i][v] {
                u = self.parent[i][u];
                v = self.parent[i][v];
            }
        }
        self.parent[0][u]
    }
}

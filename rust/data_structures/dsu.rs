struct DSU {
    parent:  Vec<usize>,
    component_size: Vec<usize>,
    num_comps: usize,
}

impl DSU {
    fn root(&mut self, x: usize) -> usize {
        if x == self.parent[x] {
            return x;
        }
        self.parent[x] = self.root(self.parent[x]);
        self.parent[x]
    }

    fn merge(&mut self, c1: usize, c2: usize) -> bool {
        let mut r1 = self.root(c1);
        let mut r2 = self.root(c2);
        if r1 == r2 {
            return false;
        }
        if self.component_size[r2] > self.component_size[r1] {
            swap(&mut r1, &mut r2);
        }
        self.parent[r2] = r1;
        self.component_size[r1] += self.component_size[r2];
        self.num_comps -= 1;
        true
    }

    fn new(n: usize) -> DSU {
        DSU {
            parent: (0..n).map(|i| i).collect(),
            component_size: vec![1; n],
            num_comps: n,
        }
    }
}

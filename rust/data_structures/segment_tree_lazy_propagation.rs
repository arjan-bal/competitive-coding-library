[derive(Clone, Debug, Copy)]
enum Update {
    None,
    Assign,
    Xor,
}

#[derive(Clone, Debug)]
struct Node {
    frequency: Vec<usize>,
    lazy: i32,
    update_type: Update,
}

impl Node {
    fn merge(&self, other: &Node) -> Node {
        let mut res = Node {
            frequency: vec![0; B],
            lazy: -1,
            update_type: Update::None,
        };

        for i in 0..B {
            res.frequency[i] = self.frequency[i] + other.frequency[i];
        }

        res
    }
}

#[derive(Debug)]
struct Res(u64);

impl Res {
    fn merge(&self, other: &Res) -> Res {
        Res(self.0 + other.0)
    }
}

struct SegTree {
    tree: Vec<Node>,
    start: i32,
    end: i32,
}

struct SegTreeBuildCtx<'a> {
    vals: &'a Vec<usize>,
}

impl SegTree {
    fn query(&mut self, l: i32, r: i32) -> Res {
        self.query_range(self.start, self.end, 1, l, r)
    }

    fn range_update(&mut self, l: i32, r: i32, delta: usize, update_type: Update) {
        self.update_range(self.start, self.end, 1, l, r, delta, update_type)
    }

    fn query_range(&mut self, st: i32, en: i32, node: usize, l: i32, r: i32) -> Res {
        if self.tree[node].lazy != -1 {
            self.apply_lazy(st, en, node);
        }
        if en < l || st > r {
            return Res(0);
        }
        if st >= l && en <= r {
            return Res(self.calculate(node));
        }
        let mid = (st + en) >> 1;
        let node_l = node << 1;
        let node_r = (node << 1) | 1;
        self.query_range(st, mid, node_l, l, r)
            .merge(&self.query_range(mid + 1, en, node_r, l, r))
    }

    fn calculate(&self, node: usize) -> u64 {
        let mut sum = 0;
        for bit in 0..B {
            sum += (1 << bit) as u64 * self.tree[node].frequency[bit] as u64;
        }
        sum
    }

    fn update_range(
        &mut self,
        st: i32,
        en: i32,
        node: usize,
        l: i32,
        r: i32,
        delta: usize,
        update_type: Update,
    ) {
        if self.tree[node].lazy != -1 {
            self.apply_lazy(st, en, node);
        }
        if en < l || st > r {
            return;
        }
        if st >= l && en <= r {
            self.tree[node].lazy = delta as i32;
            self.tree[node].update_type = update_type;
            self.apply_lazy(st, en, node);
            return;
        }
        let mid = (st + en) >> 1;
        let node_l = node << 1;
        let node_r = (node << 1) | 1;
        self.update_range(st, mid, node_l, l, r, delta, update_type);
        self.update_range(mid + 1, en, node_r, l, r, delta, update_type);
        self.tree[node] = self.tree[node_l].merge(&self.tree[node_r]);
    }

    fn apply_lazy(&mut self, st: i32, en: i32, node: usize) {
        let val = self.tree[node].lazy;
        if val == -1 {
            return;
        }
        let u_type = self.tree[node].update_type;
        match u_type {
            Update::Assign => {
                for i in 0..B {
                    if (val >> i) & 1 == 1 {
                        self.tree[node].frequency[i] = (en - st + 1) as usize;
                    } else {
                        self.tree[node].frequency[i] = 0;
                    }
                }
            }
            Update::Xor => {
                for i in 0..B {
                    if (val >> i) & 1 == 1 {
                        self.tree[node].frequency[i] =
                            (en - st + 1) as usize - self.tree[node].frequency[i];
                    }
                }
            }
            _ => (),
        }
        self.tree[node].lazy = -1;
        self.tree[node].update_type = Update::None;
        if st == en {
            return;
        }
        let node_l = node << 1;
        let node_r = (node << 1) | 1;
        match u_type {
            Update::None => (),
            Update::Assign => {
                self.tree[node_l].lazy = val;
                self.tree[node_r].lazy = val;
                self.tree[node_l].update_type = u_type;
                self.tree[node_r].update_type = u_type;
            }
            Update::Xor => {
                (self.tree[node_l].lazy, self.tree[node_l].update_type) = SegTree::combine_lazy(
                    val,
                    u_type,
                    self.tree[node_l].lazy,
                    self.tree[node_l].update_type,
                );
                (self.tree[node_r].lazy, self.tree[node_r].update_type) = SegTree::combine_lazy(
                    val,
                    u_type,
                    self.tree[node_r].lazy,
                    self.tree[node_r].update_type,
                );
            }
        }
    }

    fn combine_lazy(lazy1: i32, type1: Update, lazy2: i32, type2: Update) -> (i32, Update) {
        if lazy2 == -1 {
            return (lazy1, type1);
        }
        match type2 {
            Update::None => (lazy1, type1),
            Update::Assign|Update::Xor => match type1 {
                Update::None => panic!("Applying lazy with type1 as None"),
                Update::Assign => (lazy1, type1),
                Update::Xor => (lazy1 ^ lazy2, type2),
            },
        }
    }

    fn build_range(&mut self, st: i32, en: i32, node: usize, ctx: &SegTreeBuildCtx) {
        if st == en {
            self.tree[node].lazy = ctx.vals[st as usize] as i32;
            self.tree[node].update_type = Update::Assign;
            self.tree[node].frequency = vec![0; B];
            self.apply_lazy(st, en, node);
            return;
        }
        let mid = (st + en) >> 1;
        let node_l = node << 1;
        let node_r = (node << 1) | 1;
        self.build_range(st, mid, node_l, ctx);
        self.build_range(mid + 1, en, node_r, ctx);
        self.tree[node] = self.tree[node_l].merge(&self.tree[node_r]);
    }

    fn new(start: i32, end: i32, ctx: &SegTreeBuildCtx) -> SegTree {
        let len = 4 * (end - start + 1) as usize;
        let default_node = Node {
            frequency: Vec::new(),
            update_type: Update::None,
            lazy: -1,
        };
        let mut st = SegTree {
            tree: vec![default_node; 4 * len],
            start,
            end,
        };
        st.build_range(start, end, 1, ctx);
        st
    }
}

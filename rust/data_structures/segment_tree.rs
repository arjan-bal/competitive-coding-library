#[derive(Clone, Debug)]
struct Node {
    value: i32,
}

impl Node {
    fn merge(&self, other: &Node) -> Node {
        Node {
            value: // logic to merge nodes
        }
    }
}

#[derive(Debug)]
struct Res(i32);

impl Res {
    fn merge(&self, other: &Res) -> Res {
        Res(
            // logic to merge results
        )
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
    fn query(&self, l: i32, r: i32) -> Res {
        self.query_range(self.start, self.end, 1, l, r)
    }

    fn update(&mut self, idx: i32, val: Node) {
        self.update_range(self.start, self.end, 1, val, idx);
    }

    fn query_range(&self, st: i32, en: i32, node: usize, l: i32, r: i32) -> Res {
        if st >= l && en <= r {
            return Res(self.tree[node].value);
        }
        let mid = (st + en) >> 1;
        let node_l = node << 1;
        let node_r = (node << 1) | 1;
        if r <= mid {
            return self.query_range(st, mid, node_l, l, r);
        }
        if l > mid {
            return self.query_range(mid + 1, en, node_r, l, r);
        }
        Res::merge(
            &self.query_range(st, mid, node_l, l, r),
            &self.query_range(mid + 1, en, node_r, l, r),
        )
    }

    fn update_range(&mut self, st: i32, en: i32, node: usize, val: Node, idx: i32) {
        if en < idx || st > idx {
            return ;
        }
        if st == en {
            self.tree[node] = val;
            return ;
        }
        let mid = (st + en) >> 1;
        let node_l = node << 1;
        let node_r = (node << 1) | 1;
        if idx <= mid {
            self.update_range(st, mid, node_l, val, idx);
        } else {
            self.update_range(mid + 1, en, node_r, val, idx);
        }
        self.tree[node] = self.tree[node_l].merge(&self.tree[node_r]);
    }

    fn build_range(&mut self, st: i32, en: i32, node: usize, ctx: &SegTreeBuildCtx) {
        if st == en {
            self.tree[node] = Node {
                value: 0,
            };
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
            value: 0,
        };
        let mut st = SegTree {
            tree: vec![default_node; 4 * len],
            start,
            end,
        };
        // st.build_range(start, end, 1, ctx);
        st
    }
}

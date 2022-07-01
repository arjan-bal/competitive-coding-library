#[derive(Clone, Debug)]
struct Node {
    value: Vec<usize>,
}

impl Node {
    fn merge(&self, other: &Node) -> Node {
        Node {
            value: merge_sorted(&self.value, &other.value),
        }
    }
}

#[derive(Debug)]
struct Res(usize);

impl Res {
    fn merge(&self, other: &Res) -> Res {
        return Res(self.0 + other.0);
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
    fn query(&self, l: &i32, r: &i32, val: &i32) -> Res {
        self.query_range(&self.start, &self.end, &1, l, r, val)
    }

    fn query_range(&self, st: &i32, en: &i32, node: &usize, l: &i32, r: &i32, val: &i32) -> Res {
        if st >= l && en <= r {
            return Res(self.tree[*node]
                .value
                .partition_point(|x| *x as i32 <= *val));
        }
        let mid = (*st + *en) >> 1;
        let node_l = *node << 1;
        let node_r = (*node << 1) | 1;
        if *r <= mid {
            return self.query_range(st, &mid, &node_l, l, r, val);
        }
        if *l > mid {
            return self.query_range(&(mid + 1), en, &node_r, l, r, val);
        }
        Res::merge(
            &self.query_range(st, &mid, &node_l, l, r, val),
            &self.query_range(&(mid + 1), en, &node_r, l, r, val),
        )
    }

    fn build_range(&mut self, st: &i32, en: &i32, node: &usize, ctx: &SegTreeBuildCtx) {
        if st == en {
            self.tree[*node] = Node {
                value: vec![ctx.vals[*st as usize]],
            };
            return;
        }
        let mid = (*st + *en) >> 1;
        let node_l = *node << 1;
        let node_r = (*node << 1) | 1;
        self.build_range(st, &mid, &node_l, ctx);
        self.build_range(&(mid + 1), en, &node_r, ctx);
        self.tree[*node] = self.tree[node_l].merge(&self.tree[node_r]);
    }
}

fn new_segtree(start: &i32, end: &i32, ctx: &SegTreeBuildCtx) -> SegTree {
    let len = 4 * (*end - *start + 1) as usize;
    let default_node = Node {
        value: Vec::with_capacity(0),
    };
    let mut st = SegTree {
        tree: vec![default_node; 4 * len],
        start: *start,
        end: *end,
    };
    st.build_range(start, end, &1, ctx);
    st
}

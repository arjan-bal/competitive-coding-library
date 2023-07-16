
// incomplete implementation of a binary trie.
struct Node {
    freq: usize,
    children: [Option<usize>; 2],
}

impl Node {
    fn new() -> Node {
        Node {
            freq: 0,
            children: [None, None],
        }
    }
}

struct Trie {
    nodes: Vec<Node>,
    depth: usize,
}

impl Trie {
    fn new(depth: usize) -> Trie {
        let root = Node::new();
        Trie {
            nodes: vec![root],
            depth,
        }
    }

    fn insert(&mut self, val: usize) {
        let mut cur_idx = 0;
        for cur_depth in (0..self.depth).rev() {
            let mut cur_node = &mut self.nodes[cur_idx];
            cur_node.freq += 1;
            let nxt = (val >> cur_depth) & 1;

            if let None = cur_node.children[nxt] {
                self.nodes[cur_idx].children[nxt] = Some(self.nodes.len());
                self.nodes.push(Node::new());
            }
            cur_idx = self.nodes[cur_idx].children[nxt].unwrap();
        }
    }

    // Finds the number of elements in the trie that have a common prefix with target and are >= target.
    fn query(&self, target: usize) -> usize {
        let mut cur_idx = 0;
        let mut cur_ans = 0;

        for cur_depth in (0..self.depth).rev() {
            let cur_node = &self.nodes[cur_idx];
            let nxt = (target >> cur_depth) & 1;


            if nxt == 0 {
                match cur_node.children[1] {
                    Some(x) => cur_ans = max(cur_ans, self.nodes[x].freq),
                    None => (),
                }
            }

            match cur_node.children[nxt] {
                Some(x) => cur_idx = x,
                None => break,
            }

            if ((1 << cur_depth) - 1) & target == 0 {
                cur_ans = max(cur_ans, self.nodes[cur_idx].freq);
            }
        }

        cur_ans
    }
}

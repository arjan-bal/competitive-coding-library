struct DFSContext<'a> {
    adj: &'a Vec<Vec<usize>>,
    vals: &'a Vec<usize>,
}

fn dfs(cur: &usize, par: &usize, ctx: &mut DFSContext) {
    for i in &ctx.adj[*cur] {
        if i == par {
            continue;
        }
        dfs(&i, cur, ctx);
    }
}

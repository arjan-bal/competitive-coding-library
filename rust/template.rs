/*
    Author: Arjan Singh Bal
    "Everything in this world is magic, except to the magician"
*/

#[allow(unused_imports)]
use std::str::FromStr;
use std::io::{BufWriter, stdin, stdout, Write, Stdout};

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

fn main() {
    let mut scan = Scanner::default();
    let mut out = &mut BufWriter::new(stdout());
    let t = scan.next();
    for _ in 0..t {
        solve(&mut scan, &mut out);
    }
}

fn solve(scan: &mut Scanner, out: &mut BufWriter<Stdout>) {
    
}

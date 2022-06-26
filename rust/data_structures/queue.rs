// A simple queue implementation with basic functions. 
// This doesn't free memory on pop operations!
struct Queue<T> {
    q: Vec<T>,
    st: usize,
}

impl<T: Copy> Queue<T> {
    fn push(&mut self, val: T) {
        self.q.push(val);
    }

    fn pop(&mut self) -> T {
        if self.st >= self.q.len() {
            panic!("Cannot pop from empty queue!");
        }
        self.st += 1;
        self.q[self.st - 1]
    }

    fn len(self) -> usize {
        return self.q.len() - self.st;
    }

    fn is_empty(&self) -> bool {
        return self.q.len() - self.st == 0;
    }

    fn new(capacity: usize) -> Queue<T> {
        return Queue {
            q: Vec::with_capacity(capacity),
            st: 0,
        };
    }
}
